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

#include <stdio.h>
#include <string.h>
#include QMK_KEYBOARD_H
#include "transactions.h"

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
#define RGUIT RGUI_T(KC_SPC)
#define RCTLT RCTL_T(KC_SPC)
#define CAP_CTRL RCTL_T(KC_CAPS)

const uint16_t PROGMEM combo_minus[] = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM combo_plus[] = {KC_0, KC_BSPC, COMBO_END};

const uint16_t PROGMEM combo_lbrkt[] = {KC_6,    KC_7, COMBO_END};
const uint16_t PROGMEM combo_rbrkt[] = {KC_7,    KC_8, COMBO_END};

const uint16_t PROGMEM combo_lsqbrkt[] = {KC_3,    KC_4, COMBO_END};
const uint16_t PROGMEM combo_rsqbrkt[] = {KC_4,    KC_5, COMBO_END};

const uint16_t PROGMEM combo_home[] = {KC_BSPC, KC_DEL, COMBO_END};
const uint16_t PROGMEM combo_end[] = {KC_RSFT, KC_RGHT, COMBO_END};

const uint16_t PROGMEM combo_pgup[] = {KC_DEL, KC_QUOT, COMBO_END};
const uint16_t PROGMEM combo_pgdn[] = {KC_QUOT, KC_RSFT, COMBO_END};

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

    COMBO(combo_lbrkt, KC_LCBR),
    COMBO(combo_rbrkt, KC_RCBR),

    COMBO(combo_lsqbrkt, KC_LBRC),
    COMBO(combo_rsqbrkt, KC_RBRC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty                                                                            | - |  | = |
 * ,-----------------------------------------.             ,-----------------------------------------.
 * | Esc  |  1   |  2   |  3   [  4   ]  5   |             |  6   {  7   }  8   |  9   |  0   | BkSp |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------| Home
 * | Tab  |  Q   [  W   ]  E   |  R   |  T   |             |  Y   |  U   |  I   {  O   }  P   | Del  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------| PgUp
 * | Caps |  A   |  S   |  D   |  F   |  G   |             |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------| PgDn
 * | Shft /  Z   |  X   |  C   |  V   |  B   |  [   |   ]  |  N   |  M   |  ,   |  .   |  /   | Entr |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------| End
 * | Ctrl |  Fn  | Gui  | Alt  | Code | Spac |      |      | Spac |  Fn  | Left | Down |  Up  | Rght |
 * `-------------------------------------------------------------------------------------------------'
 */
  [_QWERTY] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
      CAP_CTRL,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      LSLSH,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
      KC_LCTL, OS_SWP,  KC_LGUI, KC_LALT, CD,      KC_SPC, KC_SPC , KC_ENT , KC_ENT,  FN,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
      ),

/* Func
* ,------------------------------------------.             ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |      |      |  (   |      |             |      |   )  | Ins  |   [  |   ]  | Home |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      | VOL- | VOL+ | MUTE |  {   |      |             |      |   }  |      |      |      | PgUp |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------|
 * |      |  \   |      |      |  [   |      |      |      |      |   ]  |      |      |      | PgDn |
 * |------+------+------+------+------+------|------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-------------------------------------------------------------------------------------------------'
 */
  [_FUNCTION] = LAYOUT(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      _______, _______, _______, _______, LBRKT,   _______,                   _______, RBRKT  , KC_INS , KC_LBRC, KC_RBRC, KC_HOME,
      _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_LCBR, _______,                   _______, KC_RCBR, _______, _______, _______, KC_PGUP,
      _______, KC_NUBS, _______, _______, KC_LBRC, _______, KC_LCBR, KC_RCBR, _______, KC_RBRC, PHP_OP , PHP_CL , PHP_SH,  KC_PGDN,
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


//OLED update loop
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    // } else {
    //     return OLED_ROTATION_180;
    // }
}

/// SUGAR STUFF

uint16_t keyCntr = 0;
#define OLED_SUGAR_HEIGHT 128
#define OLED_SUGAR_WIDTH  32

bool pixelInvert = false;
void setPixel(char * pixels, uint8_t h, uint8_t w, bool pix) {
//    oled_write_pixel(w, h, pix);
    uint16_t byteIdx = w + (h/8)*OLED_SUGAR_WIDTH;
    int8_t byteMask = 1<<(h%8);
    if(pixelInvert) pix = !pix;
    if(pix) {
        pixels[byteIdx] |= byteMask;
    } else {
        pixels[byteIdx] &= ~byteMask;
    }
}

bool getPixel(char * pixels, uint8_t h, uint8_t w) {
    uint16_t byteIdx = w + (h/8)*OLED_SUGAR_WIDTH;
    int8_t byteMask = 1<<(h%8);
    bool pix =  (pixels[byteIdx] & byteMask) != 0;
    if(pixelInvert) pix = !pix;
    return pix;
}

uint32_t rand_basic(void) {
    static uint32_t seed = 0;
    seed = 1664525*seed + 1013904223;
    return seed;
}

#define OLED_SUGAR_WITH_DOWN 1

#define OLED_SUGAR_PIXELS (OLED_SUGAR_HEIGHT*OLED_SUGAR_WIDTH)
#define OLED_SUGAR_BYTES (OLED_SUGAR_PIXELS/8)
typedef signed char lineIdx_t;
lineIdx_t* activeSugar = NULL;

char* pixels = NULL;


void oled_sugar(void) {
    //return;

    if (activeSugar == NULL) {
        activeSugar = malloc(OLED_SUGAR_HEIGHT);
        if (activeSugar != NULL) {
            memset( activeSugar, -1, OLED_SUGAR_HEIGHT );
        } else {
#ifdef PRINT_DB
            uprintf("activeSugar %X failed to inialise\n", activeSugar);
#endif
            return;
        }
    }

    if (pixels == NULL) {
        pixels = malloc(OLED_SUGAR_BYTES);
        if (pixels != NULL) {
            memset( pixels, 0, OLED_SUGAR_BYTES );
        } else {
#ifdef PRINT_DB
            uprintf("pixels %X failed to inialise\n", pixels);
#endif
            return;
        }

    }

    static uint8_t sugarCntr = 0;

   for(int16_t h = OLED_SUGAR_HEIGHT-2; h >= 0; h--) {
        lineIdx_t w = activeSugar[h];

        if(w < 0 || w >= OLED_SUGAR_WIDTH) {
            continue;
        }
        lineIdx_t wn = -1;
        bool left;
        bool right;
#ifdef OLED_SUGAR_WITH_DOWN
        uint32_t r = rand_basic();
        const uint32_t thresh1 = UINT32_MAX/3;
        const uint32_t thresh2 = UINT32_MAX-thresh1;
        left  = r < thresh1;
        right = r > thresh2;
#else
        left = ((int32_t) rand_basic())<0;
        right = !left;
#endif
        if ( left ) {
            if( w > 0 ) {
                if(!getPixel(pixels, h+1, w-1)) {
                    wn = w - 1;
                }
            }
        } else if (right) {
            if ( w < OLED_SUGAR_WIDTH-1) {
                if(!getPixel(pixels, h+1, w+1)) {
                    wn = w + 1;
                }
            }
        } else { //centre
            if(!getPixel(pixels, h+1, w)) {
                wn = w ;
            }
        }
        if(wn == -1) {
            if(!getPixel(pixels, h+1, w)) {
                wn = w;
            }
        }
        if(wn != -1) {
            setPixel(pixels, h+1, wn, true);
            activeSugar[h+1] = wn;
            setPixel(pixels, h, w, false);
        }

        activeSugar[h] = -1;
    }
    if(sugarCntr != (keyCntr&0xFF)) {

        sugarCntr++;
        lineIdx_t w = OLED_SUGAR_WIDTH/2;
        bool left = false;
        if( ((int32_t) rand_basic())<0 ) {
            w--;
            left = true;
        }
        bool full = false;
        while(getPixel(pixels,0, w)) {
            if(left) {
                if (w == 0) {
                    w = OLED_SUGAR_WIDTH-1;
                } else if ( w == OLED_SUGAR_WIDTH/2) {
                    full = true;
                    break;
                } else {
                    w--;
                }
            } else {
                if (w == OLED_SUGAR_WIDTH-1) {
                    w = 0;
                } else if ( w == OLED_SUGAR_WIDTH/2-1) {
                    full = true;
                    break;
                } else {
                    w++;
                }
            }
        }

        if(!full) {
//        if(!getPixel(pixels, 0, w)) {
            setPixel(pixels, 0, w, true);
            activeSugar[0] = w;
        } else {
            pixelInvert = !pixelInvert;
            // we where not able to add a pixel (we where full so add one now that we have inverted)
            sugarCntr--;
            oled_sugar();
        }
    }
    rand_basic(); //just here to rotate the seed
    if(!is_oled_on()) {
        //OLED timedout so we will clear everything and start fresh
        memset( pixels, 0, OLED_SUGAR_BYTES );
        memset( activeSugar, -1, OLED_SUGAR_HEIGHT );
        oled_clear();
        pixelInvert = false;
    } else {
        oled_write_raw(pixels, OLED_SUGAR_BYTES);
    }

}

/// /SUGAR STUFF

static void render_layer_status(void) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below

    oled_set_cursor(0, 5);
    oled_write_P(PSTR("LAYER "), false);
    oled_set_cursor(0, 6);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base"), false);
            break;
        case _FUNCTION:
            oled_write_P(PSTR("Func "), false);
            break;
        case _CODE:
            oled_write_P(PSTR("Code "), false);
            break;
        case _OS:
            oled_write_P(PSTR("OS   "), false);
            break;
        case _LAST:
            oled_write_P(PSTR("Last "), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);
}

static const char PROGMEM windows_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xbc, 0xbe, 0xbe, 0x00, 0xbe, 0xbe, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const char PROGMEM mac_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf0, 0xf6, 0xfb, 0xfb, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const char PROGMEM keeb_logo[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,219,219,  0,219,219,  0,219,219,  0,219,219,  0,192,192,  0,  0,192,192,  0,219,219,  0,219,219,  0,219,219,  0,219,219,  0,  0,  6,  6,  0,  6,  6,  0,  6,  6,  0,  6,  6,  0,  6,  6,  0,  0,  6,  6,  0,  6,  6,  0,  6,  6,  0,  6,  6,  0,  6,  6,  0
};
static const char PROGMEM keeb_logo_func[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,147,  3,  0,211,195,  0,211,195,  0,211,195,  0,128,  0,  0,  0,128,  0,  0,211,195,  0,155, 27,  0,155, 27,  0,155, 27,  0,  0,  4,  0,  0,  4,  0,  0,  4,  0,  0,  4,  0,  0,  4,  0,  0,  0,  4,  0,  0,  6,  6,  0,  6,  6,  0,  6,  6,  0,  6,  6,  0,
};
static const char PROGMEM keeb_logo_os[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,146,  0,  0,146,  0,  0,146,  0,  0,146,  0,  0,128,  0,  0,  0,128,  0,  0,146,  0,  0,146,  0,  0,146,  0,  0,146,  0,  0,  0,  6,  6,  0,  4,  0,  0,  4,  0,  0,  6,  6,  0,  4,  0,  0,  0,  4,  0,  0,  6,  6,  0,  6,  6,  0,  4,  0,  0,  6,  6,  0,
};
static const char PROGMEM keeb_logo_last[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,146,  0,  0,210,192,  0,146,  0,  0,146,  0,  0,128,  0,  0,  0,128,  0,  0,146,  0,  0,146,  0,  0,146,  0,  0,146,  0,  0,  0,  6,  6,  0,  4,  0,  0,  4,  0,  0,  4,  0,  0,  4,  0,  0,  0,  4,  0,  0,  4,  0,  0,  4,  0,  0,  4,  0,  0,  4,  0,  0,
};

static void render_keeb_logo(void) {
    oled_set_cursor(0, 10);
    switch (get_highest_layer(layer_state)) {
        case _FUNCTION:
        case _CODE:
            oled_write_raw_P(keeb_logo_func, sizeof(keeb_logo_func));
            break;
        case _OS:
            oled_write_raw_P(keeb_logo_os, sizeof(keeb_logo_os));
            break;
        case _LAST:
            oled_write_raw_P(keeb_logo_last, sizeof(keeb_logo_last));
            break;
        case _QWERTY:
        default:
            oled_write_raw_P(keeb_logo, sizeof(keeb_logo));
    }

}

void render_status(void) {
    // Render to mode icon
    oled_set_cursor(0, 1);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_raw_P(mac_logo, sizeof(mac_logo));
    } else {
        oled_write_raw_P(windows_logo, sizeof(windows_logo));
    }

    // oled_write_P(PSTR(" "), false);
    render_layer_status();

    oled_set_cursor(0, 8);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("CAPS"), led_state.caps_lock);

    // Logo
    render_keeb_logo();

    oled_advance_page(true);

}

bool oled_task_user(void) {

    if (is_keyboard_master()) {
        render_status();
    } else {
        // render_helix_logo();
        // render_layer_status();
        oled_sugar();
    }
    return false;
}
#endif // end of OLED_ENABLE


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

#ifdef OLED_ENABLE
    keyCntr++;
    transaction_rpc_send(USER_SYNC_KEY_CNTR, sizeof(keyCntr), &keyCntr);
#endif

  return true;
}

void matrix_init_user(void) {
    // Set to PC/Windows by default
    keymap_config.swap_lctl_lgui = false;
}

void suspend_power_down_user(void) {
    oled_off();
}

void user_sync_a_update_keyCntr_on_other_board(uint8_t in_buflen, const void* in_data, uint8_t
        out_buflen, void* out_data) { keyCntr = *((const uint16_t *)in_data); }

void keyboard_post_init_user(void) {
#ifdef OLED_ENABLE
    transaction_register_rpc(USER_SYNC_KEY_CNTR, user_sync_a_update_keyCntr_on_other_board);
#endif
}
