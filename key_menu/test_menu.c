// -*- compile-command: "gcc -D QMK_KEYBOARD_H='\"test_menu.h\"' test_menu.c default_menu.c menu.c"; -*-

#include "menu.h"

extern menu_t* current_menu;

// stub
void process_record_quantum(keyrecord_t* x) {
    return;
}

void oled_clear() {
    return;
}

void oled_write_ln(char* line, bool invert) {
    printf(line);
    if (invert) {
        printf(" <\n");
    } else {
        printf("\n");
    }
}

int main() {
    while (true) {
        char in;
        scanf("%c", &in);
        switch (in) {
        case 'j':
            menu_back();
            printf("---\n");
            menu_render_oled();
            break;
        case 'k':
            menu_up();
            printf("---\n");
            menu_render_oled();
            break;
        case 'l':
            menu_down();
            printf("---\n");
            menu_render_oled();
            break;
        case ';':
            keyrecord_t foo = { 0 };
            menu_act(&foo);
            printf("---\n");
            menu_render_oled();
            break;
        }
    }

    return 0;
}
