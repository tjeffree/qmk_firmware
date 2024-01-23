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
        // oled_sugar();
    }
    return false;
}
#endif // end of OLED_ENABLE
