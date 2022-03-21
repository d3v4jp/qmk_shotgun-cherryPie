/// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    BASE = 0,
    LOWER,
    MIDDLE,
    UPPER,
    SETTING
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_ESC,       KC_KP_ASTERISK,  KC_KP_SLASH,  KC_BSPACE,
        KC_KP_PLUS,   KC_KP_7,         KC_KP_8,      KC_KP_9,
        KC_KP_MINUS,  KC_KP_4,         KC_KP_5,      KC_KP_6,
        MO(LOWER),    KC_KP_1,         KC_KP_2,      KC_KP_3,
        KC_NO,        KC_KP_0,         KC_KP_DOT,    LT(MIDDLE, KC_KP_ENTER),
        // ROTARY ENCODER
        KC_MS_WH_LEFT, KC_MS_WH_RIGHT,
        KC_NO, KC_NO,
        KC_NO, KC_NO,
        KC_NO, KC_NO,
        KC_MS_WH_DOWN, KC_MS_WH_UP
    ),
    [LOWER] = LAYOUT(
        XXXXXXX,     KC_F2,       KC_DELETE,   XXXXXXX,
        LCTL(KC_S),  LCTL(KC_C),  XXXXXXX,     LCTL(KC_V),
        XXXXXXX,     LCTL(KC_X),  LCTL(KC_A),  XXXXXXX,
        XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
        XXXXXXX,     XXXXXXX,     XXXXXXX,     OSL(UPPER),
        // ROTARY ENCODER
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX
    ),
    [MIDDLE] = LAYOUT(
        TO(SETTING), KC_TAB,     KC_SPACE,   KC_ESC,
        XXXXXXX,     KC_HOME,    KC_UP,      KC_PGUP,
        KC_BSPACE,   KC_LEFT,    KC_ENTER,   KC_RIGHT,
        OSL(UPPER),  KC_END,     KC_DOWN,    KC_PGDN,
        XXXXXXX,     KC_INSERT,  KC_DELETE,  XXXXXXX,
        // ROTARY ENCODER
        KC_RIGHT, KC_LEFT,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        KC_DOWN, KC_UP
    ),
    [UPPER] = LAYOUT(
        TO(SETTING), XXXXXXX, XXXXXXX, KC_NUMLOCK,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // ROTARY ENCODER
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX
    ),
    [SETTING] = LAYOUT(
        TO(BASE), RGB_MOD, RGB_RMOD, XXXXXXX,
        RGB_VAI, XXXXXXX, RGB_SAI, XXXXXXX,
        RGB_VAD, RGB_HUD, RGB_M_P, RGB_HUI,
        XXXXXXX, XXXXXXX, RGB_SAD, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
        // ROTARY ENCODERc
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX
    )
};

// ENCODER FOR VIA
bool encoder_update_user(uint8_t index, bool clockwise) {
  keypos_t key;
  if (index == 0) {
    if (clockwise) {
        key.row = 0;
        key.col = 4;
    } else {
        key.row = 0;
        key.col = 5;
    }
  } else if (index == 1){
    if (clockwise) {
        key.row = 1;
        key.col = 4;
    } else {
        key.row = 1;
        key.col = 5;
    }
  } else if (index == 2){
    if (clockwise) {
        key.row = 2;
        key.col = 4;
    } else {
        key.row = 2;
        key.col = 5;
    }
  } else if (index == 3){
    if (clockwise) {
        key.row = 3;
        key.col = 4;
    } else {
        key.row = 3;
        key.col = 5;
    }
  } else if (index == 4){
    if (clockwise) {
        key.row = 4;
        key.col = 4;
    } else {
        key.row = 4;
        key.col = 5;
    }
  }
  uint8_t  layer   = layer_switch_get_layer(key);
  uint16_t keycode = keymap_key_to_keycode(layer, key);
  tap_code16(keycode);
  return true;
}

void set_color_single(int index,uint8_t hsvred, uint8_t hsvgreen, uint8_t hsvblue) {
    HSV hsv = (HSV){hsvred, hsvgreen, hsvblue};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

void set_color_all(uint8_t hsvred, uint8_t hsvgreen, uint8_t hsvblue) {
    HSV hsv = (HSV){hsvred, hsvgreen, hsvblue};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case LOWER:
            set_color_all(HSV_RED);
            break;
        case MIDDLE:
            set_color_all(HSV_GREEN);
            break;
        case UPPER:
            set_color_all(HSV_BLUE);
            break;
        case SETTING:
            set_color_all(HSV_WHITE);
            break;
        default:
            rgb_matrix_set_color_all(RGB_OFF);
            set_color_single(13, HSV_WHITE);
            if (host_keyboard_led_state().num_lock) {
                set_color_single(1, HSV_RED);
            }
            if (host_keyboard_led_state().caps_lock) {
                set_color_single(2, HSV_RED);
            }
            if (host_keyboard_led_state().scroll_lock) {
                set_color_single(3, HSV_RED);
            }
            //rgb_matrix_set_color_all(0, 0, 0);
            //rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    }
    return true;
}
