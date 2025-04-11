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
    //QWERTY Home row mods
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
    //Dvorak Keys  Home row mods
    CKC_OD,
    CKC_ED,
    CKC_UD,
    CKC_HD,
    CKC_TD,
    CKC_ND,
    CKC_SD,
    //non-homerow keys
    CKC_SCLND,
    CKC_QD,
    CKC_VD,
    CKC_ZD,
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
      //Dvorak Home Row Mods
//      SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI, 2)
      SMTD_MT(CKC_OD, KC_O, KC_LEFT_ALT, 2)  
      SMTD_MT(CKC_ED, KC_E, KC_LEFT_CTRL, 2)   
      SMTD_MT(CKC_UD, KC_U, KC_LSFT, 2)
      SMTD_MT(CKC_HD, KC_H, KC_LSFT, 2)
      SMTD_MT(CKC_TD, KC_T, KC_LEFT_CTRL, 2)
      SMTD_MT(CKC_ND, KC_N, KC_LEFT_ALT, 2)
      SMTD_MT(CKC_SD, KC_S, KC_LEFT_GUI, 2)
      //Non homerow keys       
      SMTD_LT(CKC_Z, KC_Z, U_BUTTON, 2)
      SMTD_LT(CKC_X, KC_X, KC_RIGHT_ALT, 2)
      SMTD_LT(CKC_DOT, KC_DOT, KC_RIGHT_ALT, 2)
      SMTD_LT(CKC_SLSH, KC_SLSH, U_BUTTON, 2)
      //Non homerow keys dvorak
      SMTD_LT(CKC_SCLND, KC_SCLN, U_BUTTON, 2)  
      SMTD_LT(CKC_QD, KC_Q, KC_RIGHT_ALT, 2)
      SMTD_LT(CKC_VD, KC_V, KC_RIGHT_ALT, 2)
      SMTD_LT(CKC_ZD, KC_Z, U_BUTTON, 2)
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
  [U_BASE] = LAYOUT_split_3x6_3_ex2(
   KC_ESC,  KC_Q,   KC_W,  KC_F,    KC_P,    KC_B, QK_LLCK, QK_LLCK,     KC_J,    KC_L,    KC_U,    KC_Y,  KC_SCLN, KC_BSPC,
   KC_TAB, CKC_A,  CKC_R, CKC_S,   CKC_T,    KC_G, QK_LOCK, QK_LOCK,     KC_M,   CKC_N,   CKC_E,   CKC_I,    CKC_O, KC_QUOT,
  KC_LSFT, CKC_Z,  CKC_X,  KC_C,    KC_D,    KC_V,                       KC_K,    KC_H, KC_COMM, CKC_DOT, CKC_SLSH, KC_RSFT,
//                                 CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL 
                        LT(U_SYM,KC_ESC),  LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC),  LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)
  ),
//Put numbers on right hand
  [U_NUM] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK, KC_LBRC,    KC_7, KC_8, KC_9, KC_RBRC, KC_BSPC,
   KC_TAB,         CKC_A,          CKC_R,            CKC_S,           CKC_T,             KC_NO, QK_LOCK, QK_LOCK, KC_COLN,    KC_4, KC_5, KC_6,  KC_EQL, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR, TD(U_TD_U_MOUSE),  TD(U_TD_U_NUM),             KC_NO,                    KC_GRV,    KC_1, KC_2, KC_3, KC_BSLS, KC_RSFT,
                                                                      KC_NO,             KC_NO,   KC_NO,  KC_DOT,    KC_0, KC_MINS 
  ),
  [U_SYM] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK, KC_LBRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
   KC_TAB,         CKC_A,          CKC_R,            CKC_S,           CKC_T,             KC_NO, QK_LOCK, QK_LOCK, KC_SCLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR,   TD(U_TD_U_FUN),  TD(U_TD_U_SYM),             KC_NO,                   KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, KC_RSFT,
                                                                      KC_NO,             KC_NO,   KC_NO, KC_LPRN, KC_RPRN, KC_UNDS 
  ),
  [U_FUN] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, KC_F12, KC_F7, KC_F8,  KC_F9, KC_PSCR, QK_LLCK, QK_LLCK, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE), TD(U_TD_U_DVORAK), KC_BSPC,
  KC_CAPS, KC_F11, KC_F4, KC_F5,  KC_F6, KC_SCRL, QK_LOCK, QK_LOCK,         CKC_N,          CKC_E,            CKC_I,           CKC_O,             KC_NO, KC_QUOT,
  KC_LSFT, KC_F10, KC_F1, KC_F2,  KC_F3, KC_PAUS,                           KC_NO,        KC_ALGR,   TD(U_TD_U_FUN),  TD(U_TD_U_SYM),             KC_NO, KC_RSFT,
                                 KC_APP,  KC_SPC,  KC_TAB,   KC_NO,         KC_NO,          KC_NO
  ),
  [U_BUTTON] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, U_UND, U_CUT, U_CPY,   U_PST,   U_RDO, QK_LLCK, QK_LLCK,   U_RDO,   U_PST, U_CPY, U_CUT, U_UND, KC_BSPC,
   KC_TAB, CKC_A, CKC_R, CKC_S,   CKC_T,   KC_NO, QK_LOCK, QK_LOCK,   KC_NO,   CKC_N, CKC_E, CKC_I, CKC_O, KC_QUOT,
  KC_LSFT, U_UND, U_CUT, U_CPY,   U_PST,   U_RDO,                     U_RDO,   U_PST, U_CPY, U_CUT, U_UND, KC_RSFT,
                                KC_BTN3, KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, KC_BTN3 
  ),
  [U_NAV] = LAYOUT_split_3x6_3_ex2(                              
    KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK,  KC_INS, KC_HOME,   KC_UP,  KC_END, KC_PGUP, KC_BSPC,
    KC_TAB,         CKC_A,          CKC_R,            CKC_S,           CKC_T,             KC_NO, QK_LOCK, QK_LOCK, CW_TOGG, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_QUOT,
   KC_LSFT,         KC_NO,        KC_ALGR, TD(U_TD_U_MEDIA),  TD(U_TD_U_NAV),             KC_NO,                     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_RSFT,
                                                                       KC_NO,             KC_NO,   KC_NO,  KC_ENT, KC_BSPC,  KC_DEL 
   ),  
//  [U_NAV] = LAYOUT_split_3x6_3_ex2(                              
//   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), TD(U_TD_U_BASE), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_BSPC,
//   KC_TAB,         CKC_A,          CKC_R,            CKC_S,           CKC_T,             KC_NO, QK_LOCK, QK_LOCK, CW_TOGG, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_QUOT,
//  KC_LSFT,         KC_NO,        KC_ALGR, TD(U_TD_U_MEDIA),  TD(U_TD_U_NAV),             KC_NO,                    KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_RSFT,
//                                                                      KC_NO,             KC_NO,   KC_NO,  KC_ENT, KC_BSPC,  KC_DEL 
//  ),
  [U_MOUSE] = LAYOUT_split_3x6_3_ex2(
    KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK,   KC_NO, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, KC_BSPC,
    KC_TAB,         CKC_A,          CKC_R,            CKC_S,            CKC_T,             KC_NO, QK_LOCK, QK_LOCK,   KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_QUOT,
   KC_LSFT,         KC_NO,        KC_ALGR,   TD(U_TD_U_NUM), TD(U_TD_U_MOUSE),             KC_NO,                     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_RSFT,
                                                                      KC_BTN3,           KC_BTN1, KC_BTN2,   KC_NO,   KC_NO,   KC_NO 
  ),
//  [U_MOUSE] = LAYOUT_split_3x6_3_ex2(
//    KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_BSPC,
//    KC_TAB,         CKC_A,          CKC_R,            CKC_S,            CKC_T,             KC_NO, QK_LOCK, QK_LOCK,   KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_QUOT,
//   KC_LSFT,         KC_NO,        KC_ALGR,   TD(U_TD_U_NUM), TD(U_TD_U_MOUSE),             KC_NO,                     KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_RSFT,
//                                                                      KC_BTN3,           KC_BTN1, KC_BTN2,   KC_NO,   KC_NO,   KC_NO 
//  ),
  [U_EXTRA] = LAYOUT_split_3x6_3_ex2(
   KC_ESC,  KC_Q,   KC_W,  KC_E,    KC_R,    KC_T, QK_LLCK, QK_LLCK,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P, KC_BSPC,
   KC_TAB, CKC_A, CKC_SE, CKC_D,   CKC_F,    KC_G, QK_LOCK, QK_LOCK,     KC_H,   CKC_J,   CKC_K,   CKC_L, CKC_SCLN, KC_QUOT,
  KC_LSFT, CKC_Z,  CKC_X,  KC_C,    KC_V,    KC_B,                       KC_N,    KC_M, KC_COMM, CKC_DOT, CKC_SLSH, KC_RSFT,
//                                 CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL
                        LT(U_SYM,KC_ESC),  LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC),  LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)                                  
  ),
  [U_MEDIA] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_BSPC,
   KC_TAB,         CKC_A,          CKC_R,            CKC_S,            CKC_T,             KC_NO, QK_LOCK, QK_LOCK,   KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR,   TD(U_TD_U_NAV), TD(U_TD_U_MEDIA),             KC_NO,                   OU_AUTO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_RSFT,
                                                                     KC_MSTP,           KC_MPLY, KC_MUTE,   KC_NO,   KC_NO,   KC_NO
  ),
  [U_TAP] = LAYOUT_split_3x6_3_ex2(
   KC_ESC, KC_Q, KC_W, KC_F,   KC_P,   KC_B,  TD(U_TD_U_BASE),    TD(U_TD_BOOT),    KC_J,   KC_L,    KC_U,   KC_Y, KC_SCLN, KC_BSPC,  
   KC_TAB, KC_A, KC_R, KC_S,   KC_T,   KC_G, TD(U_TD_U_EXTRA), TD(U_TD_U_DVORAK),    KC_M,   KC_N,    KC_E,   KC_I,    KC_O, KC_QUOT,
  KC_LSFT, KC_Z, KC_X, KC_C,   KC_D,   KC_V,                                        KC_K,   KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                             KC_ESC, KC_TAB,           KC_ENT,           KC_SPC, KC_BSPC, KC_DEL
  ),                                                             
  [U_DVORAK] = LAYOUT_split_3x6_3_ex2(
    KC_ESC,   KC_QUOT, KC_COMM, KC_DOT,    KC_P,    KC_Y, QK_LLCK, QK_LLCK,     KC_F,    KC_G,   KC_C,   KC_R,   KC_L, KC_BSPC,
    KC_TAB,     CKC_A,  CKC_OD, CKC_ED,  CKC_UD,    KC_I, QK_LOCK, QK_LOCK,     KC_D,  CKC_HD, CKC_TD, CKC_ND, CKC_SD, KC_SLSH,
   KC_LSFT, CKC_SCLND,  CKC_QD,   KC_J,    KC_K,    KC_X,                       KC_B,    KC_M,   KC_W, CKC_VD, CKC_ZD, KC_RSFT,
//                                        CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL 
                               LT(U_SYM,KC_ESC),  LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC),  LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)
 ), 
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  for (uint8_t i = led_min; i < led_max; i++) {
    uint8_t layer = get_highest_layer(layer_state|default_layer_state);
    switch(layer) {
        case U_EXTRA:
          rgb_matrix_set_color(i, RGB_GREEN);
          break;
        case U_DVORAK:
          rgb_matrix_set_color(i, RGB_BLUE);
          break;
        case U_SYM:
          for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
              for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                  uint8_t index = g_led_config.matrix_co[row][col];
              
                  if (index >= led_min && index < led_max && index != NO_LED &&
                  keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GOLDENROD);
                  }
                  else if (index >= led_min && index < led_max && index != NO_LED &&
                    keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_NO) {
                    rgb_matrix_set_color(index, RGB_BLACK);
                  }
              }
          }        
          break;             
        case U_NUM:
          for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
              for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                  uint8_t index = g_led_config.matrix_co[row][col];
              
                  if (index >= led_min && index < led_max && index != NO_LED &&
                  keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                      rgb_matrix_set_color(index, RGB_SPRINGGREEN);
                  }
                  else if (index >= led_min && index < led_max && index != NO_LED &&
                    keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_NO) {
                    rgb_matrix_set_color(index, RGB_BLACK);
                  }               
              }
          }     
          break;        
        case U_NAV: 
          for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
              for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                  uint8_t index = g_led_config.matrix_co[row][col];
              
                  if (index >= led_min && index < led_max && index != NO_LED &&
                  keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                      rgb_matrix_set_color(index, RGB_CORAL);
                  }
                  else if (index >= led_min && index < led_max && index != NO_LED &&
                    keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_NO) {
                    rgb_matrix_set_color(index, RGB_BLACK);
                  }              
              }
          }     
          break;        
        case U_FUN:             
          for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
            
                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_YELLOW);
                }
                else if (index >= led_min && index < led_max && index != NO_LED &&
                  keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_NO) {
                  rgb_matrix_set_color(index, RGB_BLACK);
                }             
            }
          }     
          break;        
        case U_MOUSE:
        case U_MEDIA:
        case U_BASE:
        case U_TAP:
        case U_BUTTON:
        default:
            break;
    }
  }
  return false;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_ppRGHT, KC_LEFT), },
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
        case U_DVORAK :
            oled_write("DVORAK Layer", false);
            break;
    }
  }
  
  return false;
}

#endif
