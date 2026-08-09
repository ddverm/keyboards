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
     LCTL_T(KC_ESC), LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), TD(TD_QUOT_DQT),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ENT,           KC_NO,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LSFT, LT(_LOWER, KC_SPC), KC_TAB,          KC_BSPC, TL_UPPR, KC_DEL
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PGUP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV,  _______, KC_UP,   _______, QK_BOOT, _______,                            _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PGDN,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_LBRC,                            KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RM_NEXT, EE_CLR,  _______, _______, _______, KC_LCBR, KC_LPRN,          KC_RPRN, KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_DEL,                    KC_DEL,  _______, KC_P0
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
    }
    return true;
}
