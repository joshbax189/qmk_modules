// Copyright 2026 Josh Bax

#include QMK_KEYBOARD_H

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,0,0);

// update_sync appears to be involved
// try it without initially
/* static void update_sync(void) { */
/*     if (is_keyboard_master()) { */
/*         master_to_slave_t m2s = { */
/*             .oled = { */
/*                 .static_display = oled_state.static_display, */
/*                 .timeout = oled_state.timeout, */
/*                 .active = oled_state.active, */
/*             }, */
/*             .case_lock = { */
/*                 .capturing = case_lock_state.capturing, */
/*                 .active = case_lock_state.active */
/*             } */
/*         }; */
/*         transaction_rpc_send(USER_SYNC_A, sizeof(master_to_slave_t), &m2s); */
/*     } */
/* } */

static uint16_t idle_timer = 0;

typedef enum {
    /* default: echo the typed char, then use _ as separator */
    SEP_DEF,
    /* symbol: echo nothing, use the typed char as separator */
    SEP_SYM,
    /* continue: echo _, then use _ as separator */
    SEP_CONT,
    /* camel: echo nothing, space activates shift for following char */
    SEP_CAMEL,
    /* title: activate shift, space is echoed and activates shift */
    SEP_TITLE
} sep_kind_t;

typedef struct {
    /* space is modified to send a different char */
    bool active :1;
    /* accept a char to select case mode */
    bool capturing :1;
    /* set if prev typed key was space */
    bool last_key_spc :1;
    /* active rule */
    sep_kind_t mode;
    uint16_t output;
} case_lock_flags_t;

case_lock_flags_t case_lock_state = {
    .active = false,
    .capturing = false,
    .last_key_spc = false,
    .mode = SEP_DEF,
    .output = KC_NO,
};

static inline void case_lock_on(void) {
    case_lock_state.active = true;
    /* update_sync(); */
}

static void case_lock_off(void) {
    clear_oneshot_mods();
    case_lock_state.active = false;
    case_lock_state.capturing = false;
    case_lock_state.last_key_spc = false;
    /* update_sync(); */
    case_lock_state.mode = SEP_DEF;
    case_lock_state.output = KC_NO;
    dprintf("case_lock disable\n");
}

void housekeeping_task_case_lock(void) {
    if (case_lock_state.active && timer_expired(timer_read(), idle_timer)) {
        case_lock_off();
    }
}

static void reset_idle_timer(void) {
    idle_timer = timer_read() + CASE_LOCK_TIMEOUT;
}

static void send_separator(void){
    switch (case_lock_state.mode) {
        case SEP_CONT:
        case SEP_DEF:
        case SEP_SYM:
            tap_code16(case_lock_state.output);
            break;
        case SEP_CAMEL:
            set_oneshot_mods(MOD_BIT(KC_LSFT));
            break;
        case SEP_TITLE:
            tap_code(KC_SPC);
            set_oneshot_mods(MOD_BIT(KC_LSFT));
            break;
    }
}

/* accept a char which selects from the sep rules */
static bool process_case_capture(uint16_t keycode) {
    switch (keycode) {
    case KC_MINS:
    case KC_UNDS:
    case KC_DOT:
    case KC_SLSH:
    case KC_BSLS:
        case_lock_state.mode = SEP_SYM;
        case_lock_state.output = keycode;
        break;
    case KC_SPC:
        case_lock_state.mode = SEP_CONT;
        case_lock_state.output = KC_UNDS;
        break;
    case KC_LSFT:
        case_lock_state.mode = SEP_CAMEL;
        case_lock_state.output = KC_NO;
        break;
    case KC_RSFT:
        case_lock_state.mode = SEP_TITLE;
        case_lock_state.output = KC_SPC;
        break;
    default:
        case_lock_state.mode = SEP_DEF;
        case_lock_state.output = KC_UNDS;
        break;
    }

    case_lock_state.capturing = false;
    case_lock_on();
    dprintf("case_lock enable mode = %d output = %X\n", case_lock_state.mode, case_lock_state.output);
    reset_idle_timer();

    // Immediate behaviours
    switch (case_lock_state.mode) {
        case SEP_DEF:
            return true;

        case SEP_SYM:
            return false;

        case SEP_CONT:
            tap_code16(case_lock_state.output);
            return false;

        case SEP_CAMEL:
            unregister_mods(MOD_BIT(KC_LSFT));
            return false;

        case SEP_TITLE:
            unregister_mods(MOD_BIT(KC_RSFT));
            set_oneshot_mods(MOD_BIT(KC_RSFT));
            return false;
    }
    return true;
}

bool process_record_case_lock(uint16_t keycode, keyrecord_t* record) {
    if (!record->event.pressed) {
        return true;
    }

    // double case lock -> caps
    if (keycode == CASE_LOCK) {
        if (!case_lock_state.capturing) {
            case_lock_state.capturing = true;
            reset_idle_timer();
        } else {
            tap_code(KC_CAPS);
            case_lock_state.capturing = false;
        }
        return true;
    }

    // esc cancels both
    if (keycode == KC_ESC) {
        case_lock_off();
        return false;
    }

    // this can capture some unrelated chars
    if (case_lock_state.capturing) {
        switch (keycode) {
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            return true;
        default:
            return process_case_capture(keycode);
        }
    }

    if (!case_lock_state.active) {
        return true;
    }

    reset_idle_timer();

    if (keycode == KC_SPC) {
        // double space deletes a separator and exits
        if (case_lock_state.last_key_spc) {
            switch (case_lock_state.mode) {
                case SEP_CAMEL:
                    case_lock_off();
                    return true;

                case SEP_TITLE:
                    case_lock_off();
                    return false;

                case SEP_DEF:
                case SEP_SYM:
                case SEP_CONT:
                    tap_code(KC_BSPC);
                    tap_code(KC_SPC);
                    case_lock_off();
                    return false;
            }
        } else {
            send_separator();
            case_lock_state.last_key_spc = true;
            return false;
        }
    }

    case_lock_state.last_key_spc = false;

    // these exit all modes
    switch (keycode) {
    case KC_SCLN:
    case KC_COLON:
        case_lock_off();
        break;
    }

    return true;
}
