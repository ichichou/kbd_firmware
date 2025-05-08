// KB: Cornelius
// KM: ichichou

// -- Copyright {{{

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

// }}}

// -- Includes {{{

#include QMK_KEYBOARD_H

// }}}

// -- Macros {{{

// Modifiers
#define RHYPR_T(kc) MT(MOD_RCTL | MOD_RSFT | MOD_RALT | MOD_RGUI, kc)
#define LCG(kc)     (QK_LCTL | QK_LGUI | (kc))

// Layer-Tap
#define NAV_ESC LT(_NAV, KC_ESC)
#define NAV_TAB LT(_NAV, KC_TAB)
#define SYM_TAB LT(_SYM, KC_TAB)
#define SYM_ENT LT(_SYM, KC_ENT)
#define FN_BSLS LT(_FN,  KC_BSLS)
#define FN_GRV  LT(_FN,  KC_GRV)

// Mod-Tap
#define RHYPR_TAB  RHYPR_T(KC_TAB)
#define RHYPR_BSPC RHYPR_T(KC_BSPC)
#define LSFT_SPC   SFT_T(KC_SPC)
#define LSFT_CW    SFT_T(CW_TOGG)
#define RSFT_SLSH  RSFT_T(KC_SLSH)
#define RSFT_BSLS  RSFT_T(KC_BSLS)
#define LCTL_ESC   CTL_T(KC_ESC)
#define RCTL_ENT   RCTL_T(KC_ENT)
#define RCTL_QUOT  RCTL_T(KC_QUOT)
#define RCTL_TAB   RCTL_T(KC_TAB)
#define RALT_GRV   RALT_T(KC_GRV)
#define LGUI_LNG2  GUI_T(KC_LNG2)
#define RGUI_LNG1  RGUI_T(KC_LNG1)

// Home Row Mods
#define LCTL_LBRC CTL_T(KC_LBRC)
#define LSFT_RBRC SFT_T(KC_RBRC)
#define LGUI_GRV  GUI_T(KC_GRV)

// MTGAP
#define RCTL_MT_Q RCTL_T(MT_Q)

// }}}

// -- Functions {{{

// MTGAP
static bool process_mtgap_key(uint8_t mtgap_key,
                              uint8_t qwerty_key,
                              bool *mtgap_registered,
                              bool *qwerty_registered,
                              keyrecord_t *record,
                              uint8_t mod_state) {

  if (record->event.pressed) {
    if ((mod_state & ~(MOD_MASK_SHIFT)) == 0) {
      register_code(mtgap_key);
      *mtgap_registered = true;
      return false;
    } else {
      register_code(qwerty_key);
      *qwerty_registered = true;
      return false;
    }
  } else {
    if (*mtgap_registered) {
      unregister_code(mtgap_key);
      *mtgap_registered = false;
      return false;
    } else if (*qwerty_registered) {
      unregister_code(qwerty_key);
      *qwerty_registered = false;
      return false;
    }
  }
  return false;
}

// }}}

// -- Layers {{{

enum layer_names {
  _BASE,
  _MTGAP,
  _NAV,
  _SYM,
  _WIN,
  _FN,
};

// }}}

// -- Custom Keycodes {{{

enum my_keycodes {
  SAMPLE = QK_USER,

  // MTGAP {{{
  MT_A,
  MT_B,
  MT_C,
  MT_D,
  MT_E,
  MT_F,
  MT_G,
  MT_H,
  MT_I,
  MT_J,
  MT_K,
  MT_L,
  MT_M,
  MT_N,
  MT_O,
  MT_P,
  MT_Q,
  MT_R,
  MT_S,
  MT_T,
  MT_U,
  MT_V,
  MT_W,
  MT_X,
  MT_Y,
  MT_Z,
  MT_SCLN,
  MT_QUOT,
  MT_COMM,
  MT_DOT,
  MT_SLSH,
  // }}}

};

// }}}

// -- process_record_user {{{

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  mod_state = get_mods();
  switch (keycode) {

    case SFT_T(CW_TOGG):
      if (record->tap.count && record->event.pressed) {
        caps_word_on();
        return false;
      }
      return true;

    case RCTL_T(MT_Q):
      if (record->tap.count && record->event.pressed) {
        if ((mod_state & ~(MOD_MASK_SHIFT)) == 0) {
          tap_code(KC_Q);
          return false;
        } else {
          tap_code(KC_QUOT);
          return false;
        }
      }
      return true;

    // MTGAP (Mod-1) {{{

    // ypou; kdlcw
    // inea, mhtsr q
    // z/'.x bfgvj

    static bool mtgap_registered[31];
    static bool qwerty_registered[31];

    case MT_A:    return process_mtgap_key(KC_A,    KC_F,    &mtgap_registered[0],  &qwerty_registered[0],  record, mod_state);
    case MT_B:    return process_mtgap_key(KC_B,    KC_N,    &mtgap_registered[1],  &qwerty_registered[1],  record, mod_state);
    case MT_C:    return process_mtgap_key(KC_C,    KC_O,    &mtgap_registered[2],  &qwerty_registered[2],  record, mod_state);
    case MT_D:    return process_mtgap_key(KC_D,    KC_U,    &mtgap_registered[3],  &qwerty_registered[3],  record, mod_state);
    case MT_E:    return process_mtgap_key(KC_E,    KC_D,    &mtgap_registered[4],  &qwerty_registered[4],  record, mod_state);
    case MT_F:    return process_mtgap_key(KC_F,    KC_M,    &mtgap_registered[5],  &qwerty_registered[5],  record, mod_state);
    case MT_G:    return process_mtgap_key(KC_G,    KC_COMM, &mtgap_registered[6],  &qwerty_registered[6],  record, mod_state);
    case MT_H:    return process_mtgap_key(KC_H,    KC_J,    &mtgap_registered[7],  &qwerty_registered[7],  record, mod_state);
    case MT_I:    return process_mtgap_key(KC_I,    KC_A,    &mtgap_registered[8],  &qwerty_registered[8],  record, mod_state);
    case MT_J:    return process_mtgap_key(KC_J,    KC_SLSH, &mtgap_registered[9],  &qwerty_registered[9],  record, mod_state);
    case MT_K:    return process_mtgap_key(KC_K,    KC_Y,    &mtgap_registered[10], &qwerty_registered[10], record, mod_state);
    case MT_L:    return process_mtgap_key(KC_L,    KC_I,    &mtgap_registered[11], &qwerty_registered[11], record, mod_state);
    case MT_M:    return process_mtgap_key(KC_M,    KC_H,    &mtgap_registered[12], &qwerty_registered[12], record, mod_state);
    case MT_N:    return process_mtgap_key(KC_N,    KC_S,    &mtgap_registered[13], &qwerty_registered[13], record, mod_state);
    case MT_O:    return process_mtgap_key(KC_O,    KC_E,    &mtgap_registered[14], &qwerty_registered[14], record, mod_state);
    case MT_P:    return process_mtgap_key(KC_P,    KC_W,    &mtgap_registered[15], &qwerty_registered[15], record, mod_state);
    case MT_Q:    return process_mtgap_key(KC_Q,    KC_QUOT, &mtgap_registered[16], &qwerty_registered[16], record, mod_state);
    case MT_R:    return process_mtgap_key(KC_R,    KC_SCLN, &mtgap_registered[17], &qwerty_registered[17], record, mod_state);
    case MT_S:    return process_mtgap_key(KC_S,    KC_L,    &mtgap_registered[18], &qwerty_registered[18], record, mod_state);
    case MT_T:    return process_mtgap_key(KC_T,    KC_K,    &mtgap_registered[19], &qwerty_registered[19], record, mod_state);
    case MT_U:    return process_mtgap_key(KC_U,    KC_R,    &mtgap_registered[20], &qwerty_registered[20], record, mod_state);
    case MT_V:    return process_mtgap_key(KC_V,    KC_DOT,  &mtgap_registered[21], &qwerty_registered[21], record, mod_state);
    case MT_W:    return process_mtgap_key(KC_W,    KC_P,    &mtgap_registered[22], &qwerty_registered[22], record, mod_state);
    case MT_X:    return process_mtgap_key(KC_X,    KC_B,    &mtgap_registered[23], &qwerty_registered[23], record, mod_state);
    case MT_Y:    return process_mtgap_key(KC_Y,    KC_Q,    &mtgap_registered[24], &qwerty_registered[24], record, mod_state);
    case MT_Z:    return process_mtgap_key(KC_Z,    KC_Z,    &mtgap_registered[25], &qwerty_registered[25], record, mod_state);
    case MT_SCLN: return process_mtgap_key(KC_SCLN, KC_T,    &mtgap_registered[26], &qwerty_registered[26], record, mod_state);
    case MT_QUOT: return process_mtgap_key(KC_QUOT, KC_C,    &mtgap_registered[27], &qwerty_registered[27], record, mod_state);
    case MT_COMM: return process_mtgap_key(KC_COMM, KC_G,    &mtgap_registered[28], &qwerty_registered[28], record, mod_state);
    case MT_DOT:  return process_mtgap_key(KC_DOT,  KC_V,    &mtgap_registered[29], &qwerty_registered[29], record, mod_state);
    case MT_SLSH: return process_mtgap_key(KC_SLSH, KC_X,    &mtgap_registered[30], &qwerty_registered[30], record, mod_state);

    // }}}

    // Otherwise
    default:
      return true;

  }
}

// }}}

// -- Tap-Hold Configuration {{{

// 'Hold on other key press' と 'permissive hold' を併用するには、
// HOLD_ON_OTHER_KEY_PRESS_PER_KEY と PERMISSIVE_HOLD_PER_KEY の組み合わせが必要。
//
// HOLD_ON_OTHER_KEY_PRESS と PERMISSIVE_HOLD_PER_KEY の組み合わせはうまく動作しない。
// Tap-hold キーの基本動作を 'hold on other key press' としながら、
// 個別に指定したキーの動作を 'permissive hold' とすることを意図しているが、
// そのように指定しても 'permissive hold' とはならず、すべて 'hold on other key press' になってしまう。
// 'hold on other key press' と 'permissive hold' の両方が設定されていると、'hold on...' が優先されるのだろう。

// Hold On Other Key Press Mode
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    // Layer-Tap
    case NAV_ESC: return true;
    case NAV_TAB: return true;
    case SYM_TAB: return true;
    case SYM_ENT: return true;
    case FN_BSLS: return true;
    case FN_GRV:  return true;

    // Mod-Tap
    case RHYPR_TAB:  return true;
    case RHYPR_BSPC: return true;
    case LSFT_SPC:   return true;
    case LSFT_CW:    return true;
    case RSFT_SLSH:  return true;
    case RSFT_BSLS:  return true;
    case LCTL_ESC:   return true;
    case RCTL_ENT:   return true;
    case RCTL_QUOT:  return true;
    case RCTL_TAB:   return true;
    case RALT_GRV:   return true;
    case LGUI_LNG2:  return true;
    case RGUI_LNG1:  return true;

    // Home Row Mods
    case LCTL_LBRC: return true;
    case LSFT_RBRC: return true;
    case LGUI_GRV:  return true;

    // MTGAP
    case RCTL_MT_Q: return true;

    // Otherwise
    default:
      return false;

  }
}

// Permissive Hold Mode
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Otherwise
    default:
      return false;
  }
}

// }}}

// -- Keymaps {{{

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
    RHYPR_TAB, KC_Q,    KC_W,    KC_E,      KC_R,    KC_T,        KC_Y,     KC_U,    KC_I,      KC_O,    KC_P,    KC_BSPC,
    LCTL_ESC,  KC_A,    KC_S,    KC_D,      KC_F,    KC_G,        KC_H,     KC_J,    KC_K,      KC_L,    KC_SCLN, RCTL_QUOT,
    LSFT_CW,   KC_Z,    KC_X,    KC_C,      KC_V,    KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, RSFT_BSLS,
    MO(_FN),   KC_RCTL, KC_LALT, LGUI_LNG2, NAV_ESC, LSFT_SPC,    RCTL_ENT, SYM_TAB, RGUI_LNG1, KC_DOWN, KC_UP,   FN_GRV
  ),

  [_MTGAP] = LAYOUT(
    RHYPR_TAB, MT_Y,    MT_P,    MT_O,      MT_U,    MT_SCLN,     MT_K,     MT_D,    MT_L,      MT_C,    MT_W,  KC_BSPC,
    LCTL_ESC,  MT_I,    MT_N,    MT_E,      MT_A,    MT_COMM,     MT_M,     MT_H,    MT_T,      MT_S,    MT_R,  RCTL_MT_Q,
    LSFT_CW,   MT_Z,    MT_SLSH, MT_QUOT,   MT_DOT,  MT_X,        MT_B,     MT_F,    MT_G,      MT_V,    MT_J,  RSFT_BSLS,
    MO(_FN),   KC_RCTL, KC_LALT, LGUI_LNG2, NAV_ESC, LSFT_SPC,    RCTL_ENT, SYM_TAB, RGUI_LNG1, KC_DOWN, KC_UP, FN_GRV
  ),

  [_NAV] = LAYOUT(
    _______, LSG(KC_C), KC_LPRN,   KC_RPRN,   C(KC_TAB), LSG(KC_T),    G(KC_TAB), C(KC_TAB), KC_LCBR, KC_RCBR, G(KC_RBRC), G(KC_UP),
    _______, LSG(KC_A), LCTL_LBRC, LSFT_RBRC, LCG(KC_V), LCG(KC_S),    KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT, G(KC_LBRC), G(KC_DOWN),
    _______, LSG(KC_Z), G(KC_X),   G(KC_C),   LSG(KC_V), G(KC_V),      KC_BSPC,   KC_DEL,    C(KC_A), C(KC_E), XXXXXXX,    XXXXXXX,
    _______, _______,   _______,   _______,   _______,   _______,      _______,   _______,   _______, _______, _______,    _______
  ),

  [_SYM] = LAYOUT(
    _______, KC_DOT,  KC_PLUS, KC_UNDS, KC_EXLM, KC_PIPE,    KC_GRV,  KC_QUES, KC_CIRC, KC_DLR,  KC_COMM, XXXXXXX,
    _______, KC_ASTR, KC_EQL,  KC_MINS, KC_0,    KC_AT,      KC_AMPR, KC_1,    KC_PERC, KC_HASH, KC_COLN, KC_QUOT,
    _______, KC_8,    KC_6,    KC_4,    KC_2,    KC_BSLS,    KC_TILD, KC_3,    KC_5,    KC_7,    KC_9,    XXXXXXX,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
  ),

  [_WIN] = LAYOUT(
    XXXXXXX, LCA(KC_U),    LCA(KC_I), XXXXXXX,   MEH(KC_C),    C(KC_1),    C(KC_4), MEH(KC_C),   A(KC_UP),    XXXXXXX, XXXXXXX, LCA(KC_BSPC),
    XXXXXXX, LCA(KC_LEFT), XXXXXXX,   XXXXXXX,   LCA(KC_RGHT), C(KC_2),    C(KC_5), LCA(KC_C),   A(KC_DOWN),  XXXXXXX, XXXXXXX, MEH(KC_ENT),
    XXXXXXX, LCA(KC_Z),    LCA(KC_X), LCA(KC_V), LCA(KC_B),    C(KC_3),    C(KC_6), LCA(KC_ENT), MEH(KC_ENT), XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,      XXXXXXX,   XXXXXXX,   XXXXXXX,      XXXXXXX,    XXXXXXX, XXXXXXX,     XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_FN] = LAYOUT(
    LCG(KC_Q), KC_F1,   KC_F2,   KC_F3,   KC_F4,   DF(_BASE),     LSG(KC_2), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LCG(KC_Q),
    XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   DF(_MTGAP),    LSG(KC_3), XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, KC_MPLY,
    XXXXXXX,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,       LSG(KC_4), XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE,
    _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,        QK_BOOT,   XXXXXXX, XXXXXXX, KC_LEFT, KC_RGHT, _______
  ),

};

// }}}
