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

// -- #include {{{

#include QMK_KEYBOARD_H

// }}}

// -- #define {{{

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
#define MTGAP_KEYCODE(name, mtgap_key, qwerty_key, mt_var, qwerty_var) \
  case name: \
    { \
      static bool mt_##mtgap_var##_registered; \
      static bool qw_##qwerty_var##_registered; \
      \
      if (record->event.pressed) { \
        if ((mod_state & ~(MOD_MASK_SHIFT)) == 0) { \
          register_code(mtgap_key); \
          mt_##mtgap_var##_registered = true; \
          return false; \
        } else { \
          register_code(qwerty_key); \
          qw_##qwerty_var##_registered = true; \
          return false; \
        } \
      } else { \
        if (mt_##mtgap_var##_registered) { \
          unregister_code(mtgap_key); \
          mt_##mtgap_var##_registered = false; \
          return false; \
        } else if (qw_##qwerty_var##_registered) { \
          unregister_code(qwerty_key); \
          qw_##qwerty_var##_registered = false; \
          return false; \
        } \
      } \
      return false; \
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
  RCTL_MT_Q,
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

    // MTGAP (Mod-Q) {{{
    //
    // ypou; kdlcw
    // inea, mhtsr q
    // z/'.x bfgvj
    MTGAP_KEYCODE(MT_A,    KC_A,    KC_F,    a,    f)
    MTGAP_KEYCODE(MT_B,    KC_B,    KC_N,    b,    n)
    MTGAP_KEYCODE(MT_C,    KC_C,    KC_O,    c,    o)
    MTGAP_KEYCODE(MT_D,    KC_D,    KC_U,    d,    u)
    MTGAP_KEYCODE(MT_E,    KC_E,    KC_D,    e,    d)
    MTGAP_KEYCODE(MT_F,    KC_F,    KC_M,    f,    m)
    MTGAP_KEYCODE(MT_G,    KC_G,    KC_COMM, g,    comm)
    MTGAP_KEYCODE(MT_H,    KC_H,    KC_J,    h,    j)
    MTGAP_KEYCODE(MT_I,    KC_I,    KC_A,    i,    a)
    MTGAP_KEYCODE(MT_J,    KC_J,    KC_SLSH, j,    slsh)
    MTGAP_KEYCODE(MT_K,    KC_K,    KC_Y,    k,    y)
    MTGAP_KEYCODE(MT_L,    KC_L,    KC_I,    l,    i)
    MTGAP_KEYCODE(MT_M,    KC_M,    KC_H,    m,    h)
    MTGAP_KEYCODE(MT_N,    KC_N,    KC_S,    n,    s)
    MTGAP_KEYCODE(MT_O,    KC_O,    KC_E,    o,    e)
    MTGAP_KEYCODE(MT_P,    KC_P,    KC_W,    p,    w)
    MTGAP_KEYCODE(MT_Q,    KC_Q,    KC_QUOT, q,    quot)
    MTGAP_KEYCODE(MT_R,    KC_R,    KC_SCLN, r,    scln)
    MTGAP_KEYCODE(MT_S,    KC_S,    KC_L,    s,    l)
    MTGAP_KEYCODE(MT_T,    KC_T,    KC_K,    t,    k)
    MTGAP_KEYCODE(MT_U,    KC_U,    KC_R,    u,    r)
    MTGAP_KEYCODE(MT_V,    KC_V,    KC_DOT,  v,    dot)
    MTGAP_KEYCODE(MT_W,    KC_W,    KC_P,    w,    p)
    MTGAP_KEYCODE(MT_X,    KC_X,    KC_B,    x,    b)
    MTGAP_KEYCODE(MT_Y,    KC_Y,    KC_Q,    y,    q)
    MTGAP_KEYCODE(MT_Z,    KC_Z,    KC_Z,    z,    z)
    MTGAP_KEYCODE(MT_SCLN, KC_SCLN, KC_T,    scln, t)
    MTGAP_KEYCODE(MT_QUOT, KC_QUOT, KC_C,    quot, c)
    MTGAP_KEYCODE(MT_COMM, KC_COMM, KC_G,    comm, g)
    MTGAP_KEYCODE(MT_DOT,  KC_DOT,  KC_V,    dot,  v)
    MTGAP_KEYCODE(MT_SLSH, KC_SLSH, KC_X,    slsh, x)

    // Hold 時の動作が機能せず、MT_Q と同じ挙動になる
    case RCTL_MT_Q:
      {
        static bool mt_q_registered;
        static bool qw_quot_registered;
        static bool rctl_registered;

        // On tap
        if (record->tap.count && record->event.pressed) {
          if ((mod_state & ~(MOD_MASK_SHIFT)) == 0) {
            register_code(KC_Q);
            mt_q_registered = true;
            return false;
          } else {
            register_code(KC_QUOT);
            qw_quot_registered = true;
            return false;
          }

        // On hold
        } else if (record->event.pressed) {
          register_code(KC_RCTL);
          rctl_registered = true;
          return false;

        // When key released
        } else {
          if (mt_q_registered) {
            unregister_code(KC_Q);
            mt_q_registered = false;
            return false;
          } else if (qw_quot_registered) {
            unregister_code(KC_QUOT);
            qw_quot_registered = false;
            return false;
          } else if (rctl_registered) {
            unregister_code(KC_RCTL);
            rctl_registered = false;
            return false;
          }
        }
        return false;
      }

    // }}}

    // Otherwise
    default:
      return true;

  }
}

// }}}

// -- Key Overrides {{{

// Key Overrides は Karabiner との相性が悪いため、併用できない。
// 例えば QMK 側で LCmd-H -> Left とオーバーライドしたなら、Karabiner が干渉して LCmd-H -> LCmd-Left と出力されてしまう。
// これは Karabiner の Complex Modifications に何もルールを登録していなかったとしても同じである。
// 唯一の手段として、Key Overrides を使用したいキーボードを Karabiner の管理対象から外せば、Karabiner の干渉を免れることができる。
// （当然 Karabiner と Key Overrides の併用はできなくなる）

// const key_override_t lgui_h_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_H, KC_LEFT);
// const key_override_t lgui_j_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_J, KC_DOWN);
// const key_override_t lgui_k_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_K, KC_UP);
// const key_override_t lgui_l_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_L, KC_RGHT);
// const key_override_t *key_overrides[] = {
//   &lgui_h_override,
//   &lgui_j_override,
//   &lgui_k_override,
//   &lgui_l_override,
// };

// }}}

// -- Combos {{{

// コンボは Karabiner の同時押しと干渉するため、
// 同時押し系の機能はすべて Karabiner 側で実装する。

// enum combos {
//   SD,
//   KL,
//   WE,
//   IO,
// };
//
// const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
// const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
// const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
// const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
//
// combo_t key_combos[] = {
//   [SD] = COMBO(sd_combo, MO(_NAV)),
//   [KL] = COMBO(kl_combo, MO(_NAV)),
//   [WE] = COMBO(we_combo, MO(_WIN)),
//   [IO] = COMBO(io_combo, MO(_WIN)),
// };

// }}}

// -- Combo Configuration {{{

// // COMBO_TERM_PER_COMBO (Default: 50)
// //
// // Karabiner 側の閾値が 50 ms の場合、COMBO_TERM は 20 ms 程度でないと、Karabiner での同時押し判定に支障が出る。
// // Karabiner 側の閾値が 70 ms なら、COMBO_TERM を 50 ms にしても実用に耐える。
// // 新下駄配列の同時押しに絡まないキーでのコンボなら関係ないと思われる。
// uint16_t get_combo_term(uint16_t index, combo_t *combo) {
//   switch (index) {
//     case SD: return 20;
//     case KL: return 20;
//     case WE: return 20;
//     case IO: return 20;
//   }
//   return COMBO_TERM;
// }
//
// // COMBO_MUST_TAP_PER_COMBO
// bool get_combo_must_tap(uint16_t index, combo_t *combo) {
//   switch (index) {
//   }
//   return false;
// }
//
// // COMBO_MUST_HOLD_PER_COMBO
// bool get_combo_must_hold(uint16_t index, combo_t *combo) {
//   switch (index) {
//     case SD: return true;
//     case KL: return true;
//     case WE: return true;
//     case IO: return true;
//   }
//   return false;
// }

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
    LCTL_ESC,  MT_I,    MT_N,    MT_E,      MT_A,    MT_COMM,     MT_M,     MT_H,    MT_T,      MT_S,    MT_R,  MT_Q,
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
