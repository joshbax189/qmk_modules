#include "menu.h"

#ifdef RGB_MATRIX_ENABLE
// TODO only togg works -- but all work for UG?
MAKE_MENU(rgb_menu,
    { "SAT+", KEY_ACTION(RM_SATU) },
    { "SAT-", KEY_ACTION(RM_SATD) },
    { "NEXT", KEY_ACTION(RM_NEXT) },
    { "PREV", KEY_ACTION(UG_PREV) },
    { "TOGG", KEY_ACTION(UG_TOGG) },
    { "HUE+", KEY_ACTION(RM_HUEU) },
    { "HUE-", KEY_ACTION(RM_HUED) },
);
#endif

#ifdef RGBLIGHT_ENABLE
MAKE_MENU(ug_menu,
    { "TOGG", KEY_ACTION(UG_TOGG) },
    { "NEXT", KEY_ACTION(UG_NEXT) },
    { "PREV", KEY_ACTION(UG_PREV) },
    { "HUE+", KEY_ACTION(UG_HUEU) },
    { "HUE-", KEY_ACTION(UG_HUED) },
    { "SAT+", KEY_ACTION(UG_SATU) },
    { "SAT-", KEY_ACTION(UG_SATD) },
    { "VAL+", KEY_ACTION(UG_VALU) },
    { "VAL-", KEY_ACTION(UG_VALD) },
);
#endif

MAKE_MENU(boot_menu,
     { "RESET", KEY_ACTION(QK_RBT) },
     { "BOOT", KEY_ACTION(QK_BOOT) },
);

MAKE_MENU(sys_menu,
     { "POWER", KEY_ACTION(KC_PWR) },
     { "SLEEP", KEY_ACTION(KC_SLEP) },
     { "WAKE", KEY_ACTION(KC_WAKE) },
);

#ifdef EXTRAKEY_ENABLE
MAKE_MENU(media_menu,
     { "MUTE", KEY_ACTION(KC_MUTE) },
     { "VOLU", KEY_ACTION(KC_VOLU) },
     { "VOLD", KEY_ACTION(KC_VOLD) },
     { "NEXT", KEY_ACTION(KC_MNXT) },
     { "PREV", KEY_ACTION(KC_MPRV) },
     { "STOP", KEY_ACTION(KC_STOP) },
     { "PLAY", KEY_ACTION(KC_MPLY) },
);
#endif

// TODO other magic codes
/* { "CL_SWAP", MENU_KC, { .keycode = CL_SWAP } }, */
/* { "CL_NORM", MENU_KC, { .keycode = CL_NORM } }, */
/* { "CL_CTRL", MENU_KC, { .keycode = CL_CTRL } }, */
/* { "CL_CAPS", MENU_KC, { .keycode = CL_CAPS } }, */
/* { "EC_SWAP", MENU_KC, { .keycode = EC_SWAP } }, */
/* { "EC_NORM", MENU_KC, { .keycode = EC_NORM } }, */
/* { "CG_LSWP", MENU_KC, { .keycode = CG_LSWP } }, */
/* { "CG_LNRM", MENU_KC, { .keycode = CG_LNRM } }, */
/* { "CG_RSWP", MENU_KC, { .keycode = CG_RSWP } }, */
/* { "CG_RNRM", MENU_KC, { .keycode = CG_RNRM } }, */
/* { "CG_SWAP", MENU_KC, { .keycode = CG_SWAP } }, */
/* { "CG_NORM", MENU_KC, { .keycode = CG_NORM } }, */
/* { "AG_LSWP", MENU_KC, { .keycode = AG_LSWP } }, */
/* { "AG_LNRM", MENU_KC, { .keycode = AG_LNRM } }, */
/* { "AG_RSWP", MENU_KC, { .keycode = AG_RSWP } }, */
/* { "AG_RNRM", MENU_KC, { .keycode = AG_RNRM } }, */
/* { "AG_SWAP", MENU_KC, { .keycode = AG_SWAP } }, */
/* { "AG_NORM", MENU_KC, { .keycode = AG_NORM } }, */
/* { "GE_SWAP", MENU_KC, { .keycode = GE_SWAP } }, */
/* { "GE_NORM", MENU_KC, { .keycode = GE_NORM } }, */
/* { "BS_SWAP", MENU_KC, { .keycode = BS_SWAP } }, */
/* { "BS_NORM", MENU_KC, { .keycode = BS_NORM } }, */

MAKE_MENU(swap_menu,
     { "CL", KEY_ACTION(CL_TOGG) },
     { "EC", KEY_ACTION(EC_TOGG) },
     { "CG", KEY_ACTION(CG_TOGG) },
     // Alt/GUI both sides
     { "AG", KEY_ACTION(AG_TOGG) },
     // \/Bspc
     { "BS", KEY_ACTION(BS_TOGG) },
);

MAKE_MENU(nkro_menu,
     { "ON", KEY_ACTION(NK_ON)},
     { "OFF", KEY_ACTION(NK_OFF) },
     { "TOGG", KEY_ACTION(NK_TOGG) },
);

#ifdef EE_HANDS
MAKE_MENU(split_menu,
     { "EH_LEFT", KEY_ACTION(EH_LEFT)},
     { "EH_RGHT", KEY_ACTION(EH_RGHT)},
);
#endif

MAKE_MENU(gui_menu,
    { "GU_OFF" , KEY_ACTION(GU_OFF) },
    { "GU_ON"  , KEY_ACTION(GU_ON) },
    { "GU_TOGG", KEY_ACTION(GU_TOGG) },
);

MAKE_MENU(magic_menu,
    { "NKRO", SUB_MENU(nkro_menu) },
    { "SWAP", SUB_MENU(swap_menu) },
    { "GKEYS", SUB_MENU(gui_menu) },
    #ifdef EE_HANDS
    { "SPLIT", SUB_MENU(split_menu) },
    #endif
    );

TOP_MENU(
#ifdef RGB_MATRIX_ENABLE
    { "RGB", SUB_MENU(rgb_menu) },
#endif
#ifdef RGBLIGHT_ENABLE
    { "UG", SUB_MENU(ug_menu) },
#endif
    { "BOOT", SUB_MENU(boot_menu)},
    { "MAGIC", SUB_MENU(magic_menu) },
#ifdef EXTRAKEY_ENABLE
    { "MEDIA", SUB_MENU(media_menu) },
#endif
    { "SYS", SUB_MENU(sys_menu) },
);
