// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
     _QWERTY,
     _LOWER,
     _RAISE
};

enum custom_tap_dances {
     TD_BSPC_F12,
     TD_QUOT_DQT,
     TD_1_F1,
     TD_2_F2,
     TD_3_F3,
     TD_4_F4,
     TD_5_F5,
     TD_6_F6,
     TD_7_F7,
     TD_8_F8,
     TD_9_F9,
     TD_0_F10,
};

void td_bspc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_F12);
    } else {
        tap_code16(LCTL(KC_EQL));
    }
}
void td_bspc_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_F12);
}

void td_quot_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(LSFT(KC_QUOT));
    } else {
        tap_code16(KC_QUOT);
    }
}
void td_quot_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(LSFT(KC_QUOT));
}

// Generic "tap = digit, hold = matching function key" pair, used for the number row.
typedef struct {
    uint16_t tap_kc;
    uint16_t hold_kc;
} tap_hold_t;

void td_number_fkey_finished(tap_dance_state_t *state, void *user_data) {
    tap_hold_t *pair = (tap_hold_t *)user_data;
    if (state->pressed) {
        register_code16(pair->hold_kc);
    } else {
        tap_code16(pair->tap_kc);
    }
}
void td_number_fkey_reset(tap_dance_state_t *state, void *user_data) {
    tap_hold_t *pair = (tap_hold_t *)user_data;
    if (state->pressed) {
        unregister_code16(pair->hold_kc);
    }
}

#define ACTION_TAP_DANCE_NUMBER_FKEY(tap_kc, hold_kc) \
    { .fn = {NULL, td_number_fkey_finished, td_number_fkey_reset, NULL}, .user_data = (void *)&((tap_hold_t){tap_kc, hold_kc}), }

tap_dance_action_t tap_dance_actions[] = {
    [TD_BSPC_F12] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_bspc_finished, td_bspc_reset),
    [TD_QUOT_DQT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_quot_finished, td_quot_reset),
    [TD_1_F1]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_1, KC_F1),
    [TD_2_F2]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_2, KC_F2),
    [TD_3_F3]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_3, KC_F3),
    [TD_4_F4]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_4, KC_F4),
    [TD_5_F5]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_5, KC_F5),
    [TD_6_F6]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_6, KC_F6),
    [TD_7_F7]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_7, KC_F7),
    [TD_8_F8]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_8, KC_F8),
    [TD_9_F9]     = ACTION_TAP_DANCE_NUMBER_FKEY(KC_9, KC_F9),
    [TD_0_F10]    = ACTION_TAP_DANCE_NUMBER_FKEY(KC_0, KC_F10),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
            return 250;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_VOLU, TD(TD_1_F1), TD(TD_2_F2), TD(TD_3_F3), TD(TD_4_F4), TD(TD_5_F5),         TD(TD_6_F6), TD(TD_7_F7), TD(TD_8_F8), TD(TD_9_F9), TD(TD_0_F10), TD(TD_BSPC_F12),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_VOLD, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LCTL(KC_MINS),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL_T(KC_ESC), LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_COLN), TD(TD_QUOT_DQT),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ENT,           KC_NO,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LSFT, LT(_LOWER, KC_SPC), KC_TAB,          KC_BSPC, TL_UPPR, KC_DEL
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT, KC_NO,   EE_CLR,  KC_NO,   KC_SYRQ, KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   LCTL(KC_B), LCTL(KC_1), LCTL(KC_2), LCA(KC_B),                 _______, KC_PGUP, KC_UP,   KC_PGDN, KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL(KC_LBRC), KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LCTL(KC_RBRC),                 KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   LCTL(LSFT(KC_GRV)), LCTL(KC_GRV), KC_NO, KC_NO,     KC_NO,   KC_NO,   KC_PGDN, KC_NO,   KC_NO,   KC_SLSH, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_NO,                     KC_BSPC, KC_ENT,  KC_DEL
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RM_TOGG, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, QK_BOOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RM_NEXT, KC_MPRV, KC_MNXT, KC_VOLU, KC_PGUP, KC_UNDS,                            KC_EQL,  KC_HOME, RM_HUEU, RM_SATU, RM_VALU, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_LPRN,          _______, KC_PLUS, KC_END,  RM_HUED, RM_SATD, RM_VALD, EE_CLR,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) == _QWERTY) {
        rgb_matrix_set_color(19, 0xFF, 0xF5, 0x00); // LSFT_T(KC_F)
        rgb_matrix_set_color(53, 0xFF, 0xF5, 0x00); // RSFT_T(KC_J)
        rgb_matrix_set_color(18, 0x00, 0xFF, 0x31); // LCTL_T(KC_D)
        rgb_matrix_set_color(52, 0x00, 0xFF, 0x31); // RCTL_T(KC_K)
        rgb_matrix_set_color(17, 0xF8, 0x6E, 0xD6); // LALT_T(KC_S)
        rgb_matrix_set_color(51, 0xF8, 0x6E, 0xD6); // RALT_T(KC_L)
        rgb_matrix_set_color(16, 0x00, 0x75, 0xFF); // LGUI_T(KC_A)
        rgb_matrix_set_color(50, 0x00, 0x75, 0xFF); // RGUI_T(KC_SCLN)
        rgb_matrix_set_color(0,  0x0B, 0xDD, 0x35); // KC_VOLU
        rgb_matrix_set_color(14, 0xFF, 0xF5, 0x00); // KC_VOLD
        rgb_matrix_set_color(26, 0xF5, 0x09, 0x09); // KC_MUTE
        rgb_matrix_set_color(34, 0x42, 0xFF, 0x00); // TD_BSPC_F12
        rgb_matrix_set_color(48, 0xFF, 0xF5, 0x00); // LCTL(KC_MINS)
        rgb_matrix_set_color(66, 0xF5, 0x09, 0x09); // KC_BSPC (thumb)
        rgb_matrix_set_color(63, 0xF5, 0x09, 0x09); // KC_DEL (thumb)
        rgb_matrix_set_color(60, 0x00, 0x00, 0x00); // KC_NO (was KC_RSFT)
        rgb_matrix_set_color(67, 0x00, 0x00, 0x00); // KC_NO (was KC_END)
    } else if (get_highest_layer(layer_state) == _LOWER) {
        rgb_matrix_set_color(0,  0xFF, 0xA5, 0x00); // QK_BOOT
        rgb_matrix_set_color(2,  0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(3,  0xFF, 0xA5, 0x00); // EE_CLR
        rgb_matrix_set_color(5,  0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(6,  0x8F, 0xA3, 0x00); // KC_SYRQ
        rgb_matrix_set_color(8,  0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(14, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(13, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(12, 0x42, 0xFF, 0x00); // ctrl+b
        rgb_matrix_set_color(11, 0xFF, 0x00, 0x8A); // ctrl+1
        rgb_matrix_set_color(10, 0xFF, 0x00, 0x8A); // ctrl+2
        rgb_matrix_set_color(9,  0x42, 0xFF, 0x00); // ctrl+alt+b
        rgb_matrix_set_color(16, 0x00, 0x75, 0xFF); // KC_LGUI
        rgb_matrix_set_color(17, 0xF8, 0x6E, 0xD6); // KC_LALT
        rgb_matrix_set_color(18, 0x00, 0xFF, 0x31); // KC_LCTL
        rgb_matrix_set_color(19, 0xFF, 0xF5, 0x00); // KC_LSFT
        rgb_matrix_set_color(26, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(25, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(24, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(23, 0x61, 0x00, 0xFF); // ctrl+shift+`
        rgb_matrix_set_color(22, 0x61, 0x00, 0xFF); // ctrl+`
        rgb_matrix_set_color(21, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(33, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(32, 0x00, 0x00, 0x00); // KC_NO (thumb)
        rgb_matrix_set_color(42, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(40, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(39, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(37, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(36, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(34, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(44, 0xFF, 0x00, 0xE5); // KC_PGUP
        rgb_matrix_set_color(45, 0x00, 0x75, 0xFF); // KC_UP
        rgb_matrix_set_color(46, 0xFF, 0x00, 0xE5); // KC_PGDN
        rgb_matrix_set_color(47, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(48, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(54, 0xFF, 0xF5, 0x00); // KC_HOME
        rgb_matrix_set_color(53, 0x00, 0x75, 0xFF); // KC_LEFT
        rgb_matrix_set_color(52, 0x00, 0x75, 0xFF); // KC_DOWN
        rgb_matrix_set_color(51, 0x00, 0x75, 0xFF); // KC_RGHT
        rgb_matrix_set_color(50, 0xFF, 0xF5, 0x00); // KC_END
        rgb_matrix_set_color(49, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(67, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(55, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(56, 0xFF, 0x00, 0xE5); // KC_PGDN
        rgb_matrix_set_color(57, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(58, 0x00, 0x00, 0x00); // KC_NO
        rgb_matrix_set_color(66, 0xF5, 0x09, 0x09); // KC_BSPC (thumb)
        rgb_matrix_set_color(63, 0xF5, 0x09, 0x09); // KC_DEL (thumb)
    }
    return true;
}
