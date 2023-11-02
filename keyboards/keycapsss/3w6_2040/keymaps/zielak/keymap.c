// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _COLEMAKDH = 0,
    _QWERTY,
    _NAV,
    _NUM,
    _FNK,
    _SYM,
    // _SML,
    // _SMR,
    // _FUN,
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
};

// App swapping and Print screen are different on Mac...
static bool     isOnMac = true;
static uint16_t ctrlKey = KC_LGUI;

static bool isCapsWordUp = false;

// Aliases to make keymap more readable
// #define FUN_L MO(_FUN)
#define NAV_L MO(_NAV)
#define NUM_L MO(_NUM)
#define FNK_L MO(_FNK)
#define SYM_L MO(_SYM)
// #define SML_L MO(_SML)
// #define SMR_L MO(_SMR)

// Which key do you use to enter a layer
#define _ENTRY_ _______

// My usage
// ctrl 0.3  0.0 = 0.3
// alt  0.4  0.2 = 0.6
// shft 0.8  3.0 = 3.8
// gui  7.2  0.0 = 7.2

// bottom row modifiers
// #define _LCTL LCTL_T(KC_Z)
// #define _LALT LALT_T(KC_X)
// #define _LSFT LSFT_T(KC_C)
// #define _LGUI LGUI_T(KC_D)

// #define _RGUI RGUI_T(KC_H)
// #define _RSFT RSFT_T(KC_COMM)
// #define _RALT RALT_T(KC_DOT)
// #define _RCTL RCTL_T(KC_SLASH)

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

    [_COLEMAKDH] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,            KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_BSPC ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
     // KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_G    ,            KC_M    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,
        _LCTL   ,_LALT   ,_LSFT   ,_LGUI   ,KC_G    ,            KC_M    ,_RGUI   ,_RSFT   ,_RALT   ,_RCTL   ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
     // _LCTL   ,_LALT   ,_LSFT   ,_LGUI   ,KC_V    ,            KC_K    ,_RGUI   ,_RSFT   ,_RALT   ,_RCTL   ,
        KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,            KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLASH,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              FNK_L   ,NAV_L   ,KC_SPACE,   NUM_L   ,SYM_L   ,XXXXXXX // Trackball
                           //`--------------------------'  `--------------------------'
    ),
    [_QWERTY] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,            KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,            KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_BSPC ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,            KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLASH,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              FNK_L   ,NAV_L   ,KC_SPACE,   NUM_L   ,SYM_L   ,XXXXXXX // Trackball
                           //`--------------------------'  `--------------------------'
    ),
    [_NAV] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        K_TERMI ,XXXXXXX ,XXXXXXX ,KC_PSCR ,XXXXXXX ,            KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_BSPC ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_LCTL ,KC_LALT ,KC_LSFT ,KC_LGUI ,XXXXXXX ,            KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RIGHT,KC_DEL  ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        XXXXXXX ,KC_BTN2 ,KC_BTN3 ,KC_BTN1 ,XXXXXXX ,            XXXXXXX ,XXXXXXX ,K_INDEL ,K_INDER ,KC_INS  ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              XXXXXXX ,_ENTRY_ ,_______ ,   XXXXXXX ,CW_TOGG ,XXXXXXX
                           //`--------------------------'  `--------------------------'
    ),
    [_NUM] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_PAST ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_BSPC ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_P0   ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PMNS ,            KC_PEQL ,KC_RGUI ,KC_RSFT ,KC_RALT ,KC_RCTL ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        XXXXXXX ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PSLS ,            XXXXXXX ,XXXXXXX ,KC_SCLN ,KC_COLN ,XXXXXXX ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              XXXXXXX ,KC_DOT  ,_______ ,   _ENTRY_ ,XXXXXXX ,XXXXXXX
                           //`--------------------------'  `--------------------------'
    ),
    [_FNK] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,            GU_TOGG ,RGB_TOG ,KC_BRID ,KC_BRIU ,DT_UP   ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_TAB  ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,            CG_NORM ,KC_MUTE ,KC_VOLD ,KC_VOLU ,DT_DOWN ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_LSFT ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,            CG_SWAP ,KC_MPLY ,KC_MPRV ,KC_MNXT ,DT_PRNT ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              _ENTRY_ ,EE_CLR  ,_______ ,   DF_QWER ,DF_COLE ,XXXXXXX
                           //`--------------------------'  `--------------------------'
    ),
    [_SYM] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_QUES ,KC_EXLM ,K_ARROW ,KC_PPLS ,KC_PERC ,            KC_AMPR ,KC_RPRN ,KC_RCBR ,KC_RBRC ,KC_BSPC ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_AT   ,KC_DLR  ,KC_UNDS ,KC_PMNS ,KC_EQL  ,            KC_QUOT ,KC_LPRN ,KC_LCBR ,KC_LBRC ,KC_PIPE ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_TILD ,KC_HASH ,KC_CIRC ,KC_PSLS ,KC_PAST ,            KC_DQUO ,KC_GRV  ,KC_SCLN ,KC_COLN ,KC_BSLS ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              XXXXXXX ,CW_TOGG ,_______ ,   XXXXXXX ,_ENTRY_ ,XXXXXXX
                           //`--------------------------'  `--------------------------'
    ),

    // clang-format on
};

void led_init(void) {
    setPinOutput(BLUE_LED_PIN);
    // blu_led_off;
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
    led_init();
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case _LGUI:
        case _RGUI:
            return TAPPING_TERM - 10;
        case _LSFT:
        case _RSFT:
            return TAPPING_TERM - 20;
        case _LALT:
        case _RALT:
            return TAPPING_TERM + 0;
        case _LCTL:
        case _RCTL:
            return TAPPING_TERM + 20;
        default:
            return TAPPING_TERM;
    }
}

bool tap_ctrl_and_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code(ctrlKey);
        tap_code_delay(keycode, 20);
        unregister_code(ctrlKey);
    }
    return false;
}

void update_caps_led(void) {
    if (isCapsWordUp) {
        blu_led_on;
    } else {
        blu_led_off;
    }
}

void caps_word_set_user(bool active) {
    isCapsWordUp = active;
    update_caps_led();
}

// BEGIN rgb layers

const rgblight_segment_t PROGMEM layer_colemak[] = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_OFF});
const rgblight_segment_t PROGMEM layer_qwerty[]  = RGBLIGHT_LAYER_SEGMENTS({0, 32, 0, 128, 50});
const rgblight_segment_t PROGMEM layer_nav[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_GOLD});
const rgblight_segment_t PROGMEM layer_num[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_BLUE});
const rgblight_segment_t PROGMEM layer_fnk[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_PURPLE});
const rgblight_segment_t PROGMEM layer_sym[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_GREEN});
const rgblight_segment_t PROGMEM layer_sml[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_GREEN});
// const rgblight_segment_t PROGMEM layer_smr[]  = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_GREEN});
// const rgblight_segment_t PROGMEM layer_fun[] = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_PINK});

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(layer_colemak, layer_qwerty, layer_nav, layer_num, layer_fnk, layer_sym);

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));

    // if (!is_keyboard_master()) {
    //     if (layer_state_cmp(state, 7)) {
    //         pimoroni_trackball_set_rgbw(RGB_MAGENTA, 0);
    //     } else if (layer_state_cmp(state, 6)) {
    //         pimoroni_trackball_set_rgbw(RGB_PURPLE, 0);
    //     } else if (layer_state_cmp(state, 5)) {
    //         pimoroni_trackball_set_rgbw(RGB_PINK, 0);
    //     } else if (layer_state_cmp(state, 4)) {
    //         pimoroni_trackball_set_rgbw(RGB_GREEN, 0);
    //     } else if (layer_state_cmp(state, 3)) {
    //         pimoroni_trackball_set_rgbw(RGB_GREEN, 0);
    //     } else if (layer_state_cmp(state, 2)) {
    //         pimoroni_trackball_set_rgbw(RGB_BLUE, 0);
    //     } else if (layer_state_cmp(state, 1)) {
    //         pimoroni_trackball_set_rgbw(RGB_GOLD, 0);
    //     } else if (layer_state_cmp(state, 0)) {
    //         pimoroni_trackball_set_rgbw(RGB_OFF, 0);
    //     }
    // }

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, true);

    update_caps_led();

    return false;
}

// EOF rgb layers

#ifndef VIAL_ENABLE
const uint16_t PROGMEM combo_enter[] = {KC_COMM, KC_DOT, COMBO_END};
// const uint16_t PROGMEM combo_esc[]   = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_enter, KC_ENT),
    // COMBO(combo_esc, KC_ESC),
    COMBO(combo_tab, KC_TAB),
};
#endif

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

#ifdef VIAL_ENABLE
    // Pre-define my fav combos
    vial_combo_entry_t combo_enter = {{_RSFT, _RALT, KC_NO, KC_NO}, KC_ENT};
    vial_combo_entry_t combo_esc   = {{KC_W, KC_F, KC_NO, KC_NO}, KC_ESC};
    vial_combo_entry_t combo_tab   = {{_LALT, _LSFT, KC_NO, KC_NO}, KC_TAB};

    dynamic_keymap_set_combo(0, &combo_enter);
    dynamic_keymap_set_combo(1, &combo_esc);
    dynamic_keymap_set_combo(2, &combo_tab);
#endif

    // Customise these values to desired behaviour
    // debug_enable   = true;
    // debug_matrix   = true;
    // debug_keyboard = true;
    // debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CG_NORM:
            if (record->event.pressed) {
                isOnMac = true;
                ctrlKey = KC_LGUI;
            }
            return true;
        case CG_SWAP:
            if (record->event.pressed) {
                isOnMac = false;
                ctrlKey = KC_LCTL;
            }
            return true;
        case KC_PSCR:
            if (record->event.pressed) {
                if (isOnMac) {
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    tap_code(KC_4);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
            } else {
                if (isOnMac) {
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
        case K_UNDO:
            return tap_ctrl_and_key(KC_Z, record);
        case K_REDO:
            return tap_ctrl_and_key(KC_Y, record);
        case K_CUT:
            return tap_ctrl_and_key(KC_X, record);
        case K_COPY:
            return tap_ctrl_and_key(KC_C, record);
        case K_PASTE:
            return tap_ctrl_and_key(KC_V, record);
        case K_FIND:
            return tap_ctrl_and_key(KC_F, record);
        case K_CLOSE:
            return tap_ctrl_and_key(KC_W, record);
        case K_ARROW:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            return false;
        case K_INDEL:
            return tap_ctrl_and_key(KC_LBRC, record);
        case K_INDER:
            return tap_ctrl_and_key(KC_RBRC, record);
        case K_TERMI:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_GRAVE);
                unregister_code(KC_LCTL);
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }

    return true;
}
