/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "print.h"
#include QMK_KEYBOARD_H

// Aliases to make keymap more readable
#define FNK_L MO(_FNK)
#define NAV_L MO(_NAV)
#define NUM_L TT(_NUM)
// #define NUMPD_L TG(_NUM_PAD)
// #define TAP_ALT KC_F18
// #define SYM_L LT(_SYM, KC_F18)

#include "zielak.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off
    [_COLEMAKDH] = LAYOUT_split_4x6_5(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,               KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        //-------------------------------------------------//-----------------------------------------------------------//
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B,               KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_MINS,
        //-------------------------------------------------//-----------------------------------------------------------//
        KC_LGUI, KC_A, KC_R, KC_S, KC_T, KC_G,              KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
        //-------------------------------------------------//-----------------------------------------------------------//
        KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V,               KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
        //-------------------------------------------------//-----------------------------------------------------------//
                NAV_L, KC_SPC, KC_ENT,                          KC_RALT, KC_RSFT, NUM_L,
                        FNK_L, KC_LGUI,                         KC_RCTL, KC_DEL
    ),
    [_QWERTY] = LAYOUT_split_4x6_5(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,               KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        //-------------------------------------------------//-----------------------------------------------------------//
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,               KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS,
        //-------------------------------------------------//-----------------------------------------------------------//
        KC_LGUI, KC_A, KC_S, KC_D, KC_F, KC_G,              KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        //-------------------------------------------------//-----------------------------------------------------------//
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,              KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
        //-------------------------------------------------//-----------------------------------------------------------//
                NAV_L, KC_SPC, KC_ENT,                          KC_RALT, KC_RSFT, NUM_L,
                        FNK_L, KC_LGUI,                         KC_RCTL, KC_DEL
    ),
    [_NAV] = LAYOUT_split_4x6_5(
        _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        //---------------------------------------------------------//-------------------------------------------------------//
        _______, K_TERMI ,APP_PRV ,APP_NXT ,KC_PSCR ,XXXXXXX,       KC_PGUP ,KC_HOME ,KC_UP   ,KC_END,  XXXXXXX, XXXXXXX,
        //---------------------------------------------------------//-------------------------------------------------------//
        _______, KC_LCTL ,KC_LALT ,KC_LSFT ,KC_LGUI ,XXXXXXX,       KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RIGHT,XXXXXXX, XXXXXXX,
        //---------------------------------------------------------//-------------------------------------------------------//
        _______, K_UNDO  ,K_CUT   ,K_COPY  ,K_PASTE ,K_REDO,        XXXXXXX ,XXXXXXX ,K_INDEL ,K_INDER ,KC_INS , XXXXXXX,
        //---------------------------------------------------------//-------------------------------------------------------//
                _ENTRY_, XXXXXXX, XXXXXXX,                  _______, _______, _______,
                         XXXXXXX, XXXXXXX,                  _______, _______
    ),
    [_NUM] = LAYOUT_split_4x6_5(
        XXXXXXX, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        //---------------------------------------------------------//-------------------------------------------------------//
        XXXXXXX, KC_QUES ,KC_CIRC ,K_ARROW ,KC_PPLS ,KC_AMPR,       KC_LNUM, KC_P7, KC_P8, KC_P9, KC_COLN, KC_UNDS,
        //---------------------------------------------------------//-------------------------------------------------------//
        KC_EXLM, KC_AT   ,KC_DLR  ,KC_UNDS ,KC_PMNS ,KC_EQL ,       KC_PENT, KC_P4, KC_P5, KC_P6, XXXXXXX, KC_GRV ,
        //---------------------------------------------------------//-------------------------------------------------------//
        XXXXXXX, KC_TILD ,KC_HASH ,KC_PSLS ,KC_PAST, KC_PIPE,       KC_PDOT, KC_P1, KC_P2, KC_P3, KC_P0  , XXXXXXX,
        //---------------------------------------------------------//-------------------------------------------------------//
                _______, _______, _______,                  XXXXXXX, XXXXXXX, _ENTRY_,
                         _______, _______,                  XXXXXXX, XXXXXXX
        ),
    [_FNK] = LAYOUT_split_4x6_5(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        //---------------------------------------------------------//-------------------------------------------------------//
        _______, KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,XXXXXXX,       GU_TOGG, XXXXXXX, KC_BRID ,KC_BRIU ,DT_UP  , XXXXXXX,
        //---------------------------------------------------------//-------------------------------------------------------//
        _______, KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,XXXXXXX,       CG_NORM ,KC_MUTE ,KC_VOLD ,KC_VOLU ,DT_DOWN, XXXXXXX,
        //---------------------------------------------------------//-------------------------------------------------------//
        _______, KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX,       CG_SWAP ,KC_MPLY ,KC_MPRV ,KC_MNXT ,DT_PRNT, XXXXXXX,
        //---------------------------------------------------------//-------------------------------------------------------//
                XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_LCAP ,XXXXXXX,
                         _ENTRY_, XXXXXXX,                   DF_QWER, DF_COLE
    ),

    // clang-format on
};
