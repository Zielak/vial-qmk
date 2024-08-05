#include "zielak.h"

void my_custom_function(void) {}

// App swapping and Print screen are different on Mac...
static uint16_t ctrlKey        = KC_LGUI;
static bool     isOnMac        = true;
static bool     isSwappingApps = false;

// static bool     numActive    = false;
// static bool     numLocked    = false;
// static uint16_t numLayer     = _NUM;
// static uint16_t numTimestamp = 0;
// static uint16_t numTapCount  = 0;

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
                unregister_code(KC_LGUI);
                unregister_code(KC_LSFT);
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
        case K_QUIT:
            if (record->event.pressed) {
                if (isOnMac) {
                    register_code(KC_LGUI);
                    tap_code(KC_Q);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LALT);
                    tap_code(KC_F4);
                    unregister_code(KC_LALT);
                }
            } else {
                if (isOnMac) {
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LALT);
                }
            }
            return false;
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
