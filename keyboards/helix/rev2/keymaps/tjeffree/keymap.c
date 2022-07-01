/* Copyright 2020 yushakobo
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

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _FUNCTION,
    _CODE,
    _LAST,
    _OS
};

enum custom_keycodes {
  PHP_OP = SAFE_RANGE,
  PHP_CL,
  PHP_SH, // Short php tag open
  OS_SWAP,
  OS_SWAP_PC,
  OS_SWAP_MAC,
  ARROW_LEFT,
  ARROW_RGHT,
};

#define FN MO(_FUNCTION)
#define CD MO(_CODE)
#define LST MO(_LAST)
#define MRSFT MT(MOD_RSFT, KC_ENT)
#define OS_SWP MO(_OS)
#define LSLSH LSFT_T(KC_NUBS)
#define LBRKT LSFT(KC_9)
#define RBRKT LSFT(KC_0)

const uint16_t PROGMEM combo_minus[] = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM combo_plus[] = {KC_0, KC_BSPC, COMBO_END};

const uint16_t PROGMEM combo_home[] = {KC_BSPC, KC_DEL, COMBO_END};
const uint16_t PROGMEM combo_end[] = {MRSFT, KC_RGHT, COMBO_END};

const uint16_t PROGMEM combo_pgup[] = {KC_DEL, KC_QUOT, COMBO_END};
const uint16_t PROGMEM combo_pgdn[] = {KC_QUOT, MRSFT, COMBO_END};

const uint16_t PROGMEM combo_bksl[] = {LSLSH, KC_Z, COMBO_END};
const uint16_t PROGMEM combo_hash[] = {KC_SCLN, KC_QUOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_minus, KC_MINS),
    COMBO(combo_plus, KC_EQL),

    COMBO(combo_home, KC_HOME),
    COMBO(combo_end, KC_END),

    COMBO(combo_pgup, KC_PGUP),
    COMBO(combo_pgdn, KC_PGDN),

    COMBO(combo_bksl, KC_NUBS),
    COMBO(combo_hash, KC_NUHS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty                                                                | - |  | = |
 * ,-----------------------------------------.             ,-----------------------------------------.
 * | Esc  |  1   |  2   |  3   |  4   |  5   |             |  6   |  7   |  8   |  9   |  0   | BkSp |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------| Home
 * | Tab  |  Q   |  W   |  E   |  R   |  T   |             |  Y   |  U   |  I   |  O   |  P   | Del  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------| PgUp
 * | Caps |  A   |  S   |  D   |  F   |  G   |             |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------| PgDn
 * | Shft /  Z   |  X   |  C   |  V   |  B   |  [   |   ]  |  N   |  M   |  ,   |  .   |  /   | Entr |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------| End
 * | Ctrl |  Fn  | Gui  | Alt  | Code | Spac |      |      | Spac |  Fn  | Left | Down |  Up  | Rght |
 * `-------------------------------------------------------------------------------------------------'
 */
  [_QWERTY] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      LSLSH,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MRSFT ,
      KC_LCTL, OS_SWP,  KC_LGUI, KC_LALT, CD,      KC_SPC,  KC_MINS, KC_EQL,  KC_SPC,  FN,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
      ),

/* Func
* ,------------------------------------------.             ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |      |      |  (   |      |             |      |   )  | Ins  |   [  |   ]  | Del  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      | VOL- | VOL+ | MUTE |  {   |      |             |      |   }  |      |      |      |  #   |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------|
 * |      |  \   |      |      |  [   |      |      |      |      |   ]  |      |      |      |      |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-------------------------------------------------------------------------------------------------'
 */
  [_FUNCTION] = LAYOUT(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      _______, _______, _______, _______, LBRKT,   _______,                   _______, RBRKT  , KC_INS , KC_LBRC, KC_RBRC, KC_DEL,
      _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_LCBR, _______,                   _______, KC_RCBR, _______, _______, _______, KC_NUHS,
      _______, KC_NUBS, _______, _______, KC_LBRC, _______, KC_LCBR, KC_RCBR, _______, KC_RBRC, _______, _______, _______, _______,
      _______, LST,     _______, _______, LST,     _______, _______, _______, _______, LST,     KC_HOME, KC_PGDN, KC_PGUP, KC_END
      ),

/* Code
* ,------------------------------------------.             ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |   -  |   =  | Bksp |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |      |      |  (   |      |             |      |   )  | Ins  |   [  |   ]  | Del  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      | VOL+ | VOL- | MUTE |  {   |      |             |      |   }  |      |      |      |  #   |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------|
 * |      |  \   |      |      |  [   |      |      |      |      |   ]  |PHP OP|PHP CL|PHP SH|      |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | <-   | PgDn | PgUp |  ->  |
 * `-------------------------------------------------------------------------------------------------'
 */
  [_CODE] = LAYOUT(
      KC_GRV , KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_MINS, KC_EQL,  KC_BSPC,
      _______, _______, _______, _______, LBRKT,   _______,                   _______, RBRKT  , KC_INS , KC_LBRC, KC_RBRC, KC_DEL,
      _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_LCBR, _______,                   _______, KC_RCBR, _______, _______, _______, KC_NUHS,
      _______, KC_NUBS, _______, _______, KC_LBRC, _______, KC_LCBR, KC_RCBR, _______, KC_RBRC, PHP_OP , PHP_CL , PHP_SH , _______,
      _______, LST,     _______, _______, LST,     _______, _______, _______, _______, LST,     ARROW_LEFT, KC_PGDN, KC_PGUP, ARROW_RGHT
      ),

/* Last / OS
* ,------------------------------------------.             ,-----------------------------------------.
 * |      |      |      |      |      |      |             |      |      |      |      |      |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |      |      |      |      |             |      |      |      |      |      |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |SLEEP |      |      |      |             |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------|
 * |RESET |      |      |      |      |  OS  |      |      |  OS  |      | MAC  |      |      |  PC  |
 * `-------------------------------------------------------------------------------------------------'
 */
  [_LAST] =  LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, KC_SLEP, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
      ),

  [_OS] =  LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, OS_SWAP, _______, _______, OS_SWAP, _______, OS_SWAP_MAC, _______, _______, OS_SWAP_PC
      )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

        // PHP macros
        case PHP_OP:
            if (record->event.pressed) {
                SEND_STRING("<?php");
            }
            break;
        case PHP_CL:
            if (record->event.pressed) {
                SEND_STRING("?>");
            }
            break;
        case PHP_SH:
            if (record->event.pressed) {
                SEND_STRING("<?=");
            }
            break;

        // OS swapping
        case OS_SWAP:
            if (record->event.pressed) {
                keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
            }
            break;

        case OS_SWAP_MAC:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_LEFT));
                keymap_config.swap_lctl_lgui = true;
            }
            break;

        case OS_SWAP_PC:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_RGHT));
                keymap_config.swap_lctl_lgui = false;
            }
            break;

        // Code stuff
        case ARROW_LEFT:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {  // Is shift held?
                    del_mods(MOD_MASK_SHIFT);  // Temporarily delete shift.
                    SEND_STRING("<=");
                } else {
                    SEND_STRING("<-");
                }
            }
            break;
        case ARROW_RGHT:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {  // Is shift held?
                    del_mods(MOD_MASK_SHIFT);  // Temporarily delete shift.
                    SEND_STRING("=>");
                } else {
                    SEND_STRING("->");
                }
            }
            break;

    }
  return true;
}

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

void matrix_init_user(void) {
    // Set to PC/Windows by default
    keymap_config.swap_lctl_lgui = false;

    #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

void suspend_power_down_user(void) {
    oled_off();
}
