#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef struct { uint16_t keycode; } keyrecord_t;

enum keycodes { QK_RBT, QK_BOOT, UG_TOGG, UG_NEXT, UG_PREV, CL_TOGG, EC_TOGG, CG_TOGG, AG_TOGG, BS_TOGG, NK_ON, NK_OFF, NK_TOGG, EH_LEFT, EH_RGHT, GU_OFF, GU_ON, GU_TOGG, KC_PWR, KC_SLEP, KC_WAKE, KC_MUTE, KC_VOLU, KC_VOLD, KC_MNXT, KC_MPRV, KC_PLAY, KC_STOP };

void process_record_quantum(keyrecord_t*);

void oled_write_ln(char*, bool);
void oled_clear(void);

#define OLED_ENABLE
