// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "print.h"
#include QMK_KEYBOARD_H

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
    NUM_L,
    NUMPD_L,
};

// App swapping and Print screen are different on Mac...
static uint16_t ctrlKey        = KC_LGUI;
static bool     isOnMac        = true;
static bool     isSwappingApps = false;

static bool     numActive    = false;
static bool     numLocked    = false;
static uint16_t numLayer     = _NUM;
static uint16_t numTimestamp = 0;
static uint16_t numTapCount  = 0;

// Aliases to make keymap more readable
#define FNK_L LT(_FNK, KC_ESC)
#define NAV_L LT(_NAV, KC_DEL)
// #define NUM_L TT(_NUM)
// #define NUMPD_L TG(_NUM_PAD)
// #define TAP_ALT KC_F18
#define SYM_L LT(_SYM, KC_F18)

// Which key do you use to enter a layer
#define _ENTRY_ _______

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
                           // KC_ESC  ,KC_DEL  ,        ,   TT(_NUM),OSM(ALT),
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
        K_TERMI ,APP_PRV ,APP_NXT ,KC_PSCR ,XXXXXXX ,            KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,_______ ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_LCTL ,KC_LALT ,KC_LSFT ,KC_LGUI ,XXXXXXX ,            KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RIGHT,XXXXXXX ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        K_UNDO  ,K_CUT   ,K_COPY  ,K_PASTE ,K_REDO  ,            XXXXXXX ,KC_TAB  ,K_INDEL ,K_INDER ,KC_INS  ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              XXXXXXX ,_ENTRY_ ,_______ ,   XXXXXXX ,KC_CAPS ,XXXXXXX
                           //`--------------------------'  `--------------------------'
    ),
    [_NUM] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_PERC ,KC_7    ,KC_8    ,KC_9    ,KC_PPLS ,            NUMPD_L ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_PAST ,KC_4    ,KC_5    ,KC_6    ,KC_MINS ,            XXXXXXX ,KC_RGUI ,KC_RSFT ,KC_RALT ,KC_RCTL ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_PSLS ,KC_1    ,KC_2    ,KC_3    ,KC_EQL  ,            K_REDO  ,K_PASTE ,K_COPY  ,K_CUT   ,K_UNDO  ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              KC_DOT   ,KC_0   ,_______ ,   _ENTRY_ ,XXXXXXX ,XXXXXXX
                           //`--------------------------'  `--------------------------'
    ),
    [_NUM_PAD] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_PERC ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PPLS ,            NUMPD_L ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_PAST ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PMNS ,            XXXXXXX ,KC_RGUI ,KC_RSFT ,KC_RALT ,KC_RCTL ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
        KC_PSLS ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PENT ,            K_REDO  ,K_PASTE ,K_COPY  ,K_CUT   ,K_UNDO  ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              KC_PDOT ,KC_P0  ,_______ ,    _ENTRY_ ,XXXXXXX ,XXXXXXX
                           //`--------------------------'  `--------------------------'
    ),
    [_FNK] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,XXXXXXX ,            GU_TOGG ,RGB_TOG ,KC_BRID ,KC_BRIU ,DT_UP   ,
     //|--------+--------+--------+--------|--------+           |--------+--------+--------+--------+--------|
        KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,XXXXXXX ,            CG_NORM ,KC_MUTE ,KC_VOLD ,KC_VOLU ,DT_DOWN ,
     //|--------+--------+--------+--------|--------+           |--------+--------+--------+--------+--------|
        KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX ,            CG_SWAP ,KC_MPLY ,KC_MPRV ,KC_MNXT ,DT_PRNT ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              _ENTRY_ ,XXXXXXX ,_______ ,   DF_QWER ,DF_COLE ,XXXXXXX
                           //`--------------------------'  `--------------------------'
    ),
    [_SYM] = LAYOUT_split_3x5_3(
     //,--------------------------------------------.           ,--------------------------------------------.
        KC_QUES ,KC_EXLM ,K_ARROW ,KC_COLN ,KC_PPLS ,            XXXXXXX ,KC_LCBR ,KC_RCBR ,KC_AMPR ,_______ ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+
        KC_AT   ,KC_DLR  ,KC_UNDS ,KC_SCLN ,KC_MINS ,            KC_GRV  ,KC_LPRN ,KC_RPRN ,KC_DQUO ,KC_PIPE ,
     //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+
        KC_TILD ,KC_HASH ,KC_CIRC ,KC_PSLS ,KC_PAST ,            XXXXXXX ,KC_LBRC ,KC_RBRC ,KC_QUOT ,KC_BSLS ,
     //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                              XXXXXXX ,KC_CAPS ,_______ ,   XXXXXXX ,_ENTRY_ ,XXXXXXX
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
        tap_code_delay(keycode, 12);
        unregister_code(ctrlKey);
    }
    return false;
}

bool switch_num_layers(void) {
    numActive = !numActive;
    numLayer  = numActive ? _NUM_PAD : _NUM;

    if (numActive) {
        layer_on(_NUM_PAD);
        layer_off(_NUM);
    } else {
        layer_off(_NUM_PAD);
        layer_on(_NUM);
    }

    return false;
}

void num_layers_off(void) {
    layer_off(_NUM);
    layer_off(_NUM_PAD);
}

void num_layer_on(void) {
    layer_on(numLayer);
    numTapCount = 0;
}

bool tap_num_layers(keyrecord_t *record) {
    // dprint("tap_num_layers");
    // record->tap.count
    // record->tap.interrupted

    if (!numLocked) {
        if (record->event.pressed && numTapCount < 1) {
            numTapCount++;
        }
    }

    dprintf("tap_num_layers - TAPPING_TERM: %d, now: %d, last: %d, TAPcount: %d\n", TAPPING_TERM, record->event.time, numTimestamp, record->tap.count);
    // Did double tap
    if (!numLocked && record->event.pressed && record->tap.count > 1 && record->event.time < numTimestamp + TAPPING_TERM) {
        num_layer_on();
        dprint("Did double tap!\n");
        numLocked = true;
        return false;
    }

    if (numLocked) {
        dprint("is locked\n");
        if (record->event.pressed) {
            dprint("unlocking\n");
            numLocked = false;
            num_layers_off();
        } else {
        }
        return true;
    }

    if (record->event.pressed) {
        numTimestamp = record->event.time;
        num_layer_on();
    } else {
        num_layers_off();
    }
    return true;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        writePin(BLUE_LED_PIN, led_state.caps_lock);
    }
    return res;
}

// BEGIN rgb layers

const rgblight_segment_t PROGMEM layer_colemak[] = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_OFF});
const rgblight_segment_t PROGMEM layer_qwerty[]  = RGBLIGHT_LAYER_SEGMENTS({0, 32, 0, 128, 50});
const rgblight_segment_t PROGMEM layer_nav[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_GOLD});
const rgblight_segment_t PROGMEM layer_num[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_BLUE});
const rgblight_segment_t PROGMEM layer_numpad[]  = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_CYAN});
const rgblight_segment_t PROGMEM layer_fnk[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_PURPLE});
const rgblight_segment_t PROGMEM layer_sym[]     = RGBLIGHT_LAYER_SEGMENTS({0, 32, HSV_GREEN});

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(layer_colemak, layer_qwerty, layer_nav, layer_num, layer_numpad, layer_fnk, layer_sym);

layer_state_t layer_state_set_user(layer_state_t state) {
    // Num / Numpad layer switching

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

    // update_caps_led();

    return true;
}

// EOF rgb layers

#ifndef VIAL_ENABLE
const uint16_t PROGMEM combo_enter[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_tab[]   = {KC_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_enter, KC_ENT),
    COMBO(combo_tab, KC_TAB),
};
#endif

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

#ifdef VIAL_ENABLE
    // Pre-define my fav combos
    vial_combo_entry_t combo_enter = {{_RSFT, _RALT, KC_NO, KC_NO}, KC_ENT};
    vial_combo_entry_t combo_tab   = {{_LALT, _LSFT, KC_NO, KC_NO}, KC_TAB};

    dynamic_keymap_set_combo(0, &combo_enter);
    dynamic_keymap_set_combo(1, &combo_tab);
#endif

    // Customise these values to desired behaviour
    debug_enable = true;
    // debug_matrix   = true;
    debug_keyboard = true;
    // debug_mouse=true;
}

void oneshot_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        println("Oneshot mods SHIFT");
    }
    if (mods & MOD_MASK_CTRL) {
        println("Oneshot mods CTRL");
    }
    if (mods & MOD_MASK_ALT) {
        println("Oneshot mods ALT");
    }
    if (mods & MOD_MASK_GUI) {
        println("Oneshot mods GUI");
    }
    if (!mods) {
        println("Oneshot mods off");
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t current_layer = get_highest_layer(layer_state);

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
        case APP_NXT:
        case APP_PRV:
            // Only accept while on layer NAV
            if (current_layer == _NAV || isSwappingApps) {
                if (record->event.pressed) {
                    isSwappingApps = true;

                    register_code(isOnMac ? KC_LGUI : KC_LALT);
                    if (keycode == APP_PRV) {
                        register_code(KC_LSFT);
                    }
                    tap_code(KC_TAB);
                    if (keycode == APP_PRV) {
                        unregister_code(KC_LSFT);
                    }
                } else {
                    unregister_code(KC_TAB);
                }
                return true;
            }
            return false;
        case NAV_L:
            if (!record->event.pressed && isSwappingApps) {
                isSwappingApps = false;
                unregister_code(isOnMac ? KC_LGUI : KC_LALT);
                unregister_code(KC_TAB);
            }
            return true;
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
        case SYM_L:
            dprintf("TAP_ALT: %d, now: %d\n", record->event.pressed, record->event.time);
            if (record->tap.count > 0) {
                dprintf("tap.count = %d\n", record->tap.count);
                if (record->event.pressed) {
                    dprint("set oneshot!\n");
                    set_oneshot_mods(MOD_BIT(KC_ALGR));
                } else {
                }
                return false;
            }
            break;
        case NUM_L:
            return tap_num_layers(record);
        case NUMPD_L:
            if (record->event.pressed) {
                switch_num_layers();
            }
            return true;
        default:
            return true; // Process all other keycodes normally
    }

    return true;
}
