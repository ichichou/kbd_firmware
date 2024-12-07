/* Copyright 2020 foostan
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

// -- Define Macros {{{

// Modifier Keycodes
#define RHYPR_T(kc) MT(MOD_RCTL | MOD_RSFT | MOD_RALT | MOD_RGUI, kc)
#define LCG(kc)     (QK_LCTL | QK_LGUI | (kc))
#define GUI_SFT     G(KC_LSFT)

// Layer-Tap
#define NAV_ESC  LT(_NAV, KC_ESC)
#define NAV_SLSH LT(_NAV, KC_SLSH)
#define SYM_TAB  LT(_SYM, KC_TAB)
#define SYM_ENT  LT(_SYM, KC_ENT)
#define FN_GRV   LT(_FN,  KC_GRV)

// Mod-Tap
#define HYPR_TAB  RHYPR_T(KC_TAB)
#define HYPR_BSPC RHYPR_T(KC_BSPC)
#define SFT_SPC   SFT_T(KC_SPC)
#define SFT_CW    SFT_T(CW_TOGG)
#define RSFT_SLSH RSFT_T(KC_SLSH)
#define RSFT_BSLS RSFT_T(KC_BSLS)
#define CTL_ENT   CTL_T(KC_ENT)
#define CTL_ESC   CTL_T(KC_ESC)
#define RCTL_QUOT RCTL_T(KC_QUOT)
#define RCTL_Q    RCTL_T(KC_Q)
#define GUI_LNG2  GUI_T(KC_LNG2)
#define RGUI_LNG1 RGUI_T(KC_LNG1)

// Home Row Mods
#define SFT_RBRC  SFT_T(KC_RBRC)
#define CTL_LBRC  CTL_T(KC_LBRC)
#define ALT_LSG_A ALT_T(LSG(KC_A))

// }}}

// -- Layers {{{

enum layer_names {
  _BASE,
  _NAV,
  _SYM,
  _WIN,
  _FN,
};

// }}}

// -- Behavior of Any Keycode {{{

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    // Caps Word / Shift
    case SFT_CW:
      if (record->tap.count && record->event.pressed) {
        caps_word_toggle();
        return false;
      }
      return true;

    // Shift-Command-A / Option
    case ALT_T(LSG(KC_A)):
      if (record->tap.count && record->event.pressed) {
        tap_code16(LSG(KC_A));
        return false;
      }
      return true;

    // Otherwise
    default:
      return true;

  }
  return true;
}

// }}}

// -- Tap-Hold Configuration {{{

// Hold On Other Key Press Mode
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    // -- Layer Keys
    case NAV_ESC:
      return true;
    case SYM_TAB:
      return true;
    case SYM_ENT:
      return true;
    case FN_GRV:
      return true;

    // -- Mod Keys
    case HYPR_TAB:
      return true;
    case HYPR_BSPC:
      return true;
    case SFT_SPC:
      return true;
    case SFT_CW:
      return true;
    case RSFT_BSLS:
      return true;
    case CTL_ENT:
      return true;
    case CTL_ESC:
      return true;
    case GUI_LNG2:
      return true;
    case RGUI_LNG1:
      return true;

    // -- Home Row Mods
    case SFT_RBRC:
      return true;
    case CTL_LBRC:
      return true;
    case ALT_LSG_A:
      return true;

    // Otherwise
    default:
      return false;

  }
}

// Permissive Hold Mode
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NAV_SLSH:
      return true;
    case RSFT_SLSH:
      return true;
    case RCTL_QUOT:
      return true;
    default:
      return false;
  }
}

// }}}

// -- Combos {{{

enum combos {
  SD,
  KL,
  WE,
  IO,
  DF,
  JK,
};

const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[] = {
  [SD] = COMBO(sd_combo, MO(_NAV)),
  [KL] = COMBO(kl_combo, MO(_NAV)),
  [WE] = COMBO(we_combo, MO(_WIN)),
  [IO] = COMBO(io_combo, MO(_WIN)),
  [DF] = COMBO(df_combo, KC_LNG2),
  [JK] = COMBO(jk_combo, KC_LNG1),
};

// COMBO_TERM_PER_COMBO (Default: 50)
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
  switch (index) {
    case SD:
      return 20;
    case KL:
      return 20;
    case WE:
      return 20;
    case IO:
      return 20;
    case DF:
      return 20;
    case JK:
      return 20;
  }
  return COMBO_TERM;
}

// COMBO_MUST_TAP_PER_COMBO
bool get_combo_must_tap(uint16_t index, combo_t *combo) {
  switch (index) {
    case DF:
      return true;
    case JK:
      return true;
  }
  return false;
}

// COMBO_MUST_HOLD_PER_COMBO
bool get_combo_must_hold(uint16_t index, combo_t *combo) {
  switch (index) {
    case SD:
      return true;
    case KL:
      return true;
    case WE:
      return true;
    case IO:
      return true;
  }
  return false;
}

// }}}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
    HYPR_TAB, KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,      KC_O,    KC_P,    HYPR_BSPC,
    CTL_ESC,  KC_A,    KC_S,    KC_D,     KC_F,    KC_G,       KC_H,    KC_J,    KC_K,      KC_L,    KC_SCLN, RCTL_QUOT,
    SFT_CW,   KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, RSFT_BSLS,
    MO(_FN),  KC_RCTL, KC_LALT, GUI_LNG2, NAV_ESC, SFT_SPC,    CTL_ENT, SYM_TAB, RGUI_LNG1, KC_DOWN, KC_UP,   FN_GRV
  ),

  [_NAV] = LAYOUT(
    _______, LSG(KC_S), KC_LPRN,  KC_RPRN,  MEH(KC_C), LSG(KC_T),    G(KC_TAB), C(KC_TAB), KC_LCBR, KC_RCBR, G(KC_RBRC), G(KC_UP),
    _______, ALT_LSG_A, CTL_LBRC, SFT_RBRC, LCG(KC_V), LCG(KC_S),    KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT, G(KC_LBRC), G(KC_DOWN),
    _______, LSG(KC_Z), G(KC_X),  G(KC_C),  LSG(KC_V), G(KC_V),      KC_BSPC,   KC_DEL,    C(KC_A), C(KC_E), XXXXXXX,    XXXXXXX,
    _______, _______,   _______,  _______,  _______,   _______,      _______,   _______,   _______, _______, _______,    _______
  ),

  [_SYM] = LAYOUT(
    _______, KC_DOT,  KC_PLUS, KC_UNDS, KC_EXLM, KC_PIPE,    KC_GRV,  KC_QUES, KC_CIRC, KC_DLR,  KC_COMM, XXXXXXX,
    _______, KC_ASTR, KC_EQL,  KC_MINS, KC_0,    KC_AT,      KC_AMPR, KC_1,    KC_PERC, KC_HASH, KC_COLN, KC_QUOT,
    _______, KC_8,    KC_6,    KC_4,    KC_2,    KC_BSLS,    KC_TILD, KC_3,    KC_5,    KC_7,    KC_9,    XXXXXXX,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
  ),

  [_WIN] = LAYOUT(
    XXXXXXX, LCA(KC_U),    LCA(KC_I), XXXXXXX,   MEH(KC_C),    C(KC_1),    C(KC_4), MEH(KC_C),   A(KC_UP),   XXXXXXX, XXXXXXX, LCA(KC_BSPC),
    XXXXXXX, LCA(KC_LEFT), LCA(KC_D), LCA(KC_G), LCA(KC_RGHT), C(KC_2),    C(KC_5), LCA(KC_C),   A(KC_DOWN), XXXXXXX, XXXXXXX, MEH(KC_ENT),
    XXXXXXX, LCA(KC_Z),    LCA(KC_X), LCA(KC_V), LCA(KC_B),    C(KC_3),    C(KC_6), LCA(KC_ENT), XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,      XXXXXXX,   XXXXXXX,   _______,      XXXXXXX,    XXXXXXX, _______,     XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_FN] = LAYOUT(
    LCG(KC_Q), KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,    LSG(KC_2), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LCG(KC_Q),
    XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,    LSG(KC_3), XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, KC_MPLY,
    XXXXXXX,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,    LSG(KC_4), XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE,
    _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    QK_BOOT,   XXXXXXX, XXXXXXX, KC_LEFT, KC_RGHT, _______
  ),

};
