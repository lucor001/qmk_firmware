/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "layers.h"

// Define custom keycodes for the home row mods
enum custom_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_R,
    CKC_S,
    CKC_T,
    CKC_O,
    CKC_I,
    CKC_E,
    CKC_N,
    CKC_SE,
    CKC_D,
    CKC_F,
    CKC_J,
    CKC_K,
    CKC_L,
    CKC_SCLN,
    //non-homerow keys
    CKC_Z,
    CKC_X,
    CKC_DOT,
    CKC_SLSH,    
    //thumb keys
    CKC_ESC,
    CKC_TAB,
    CKC_ENT,
    CKC_SPC,
    CKC_BSPC,
    CKC_DEL,
    SMTD_KEYCODES_END,
};

#include "sm_td.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_smtd(keycode, record)) return false;

  return true;
}

// Enumerate all of the tap dance keys
enum {
  U_TD_BOOT,
#define KEYBOARD_X(LAYER, STRING) U_TD_U_##LAYER,
KEYBOARD_LAYER_LIST
#undef KEYBOARD_X
};

// Implement the boot tap dance 
void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
};

// Implement the remaining tap dances
#define KEYBOARD_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
if (state->count == 2) { \
  default_layer_set((layer_state_t)1 << U_##LAYER); \
} \
}
KEYBOARD_LAYER_LIST
#undef KEYBOARD_X

// Create the array of tap dance functions
tap_dance_action_t tap_dance_actions[] = {
  [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define KEYBOARD_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
KEYBOARD_LAYER_LIST
#undef KEYBOARD_X
};

// SM Tap Dance feature to implement the home row mods
void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
  switch (keycode) {
      //COLMAK-DH Home Row Mods
      SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI, 2)
      SMTD_MT(CKC_R, KC_R, KC_LEFT_ALT, 2)
      SMTD_MT(CKC_S, KC_S, KC_LEFT_CTRL, 2)
      SMTD_MT(CKC_T, KC_T, KC_LSFT, 2)
      SMTD_MT(CKC_N, KC_N, KC_LSFT, 2)
      SMTD_MT(CKC_E, KC_E, KC_LEFT_CTRL, 2)
      SMTD_MT(CKC_I, KC_I, KC_LEFT_ALT, 2)
      SMTD_MT(CKC_O, KC_O, KC_LEFT_GUI, 2)
      //QWERTY Home Row Mods
//        SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI)
      SMTD_MT(CKC_SE, KC_S, KC_LEFT_ALT, 2)
      SMTD_MT(CKC_D, KC_D, KC_LEFT_CTRL, 2)
      SMTD_MT(CKC_F, KC_F, KC_LSFT, 2)
      SMTD_MT(CKC_J, KC_J, KC_LSFT, 2)
      SMTD_MT(CKC_K, KC_K, KC_LEFT_CTRL, 2)
      SMTD_MT(CKC_L, KC_L, KC_LEFT_ALT, 2)
      SMTD_MT(CKC_SCLN, KC_SCLN, KC_LEFT_GUI, 2)
      //Non homerow keys       
      SMTD_LT(CKC_Z, KC_Z, U_BUTTON, 2)
      SMTD_LT(CKC_X, KC_X, KC_RIGHT_ALT, 2)
      SMTD_LT(CKC_DOT, KC_DOT, KC_RIGHT_ALT, 2)
      SMTD_LT(CKC_SLSH, KC_SLSH, U_BUTTON, 2)
      //Thumb keys
      SMTD_LT(CKC_ESC, KC_ESC, U_SYM, 2)
      SMTD_LT(CKC_TAB, KC_TAB, U_NAV, 2)
      SMTD_LT(CKC_ENT, KC_ENT, U_NUM, 2)
      SMTD_LT(CKC_SPC, KC_SPC, U_MOUSE, 2)
      SMTD_LT(CKC_BSPC, KC_BSPC, U_MEDIA, 2)
      SMTD_LT(CKC_DEL, KC_DEL, U_FUN, 2)
  }
};

// Map the redo/paste/copy/cut/undo functions
#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

// Keymap, leveraged Miryoku heavily but swapped action hand to right hand, updated for a Corne v4.1 3x6+2 keyboard

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//COLMAK-DH layout with home row special keys
    //Expanded Miryoku for this keyboard, adds outside columns and 4 keys in the middle
//   KC_TAB,             CKC_A,         CKC_R, CKC_S,            CKC_T,             KC_G,          QK_LOCK,            QK_LOCK,                KC_M,            CKC_N,   CKC_E,          CKC_I,                CKC_O, KC_QUOT,

  [U_BASE] = LAYOUT_split_3x6_3_ex2(
   KC_ESC,  KC_Q,   KC_W,  KC_F,    KC_P,    KC_B, QK_LOCK, QK_LOCK,     KC_J,    KC_L,    KC_U,    KC_Y,  KC_SCLN, KC_BSPC,
   KC_TAB, CKC_A,  CKC_R, CKC_S,   CKC_T,    KC_G, QK_LLCK, QK_LLCK,     KC_M,   CKC_N,   CKC_E,   CKC_I,    CKC_O, KC_QUOT,
//   KC_TAB,      LGUI_T(KC_A),  LALT_T(KC_R), LCTL_T(KC_S),     LSFT_T(KC_T),             KC_G,            QK_LLCK,             QK_LLCK,                KC_M,     LSFT_T(KC_N), LCTL_T(KC_E),   LALT_T(KC_I),         LGUI_T(KC_O), KC_QUOT,
  KC_LSFT, CKC_Z,  CKC_X,  KC_C,    KC_D,    KC_V,                       KC_K,    KC_H, KC_COMM, CKC_DOT, CKC_SLSH, KC_RSFT,
                                 CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL 
  ),
//Put numbers on right hand
  [U_NUM] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE), KC_NO, QK_LOCK, QK_LOCK, KC_LBRC,    KC_7, KC_8, KC_9, KC_RBRC, KC_BSPC,
   KC_TAB,         CKC_A,          CKC_R,            CKC_S,           CKC_T, KC_NO, QK_LLCK, QK_LLCK, KC_COLN,    KC_4, KC_5, KC_6,  KC_EQL, KC_QUOT,
//   KC_TAB,  LGUI_T(KC_A),   LALT_T(KC_R),     LCTL_T(KC_S),    LSFT_T(KC_T), KC_NO, QK_LLCK, QK_LLCK, KC_COLN,    KC_4, KC_5, KC_6,  KC_EQL, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR,   TD(U_TD_U_FUN),  TD(U_TD_U_NUM), KC_NO,                    KC_GRV,    KC_1, KC_2, KC_3, KC_BSLS, KC_RSFT,
                                                                      KC_NO, KC_NO,   KC_NO, KC_DOT,     KC_0, KC_MINS 
  ),
  [U_SYM] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE), KC_NO, QK_LOCK, QK_LOCK, KC_LBRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
   KC_TAB,         CKC_A,          CKC_R,            CKC_S,           CKC_T, KC_NO, QK_LLCK, QK_LLCK, KC_SCLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, KC_QUOT,
//   KC_TAB,  LGUI_T(KC_A),   LALT_T(KC_R),     LCTL_T(KC_S),    LSFT_T(KC_T), KC_NO, QK_LLCK, QK_LLCK, KC_SCLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR, TD(U_TD_U_MOUSE),  TD(U_TD_U_SYM), KC_NO,                   KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, KC_RSFT,
                                                                      KC_NO, KC_NO,   KC_NO, KC_LPRN, KC_RPRN, KC_UNDS 
  ),
  [U_FUN] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, KC_F12, KC_F7, KC_F8,  KC_F9, KC_PSCR, QK_LOCK, QK_LOCK, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE),   KC_NO, KC_BSPC,
   KC_TAB, KC_F11, KC_F4, KC_F5,  KC_F6, KC_SCRL, QK_LLCK, QK_LLCK,         CKC_N,          CKC_E,            CKC_I,           CKC_O,   KC_NO, KC_QUOT,
//   KC_TAB, KC_F11, KC_F4, KC_F5,  KC_F6, KC_SCRL, QK_LLCK, QK_LLCK,  LGUI_T(KC_A),   LALT_T(KC_R),     LCTL_T(KC_S),    LSFT_T(KC_T),   KC_NO, KC_QUOT,
  KC_LSFT, KC_F10, KC_F1, KC_F2,  KC_F3, KC_PAUS,                           KC_NO,        KC_ALGR,   TD(U_TD_U_NUM),  TD(U_TD_U_FUN),   KC_NO, KC_RSFT,
                                  KC_NO,   KC_NO,   KC_NO,  KC_APP,        KC_SPC,         KC_TAB 
  ),
  [U_MOUSE] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   KC_NO, QK_LOCK, QK_LOCK,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_BSPC,
   KC_TAB,         CKC_A,          CKC_R,            CKC_S,            CKC_T,   KC_NO, QK_LLCK, QK_LLCK,   KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_QUOT,
//   KC_TAB,  LGUI_T(KC_A),   LALT_T(KC_R),     LCTL_T(KC_S),     LSFT_T(KC_T),   KC_NO, QK_LLCK, QK_LLCK,   KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR,   TD(U_TD_U_SYM), TD(U_TD_U_MOUSE),   KC_NO,                     KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_RSFT,
                                                                     KC_BTN3, KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, KC_BTN3 
  ),
  [U_BUTTON] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, U_UND, U_CUT, U_CPY,   U_PST,   U_RDO, QK_LOCK, QK_LOCK,   U_RDO,   U_PST, U_CPY, U_CUT, U_UND, KC_BSPC,
   KC_TAB, CKC_A, CKC_R, CKC_S,   CKC_T,   KC_NO, QK_LLCK, QK_LLCK,   KC_NO,   CKC_N, CKC_E, CKC_I, CKC_O, KC_QUOT,
//   KC_TAB, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S),   LSFT_T(KC_T),    KC_G, QK_LLCK, QK_LLCK,    KC_M, LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), KC_QUOT,
  KC_LSFT, U_UND, U_CUT, U_CPY,   U_PST,   U_RDO,                     U_RDO,   U_PST, U_CPY, U_CUT, U_UND, KC_RSFT,
                                KC_BTN3, KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, KC_BTN3 
  ),
  [U_NAV] = LAYOUT_split_3x6_3_ex2(                              
   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE), KC_NO, QK_LOCK, QK_LOCK,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_BSPC,
   KC_TAB,         CKC_A,          CKC_R,            CKC_S,           CKC_T, KC_NO, QK_LLCK, QK_LLCK, CW_TOGG, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_QUOT,
//   KC_TAB,  LGUI_T(KC_A),   LALT_T(KC_R),     LCTL_T(KC_S),    LSFT_T(KC_T), KC_NO, QK_LLCK, QK_LLCK, CW_TOGG, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_QUOT,
  KC_LSFT,       KC_ALGR, TD(U_TD_U_NUM),   TD(U_TD_U_NAV),           KC_NO, KC_NO,                    KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_RSFT,
                                                                      KC_NO, KC_NO,   KC_NO,  KC_ENT, KC_BSPC,  KC_DEL 
  ),
  [U_EXTRA] = LAYOUT_split_3x6_3_ex2(
   KC_ESC,  KC_Q,   KC_W,  KC_E,    KC_R,    KC_T, QK_LOCK, QK_LOCK,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P, KC_BSPC,
   KC_TAB, CKC_A, CKC_SE, CKC_D,   CKC_F,    KC_G, QK_LLCK, QK_LLCK,     KC_H,   CKC_J,   CKC_K,   CKC_L, CKC_SCLN, KC_QUOT,
//   KC_TAB,      LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D),     LSFT_T(KC_F),             KC_G,          QK_LLCK,            QK_LLCK,                KC_H,     LSFT_T(KC_J), LCTL_T(KC_K),   LALT_T(KC_L),      LGUI_T(KC_QUOT), KC_QUOT,
  KC_LSFT, CKC_Z,  CKC_X,  KC_C,    KC_V,    KC_B,                       KC_N,    KC_M, KC_COMM, CKC_DOT, CKC_SLSH, KC_RSFT,
                                 CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL 
  ),
  [U_MEDIA] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   KC_NO, QK_LOCK, QK_LOCK, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_BSPC,
   KC_TAB,         CKC_A,          CKC_R,            CKC_S,            CKC_T,   KC_NO, QK_LLCK, QK_LLCK,   KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_QUOT,
//   KC_TAB,  LGUI_T(KC_A),   LALT_T(KC_R),     LCTL_T(KC_S),     LSFT_T(KC_T),   KC_NO, QK_LLCK, QK_LLCK,   KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR,   TD(U_TD_U_FUN), TD(U_TD_U_MEDIA),   KC_NO,                   OU_AUTO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_RSFT,
                                                                       KC_NO,   KC_NO,   KC_NO, KC_MSTP, KC_MPLY, KC_MUTE 
  ),
  [U_TAP] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, KC_Q, KC_W, KC_F,   KC_P,   KC_B,  TD(U_TD_U_BASE), TD(U_TD_BOOT),    KC_J,   KC_L,    KC_U,   KC_Y, KC_SCLN, KC_BSPC,
   KC_TAB, KC_A, KC_R, KC_S,   KC_T,   KC_G, TD(U_TD_U_EXTRA),         KC_NO,    KC_M,   KC_N,    KC_E,   KC_I,    KC_O, KC_QUOT,
  KC_LSFT, KC_Z, KC_X, KC_C,   KC_D,   KC_V,                                     KC_K,   KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                             KC_ESC, KC_TAB,           KC_ENT,        KC_SPC, KC_BSPC, KC_DEL
  ),                                                             
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif

// OLED
#ifdef OLED_ENABLE
 
// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90; 
}

//oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//  if (!is_keyboard_master()) {
//      return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
//  }
//
//  return rotation;
//}

// Draw to OLED
bool oled_task_user() {
  if (is_keyboard_master()) {
    // Set cursor position
    oled_set_cursor(0, 1);

    // Switch on current active layer
    switch (get_highest_layer(layer_state)) {
        case U_BASE :
            oled_write("Base Layer", false);
            break;
        case U_NUM :
            oled_write("Number Layer", false);
            break;
        case U_NAV : 
            oled_write("Navigation Layer", false);
            break;
        case U_SYM :
            oled_write("Symbol Layer", false);
            break;
        case U_MOUSE :
            oled_write("Mouse Layer", false);
            break;
        case U_MEDIA :
            oled_write("Media Layer", false);
            break;
        case U_BUTTON :
            oled_write("Button Layer", false);
            break;
        case U_TAP :
            oled_write("Tap Layer", false);
            break;            
        case U_EXTRA :
            oled_write("QWERTY Layer", false);
            break;
    }
  }
  
  return false;
}

#endif




//enum layers {
//    U_BASE,
//    U_NUM,
//    U_NAV,
//    U_FUN,
//    U_SYM,
//    U_MOUSE,
//    U_MEDIA,
//    U_BUTTON,
//    U_TAP,
//    U_EXTRA
//};
//
//enum {
//    U_TD_U_BASE,
//    U_TD_U_NUM,
//    U_TD_U_NAV,
//    U_TD_U_TAP,
//    U_TD_U_EXTRA,
//    U_TD_U_SYM,
//    U_TD_U_MOUSE,
//    U_TD_U_FUN,
//    U_TD_U_MEDIA,
//    U_TD_BOOT
//};
//
//void u_td_fn_u_base(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 2) {
//      default_layer_set((layer_state_t)1 << U_BASE);
//    }
//};
//
//void u_td_fn_u_num(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 2) {
//      default_layer_set((layer_state_t)1 << U_NUM);
//    }
//};
//
//void u_td_fn_u_nav(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 2) {
//      default_layer_set((layer_state_t)1 << U_NAV);
//    }
//};
//
//void u_td_fn_u_tap(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 2) {
//      default_layer_set((layer_state_t)1 << U_TAP);
//    }
//};
//
//void u_td_fn_u_extra(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 2) {
//      default_layer_set((layer_state_t)1 << U_EXTRA);
//    }
//};
//
//void u_td_fn_u_sym(tap_dance_state_t *state, void *user_data) {
//  if (state->count == 2) {
//    default_layer_set((layer_state_t)1 << U_SYM);
//  }
//};
//void u_td_fn_u_mouse(tap_dance_state_t *state, void *user_data) {
//  if (state->count == 2) {
//    default_layer_set((layer_state_t)1 << U_MOUSE);
//  }
//};
//
//void u_td_fn_u_fun(tap_dance_state_t *state, void *user_data) {
//  if (state->count == 2) {
//    default_layer_set((layer_state_t)1 << U_FUN);
//  }
//};
//
//void u_td_fn_u_media(tap_dance_state_t *state, void *user_data) {
//  if (state->count == 2) {
//    default_layer_set((layer_state_t)1 << U_MEDIA);
//  }
//};
//
//void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 2) {
//      reset_keyboard();
//    }
//};
//
//tap_dance_action_t tap_dance_actions[] = {
//    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
//    [U_TD_U_BASE] = ACTION_TAP_DANCE_FN(u_td_fn_u_base),
//    [U_TD_U_NUM] = ACTION_TAP_DANCE_FN(u_td_fn_u_num),
//    [U_TD_U_NAV] = ACTION_TAP_DANCE_FN(u_td_fn_u_nav),
//    [U_TD_U_TAP] = ACTION_TAP_DANCE_FN(u_td_fn_u_tap),
//    [U_TD_U_EXTRA] = ACTION_TAP_DANCE_FN(u_td_fn_u_extra),
//    [U_TD_U_SYM] = ACTION_TAP_DANCE_FN(u_td_fn_u_sym),
//    [U_TD_U_MOUSE] = ACTION_TAP_DANCE_FN(u_td_fn_u_mouse),
//    [U_TD_U_FUN] = ACTION_TAP_DANCE_FN(u_td_fn_u_fun),
//    [U_TD_U_MEDIA] = ACTION_TAP_DANCE_FN(u_td_fn_u_media),
//};