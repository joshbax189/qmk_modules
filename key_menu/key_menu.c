// Copyright 2026 Josh Bax
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "introspection.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

bool process_record_oled_key_menu(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_oled_key_menu_kb(keycode, record)) {
        return false;
    }

    switch (keycode) {
    case MENU_BACK:
        if (record->event.pressed) {
            menu_back();
        }
        break;
    case MENU_ACT:
        if (record->event.pressed) {
            menu_act(record);
        }
        break;
    case MENU_UP:
        if (record->event.pressed) {
            menu_up();
        }
        break;
    case MENU_DOWN:
        if (record->event.pressed) {
            menu_down();
        }
        break;
    case MENU_RESET:
        if (record->event.pressed) {
            menu_reset();
        }
        break;
    }

    return true;
}
