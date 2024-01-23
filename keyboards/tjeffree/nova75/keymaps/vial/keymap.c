#include "nova75.h"

enum layers {
  _QWERTY = 0,
  _FUNCTION,
  _LAST
};

#define FN MO(_FUNCTION)
#define LST MO(_LAST)
#define MRSFT MT(MOD_RSFT, KC_ENT)
#define LSLSH LSFT_T(KC_NUBS)
#define RCTLT RCTL_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty                                                                                   | - |  | = |
 * ,-------------------------------------------------------+------------------------------------------------.
 * | Esc  |  1   |  2   |  3   |  4   |  5   | PgUp | F12  | Home |  6   |  7   |  8   |  9   |  0   | BkSp |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------| Home
 * | Tab  |  Q   |  W   |  E   |  R   |  T   | PgDn | Ins  | End  |  Y   |  U   |  I   |  O   |  P   | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------| PgUp
 * | Caps |  A   |  S   |  D   |  F   |  G   | Prnt | `    | Paus |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------| PgDn
 * | Shft /  Z   |  X   |  C   |  V   |  B   |  [   | Up   |   ]  |  N   |  M   |  ,   |  .   |  /   | Entr |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------| End
 * | Ctrl |  Fn  | Gui  | Alt  | Code | Spac | Left | Down | Rght | Spac |  Fn  | Left | Down | Up   | Rght |
 * `-------------------------------------------------------+------------------------------------------------'
 */
	[_QWERTY] = LAYOUT_ortho_5x15(
      KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PGUP, KC_F12 , KC_HOME, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_PGDN, KC_INS , KC_END , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
      KC_CAPS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PSCR, KC_GRV , KC_PAUS, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      LSLSH,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_UP  , KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MRSFT ,
      KC_LCTL,   KC_LGUI, KC_LGUI, KC_LALT, FN,      KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, RCTLT,   FN,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

	[_FUNCTION] = LAYOUT_ortho_5x15(
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6  , KC_TRNS, KC_TRNS, KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 ,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_NUBS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LST,     KC_TRNS, KC_TRNS, LST,     KC_TRNS, KC_TRNS, LST,     KC_HOME, KC_PGDN, KC_PGUP, KC_END
        ),

	[_LAST] = LAYOUT_ortho_5x15(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_SLEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, LST,     KC_TRNS, KC_TRNS, LST,     KC_TRNS, KC_TRNS, LST,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        )

};

void matrix_init_user(void) {
    // Set to PC/Windows by default
    keymap_config.swap_lctl_lgui = false;
}
