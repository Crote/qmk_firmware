/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
 
#ifdef ENCODER_ENABLE
  // Encoder resolution defaults to 4, which means we get one event every
  // four pulses. This is useful to sync with encoder indents, but
  // we use linear encoders, so use the lowest resolution possible.
  #define ENCODER_RESOLUTION 1
  #define ENCODER_TICKS 72
  #define ENCODER_COUNT 2

  // Default Kyria direction is wrong
  #define ENCODER_DIRECTION_FLIP
#endif

#ifdef RGBLIGHT_ENABLE
  //#define RGBLIGHT_EFFECT_BREATHING
  //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
  //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  //#define RGBLIGHT_EFFECT_SNAKE
  //#define RGBLIGHT_EFFECT_KNIGHT
  //#define RGBLIGHT_EFFECT_CHRISTMAS
  //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
  //#define RGBLIGHT_EFFECT_RGB_TEST
  //#define RGBLIGHT_EFFECT_ALTERNATING
  //#define RGBLIGHT_EFFECT_TWINKLE
  //#define RGBLIGHT_EFFECT_STATIC_GRADIENT

  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 127

  // Turn off underglow when system goes to sleep
  // TODO: does not work??
  #define RGBLIGHT_SLEEP
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
#define SPLIT_USB_DETECT
#define NO_USB_STARTUP_CHECK

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS

// Use I2C as transport
#undef SOFT_SERIAL_PIN
#define USE_I2C
// By default I2C speed is 100khz for split, 400khz for solo
// Our hardware can easily handle 400k,
// so this greatly increases the scan frequency
#define F_SCL 400000UL

// My switches do not lock
#undef LOCKING_SUPPORT_ENABLE

#define TRACKBALL_MATRIX_ROW 6
#define TRACKBALL_MATRIX_COL 1
#define TRACKBALL_RGBLIGHT 10
#define TRACKBALL_ORIENTATION 2
