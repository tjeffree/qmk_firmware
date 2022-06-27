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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _FUNC,
    _CODE,
    _LAST,
    _OS
};

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_FUNC (1<<_FUNC)
#define L_CODE (1<<_CODE)
#define L_LAST (1<<_LAST)
#define L_OS (1<<_OS)

//OLED update loop
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
}
/*
static void render_rgbled_status(bool full) {
#    ifdef RGBLIGHT_ENABLE
    char buf[30];
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        if (full) {
            snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                     rgblight_get_mode(),
                     rgblight_get_hue()/RGBLIGHT_HUE_STEP,
                     rgblight_get_sat()/RGBLIGHT_SAT_STEP,
                     rgblight_get_val()/RGBLIGHT_VAL_STEP);
        } else {
            snprintf(buf, sizeof(buf), "[%2d] ", rgblight_get_mode());
        }
        oled_write(buf, false);
    }
#    endif
}
*/
static void render_layer_status(void) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below

    oled_set_cursor(0, 5);
    oled_write_P(PSTR("LAYER "), false);
    oled_set_cursor(0, 6);

    // switch (layer_state) {
    // case L_BASE:
    //     oled_write_P(PSTR("Base "), false);
    //     break;
    // case L_CODE:
    //     oled_write_P(PSTR("Code "), false);
    //     break;
    // case L_FUNC:
    //     oled_write_P(PSTR("Func "), false);
    //     break;
    // case L_LAST:
    //     oled_write_P(PSTR("Last "), false);
    //     break;
    // case L_OS:
    //     oled_write_P(PSTR("OS   "), false);
    //     break;
    // default:
    //     oled_write_P(PSTR("Undef"), false);
    //     break;
    // }
    // oled_write_P(PSTR("\n"), false);

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

// static const char PROGMEM keeb_logo[] = {
//     0,254,228, 12,248, 16,240, 32,224, 64,192, 64,128,128,  0,  0,  0,  0,128,128, 64,192, 96,160, 48,208, 24,232,  4,228,254,  0,  0,255,159,128, 95, 96, 47, 48, 23, 24, 15,  8,  7,  4,  3,  1,  2,  3,  4,  7,  8, 15,  8, 31, 16, 63, 32,127,128,159,255,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0
// };

void render_status(void) {
  // Render to mode icon
    // static const char os_logo[][2][3] PROGMEM = {{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
    oled_set_cursor(0, 1);
    if (keymap_config.swap_lctl_lgui) {
        // oled_write_P(os_logo[0][0], false);
        // oled_write_P(PSTR("\n"), false);
        // oled_write_P(os_logo[0][1], false);
        oled_write_raw_P(mac_logo, sizeof(mac_logo));
    } else {
        // oled_write_P(os_logo[1][0], false);
        // oled_write_P(PSTR("\n"), false);
        // oled_write_P(os_logo[1][1], false);
        oled_write_raw_P(windows_logo, sizeof(windows_logo));
    }

    // oled_write_P(PSTR(" "), false);
    render_layer_status();

    oled_set_cursor(0, 8);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    //oled_write_P(led_state.num_lock ? PSTR("NUMLOCK") : PSTR("       "), false);
    oled_write_P(PSTR("CAPS"), led_state.caps_lock);
    //oled_write_P(led_state.scroll_lock ? PSTR("SCLK") : PSTR("    "), false);

    oled_set_cursor(0, 10);
    oled_write_raw_P(keeb_logo, sizeof(keeb_logo));

    oled_advance_page(true);
    //render_rgbled_status(true);
    // oled_write_P(PSTR("\n"), false);

}

void render_helix_logo(void) {
    static const char helix_logo[] PROGMEM ={
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
        0};
    oled_write_P(helix_logo, false);
}

bool oled_task_user(void) {

#        if DEBUG_TO_SCREEN
    if (debug_enable) {
        return;
    }
#        endif

    if (is_keyboard_master()) {
        render_status();
    } else {
        render_helix_logo();
        //render_rgbled_status(false);
        render_layer_status();
    }
    return false;
}
#endif // end of OLED_ENABLE

//SSD1306 OLED update loop
/*
    The following code is left as a sample to help you transition from SSD1306OLED to OLED_ENABLE.

    * `matrix_write(matrix, data)` is replaced by `oled_write(data, false)`.
    * `matrix_write_P(matrix, data)` is replaced by `oled_write_P(data, false)`.
    * It is no longer necessary to call `iota_gfx_task()`.
    * `matrix_update()` are no longer needed.
    * `iota_gfx_task_user()` is no longer needed. Instead, `bool oled_task_user(void)` is provided.

    以下のコードは、SSD1306OLED から OLED_ENABLE に移行する助けになるようにサンプルとして残してあります。

    * `matrix_write(matrix, data)` は、`oled_write(data, false)` に書き換えます。
    * `matrix_write_P(matrix, data)` は、`oled_write_P(data, false)` に書き換えます。
    * `iota_gfx_task()` を呼び出す必要はなくなります。
    * `matrix_update()` は不要になります。
    * `iota_gfx_task_user()` は不要になります。代りに `bool oled_task_user(void)` を用意します。
 */

#ifdef SSD1306OLED
#include "ssd1306.h"
#define oled_write(data,flag)    matrix_write(matrix, data)
#define oled_write_P(data,flag)  matrix_write_P(matrix, data)

void matrix_scan_user(void) {
    iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                   const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

static void render_logo(struct CharacterMatrix *matrix) {

    static const char helix_logo[] PROGMEM ={
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
        0};
    oled_write_P(helix_logo, false);
}

// static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
// #    ifdef RGBLIGHT_ENABLE
//     char buf[30];
//     if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
//         if (full) {
//             snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
//                      rgblight_get_mode(),
//                      rgblight_get_hue()/RGBLIGHT_HUE_STEP,
//                      rgblight_get_sat()/RGBLIGHT_SAT_STEP,
//                      rgblight_get_val()/RGBLIGHT_VAL_STEP);
//         } else {
//             snprintf(buf, sizeof(buf), "[%2d] ", rgblight_get_mode());
//         }
//         oled_write(buf, false);
//     }
// #    endif
// }

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below

    // oled_write_P(PSTR("Layer: "), false);
    // switch (layer_state) {
    // case L_BASE:
    //     oled_write_P(PSTR("Base "), false);
    //     break;
    // case L_CODE:
    //     oled_write_P(PSTR("Code "), false);
    //     break;
    // case L_FUNC:
    //     oled_write_P(PSTR("Func "), false);
    //     break;
    // case L_LAST:
    //     oled_write_P(PSTR("Last "), false);
    //     break;
    // case L_OS:
    //     oled_write_P(PSTR("OS   "), false);
    //     break;
    // default:
    //     oled_write_P(PSTR("Undef"), false);
    //     break;
    // }
    // oled_write_P(PSTR("\n"), false);

    oled_write_P(PSTR("Layer: "), false);
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

void render_status(struct CharacterMatrix *matrix) {
  // Render to mode icon
    static const char os_logo[][2][3] PROGMEM = {{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(os_logo[0][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[0][1], false);
    } else {
        oled_write_P(os_logo[1][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[1][1], false);
    }

    oled_write_P(PSTR(" "), false);
    render_layer_status(matrix);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    //oled_write_P(led_state.num_lock ? PSTR("NUMLOCK") : PSTR("       "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
    //oled_write_P(led_state.scroll_lock ? PSTR("SCLK") : PSTR("    "), false);
    oled_write_P(PSTR("\n"), false);
    //render_rgbled_status(true, matrix);
}

#    if OLED_UPDATE_INTERVAL > 0
uint16_t oled_update_timeout;
#    endif

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;

#    if DEBUG_TO_SCREEN
    if (debug_enable) {
        return;
    }
#    endif

#    if OLED_UPDATE_INTERVAL > 0
    if (timer_elapsed(oled_update_timeout) < OLED_UPDATE_INTERVAL) {
        return;
    }
    oled_update_timeout = timer_read();
#    endif
    matrix_clear(&matrix);
    if (is_keyboard_master()) {
        render_status(&matrix);
    } else {
        render_logo(&matrix);
        //render_rgbled_status(false, &matrix);
        render_layer_status(&matrix);
    }
    matrix_update(&display, &matrix);
}

#endif // end of SSD1306OLED
