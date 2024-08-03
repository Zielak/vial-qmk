// Copyright 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define VIAL_KEYBOARD_UID \
    { 0x5C, 0xD1, 0x02, 0x5A, 0x42, 0x02, 0x9E, 0x28 }
#define VIAL_UNLOCK_COMBO_ROWS \
    { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS \
    { 0, 0 }

#ifdef VIAL_ENABLE
// number of combos used, each entry take 10 byte in EEPROM
#    define VIAL_COMBO_ENTRIES 5
#endif
#ifndef VIAL_ENABLE
#    define COMBO_COUNT 2
#    define COMBO_STRICT_TIMER
#endif

#define TAPPING_TERM 150
#undef HOLD_ON_OTHER_KEY_PRESS
#define TAPPING_TOGGLE 2

#define COMBO_STRICT_TIMER
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 7

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 7

#undef RGBLIGHT_MODE_SNAKE
#undef RGBLIGHT_MODE_KNIGHT
#undef RGBLIGHT_MODE_CHRISTMAS
#undef RGBLIGHT_MODE_STATIC_GRADIENT
#undef RGBLIGHT_MODE_ALTERNATING
#undef RGBLIGHT_MODE_TWINKLE

// ---
#define BLUE_LED_PIN GP17
// #define WS2812_DI_PIN GP25
// #define NEXT_LED_PIN GP16

#define blu_led_on writePinHigh(BLUE_LED_PIN)
#define blu_led_off writePinLow(BLUE_LED_PIN)

// #define next_led_on writePinHigh(NEXT_LED_PIN)
// #define next_led_off writePinLow(NEXT_LED_PIN)
