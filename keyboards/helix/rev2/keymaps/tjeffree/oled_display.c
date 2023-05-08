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

enum layer_number {
    _QWERTY = 0,
    _FUNC,
    _CODE,
    _LAST,
    _OS
};

//OLED update loop
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
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

void user_sync_a_update_keyCntr_on_other_board(uint8_t in_buflen, const void* in_data, uint8_t
        out_buflen, void* out_data) { keyCntr = *((const uint16_t *)in_data); }

void keyboard_post_init_user(void) {
#ifdef OLED_ENABLE
    transaction_register_rpc(USER_SYNC_KEY_CNTR, user_sync_a_update_keyCntr_on_other_board);
#endif
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
        case _FUNC:
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
        case _FUNC:
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
