#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

void my_custom_function(void);

enum layers {
    _COLEMAKDH = 0,
    _QWERTY,
    _NAV,
    _NUM,
    _NUM_PAD,
    _FNK,
    _SYM,
};

enum custom_keycodes {
    K_QUIT = QK_KB_0,
    K_CLOSE,
    K_FIND,
    K_UNDO,
    K_REDO,
    K_CUT,
    K_COPY,
    K_PASTE,
    K_INDEL,
    K_INDER,
    K_ARROW,
    K_TERMI,
    APP_NXT,
    APP_PRV,
};

// My usage
// ctrl 0.3  0.0 = 0.3
// alt  0.4  0.2 = 0.6
// shft 0.8  3.0 = 3.8
// gui  7.2  0.0 = 7.2

// home row modifiers
#define _LCTL LCTL_T(KC_A)
#define _LALT LALT_T(KC_R)
#define _LSFT LSFT_T(KC_S)
#define _LGUI LGUI_T(KC_T)

#define _RGUI RGUI_T(KC_N)
#define _RSFT RSFT_T(KC_E)
#define _RALT RALT_T(KC_I)
#define _RCTL RCTL_T(KC_O)

#define DF_COLE DF(_COLEMAKDH)
#define DF_QWER DF(_QWERTY)

#define NAV_L MO(_NAV)

// Which key do you use to enter a layer
#define _ENTRY_ _______

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);

bool tap_ctrl_and_key(uint16_t keycode, keyrecord_t *record);

#endif
