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

// -- HOLD_ON_OTHER_KEY_PRESS_PER_KEY {{{

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    // "Hold On Other Key Press Mode" Mode
    case NAV_ESC:
      return true;
    case SYM_TAB:
      return true;
    case SYM_ENT:
      return true;
    case HYPR_TAB:
      return true;
    case HYPR_BSPC:
      return true;
    case SFT_SPC:
      return true;
    case SFT_CW:
      return true;
    case CTL_ENT:
      return true;
    case CTL_ESC:
      return true;
    case GUI_LNG2:
      return true;
    case RGUI_LNG1:
      return true;
    case SFT_RBRC:
      return true;
    case CTL_LBRC:
      return true;
    case ALT_LSG_A:
      return true;

    // Default Mode
    case NAV_SLSH:
      return false;
    case RSFT_SLSH:
      return false;
    case RSFT_BSLS:
      return false;
    case RCTL_QUOT:
      return false;

    // Otherwise
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

  [_BASE] = LAYOUT_split_3x6_3_ex2(
    HYPR_TAB, KC_Q, KC_W, KC_E, KC_R,     KC_T,    C(KC_1),    C(KC_3), KC_Y,    KC_U, KC_I,    KC_O,   KC_P,    HYPR_BSPC,
    CTL_ESC,  KC_A, KC_S, KC_D, KC_F,     KC_G,    C(KC_2),    C(KC_4), KC_H,    KC_J, KC_K,    KC_L,   KC_SCLN, RCTL_QUOT,
    SFT_CW,   KC_Z, KC_X, KC_C, KC_V,     KC_B,                         KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_BSLS,
                                GUI_LNG2, NAV_ESC, SFT_SPC,    CTL_ENT, SYM_TAB, RGUI_LNG1
  ),

  [_NAV] = LAYOUT_split_3x6_3_ex2(
    _______, LSG(KC_S), KC_LPRN,  KC_RPRN,  MEH(KC_C), LSG(KC_T), XXXXXXX,    XXXXXXX, G(KC_TAB), C(KC_TAB), KC_LCBR, KC_RCBR, G(KC_RBRC), G(KC_UP),
    _______, ALT_LSG_A, CTL_LBRC, SFT_RBRC, LCG(KC_V), LCG(KC_S), XXXXXXX,    XXXXXXX, KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT, G(KC_LBRC), G(KC_DOWN),
    _______, LSG(KC_Z), G(KC_X),  G(KC_C),  LSG(KC_V), G(KC_V),                        KC_BSPC,   KC_DEL,    C(KC_A), C(KC_E), XXXXXXX,    XXXXXXX,
                                            _______,   _______,   _______,    _______, _______,   _______
  ),

  [_SYM] = LAYOUT_split_3x6_3_ex2(
    _______, KC_DOT,  KC_PLUS, KC_UNDS, KC_EXLM, KC_PIPE, XXXXXXX,    XXXXXXX, KC_GRV,  KC_QUES, KC_CIRC, KC_DLR,  KC_COMM, XXXXXXX,
    _______, KC_ASTR, KC_EQL,  KC_MINS, KC_0,    KC_AT,   XXXXXXX,    XXXXXXX, KC_AMPR, KC_1,    KC_PERC, KC_HASH, KC_COLN, KC_QUOT,
    _______, KC_8,    KC_6,    KC_4,    KC_2,    KC_BSLS,                      KC_TILD, KC_3,    KC_5,    KC_7,    KC_9,    XXXXXXX,
                                        _______, _______, _______,    _______, _______, _______
  ),

  [_WIN] = LAYOUT_split_3x6_3_ex2(
    XXXXXXX, LCA(KC_U),    LCA(KC_I), XXXXXXX,   MEH(KC_C),    C(KC_1), XXXXXXX,    XXXXXXX, C(KC_4), MEH(KC_C),   A(KC_UP),   XXXXXXX, XXXXXXX, LCA(KC_BSPC),
    XXXXXXX, LCA(KC_LEFT), LCA(KC_D), LCA(KC_G), LCA(KC_RGHT), C(KC_2), XXXXXXX,    XXXXXXX, C(KC_5), LCA(KC_C),   A(KC_DOWN), XXXXXXX, XXXXXXX, MEH(KC_ENT),
    XXXXXXX, LCA(KC_Z),    LCA(KC_X), LCA(KC_V), LCA(KC_B),    C(KC_3),                      C(KC_6), LCA(KC_ENT), XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
                                                 XXXXXXX,      _______, XXXXXXX,    XXXXXXX, _______, XXXXXXX
  ),

  [_FN] = LAYOUT_split_3x6_3_ex2(
    LCG(KC_Q), KC_F1, KC_F2,  KC_F3,  KC_F4,   XXXXXXX, XXXXXXX,    XXXXXXX, LSG(KC_2), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LCG(KC_Q),
    XXXXXXX,   KC_F5, KC_F6,  KC_F7,  KC_F8,   XXXXXXX, XXXXXXX,    XXXXXXX, LSG(KC_3), XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, KC_MPLY,
    XXXXXXX,   KC_F9, KC_F10, KC_F11, KC_F12,  XXXXXXX,                      LSG(KC_4), XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE,
                                      XXXXXXX, XXXXXXX, XXXXXXX,    QK_BOOT, XXXXXXX,   XXXXXXX
  ),

};
