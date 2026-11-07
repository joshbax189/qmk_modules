#pragma once

#include QMK_KEYBOARD_H

typedef enum {
    MENU_SUB, // data is another menu
    MENU_KC,  // data is a keycode
    MENU_FN,  // data is a function
} menu_action_t;

typedef struct menu_t menu_t;

typedef union {
    uint16_t keycode;
    menu_t  *sub_menu;
    void (*callback)(void);
} menu_data_t;

/* A single displayed line in a menu */
typedef struct {
    char         *text;
    menu_action_t action_type;
    menu_data_t   data;
} menu_entry_t;

/* A submenu together with its state */
struct menu_t {
    menu_entry_t *entries;
    uint8_t       index;
    /* Forms a linked list back to top_menu, whose parent is NULL */
    menu_t *parent;
};

void menu_up(void);
void menu_down(void);
void menu_back(void);
void menu_act(keyrecord_t *);
void menu_reset(void);

const menu_entry_t *menu_get_entry(uint8_t);

#ifdef OLED_ENABLE
void menu_render_oled(void);
#endif

/* Menu Delimiter */
#define MENU_END {NULL, MENU_SUB, {0}}

#define SUB_MENU(name)    \
    MENU_SUB, {           \
        .sub_menu = &name \
    }
#define FUNC_ACTION(name) \
    MENU_FN, {            \
        .callback = &name \
    }
#define KEY_ACTION(name) \
    MENU_KC, {           \
        .keycode = name  \
    }

#define MAKE_MENU(name, ...)                                \
    menu_entry_t name##_entries[] = {__VA_ARGS__ MENU_END}; \
    menu_t       name             = {.entries = name##_entries, .index = 0, .parent = NULL}

#define TOP_MENU(...) MAKE_MENU(top_menu, __VA_ARGS__)

#ifdef RGB_MATRIX_ENABLE
extern menu_t rgb_menu;
#endif

#ifdef RGBLIGHT_ENABLE
extern menu_t ug_menu;
#endif

extern menu_t boot_menu;
extern menu_t swap_menu;
extern menu_t nkro_menu;
extern menu_t gui_menu;
extern menu_t magic_menu;
#ifdef EXTRAKEY_ENABLE
extern menu_t media_menu;
#endif
extern menu_t sys_menu;
extern menu_t top_menu;
