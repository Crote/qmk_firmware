#pragma once

#include <stdbool.h>
#include "i2c_master.h"

/* Docs
# Getting started
To enable support for the Pimoroni trackball, place `TRACKBALL_ENABLE = yes`
in your `rules.mk`

The Pimoroni trackball driver has builtin support to use it as a mouse.
If you wish to do so, you should use the rule `POINTING_DEVICE_ENABLE = yes` as well.

# Orientation
For some keyboards, it may be more convenient to rotate the trackball.
Luckily, there is a builtin option to compensate for that.

To determine your orientation, look at the "pimoroni.com" text on the trackball.
In what direction is the dot on the "i" pointing from the text?
Look up the orientation in the following table and set `TRACKBALL_ORIENTATION`
to this value.

Up    0 (default)
Right 1
Down  2
Left  3

# Button behaviour
By default, pressing the trackball will emulate a left mouse click.
If you wish to change this to a different mouse button, you can set
`TRACKBALL_MOUSE_BTN` to a different value.
For example, setting it to `MOUSE_BTN2` will result in a right click.

You can also use the trackball button to take over the role of a key in the key matrix.
To do this, set `TRACKBALL_MATRIX_ROW` and `TRACKBALL_MATRIX_COL` to the desired position.
Users of split keyboards should be aware that the right half is placed _below_
the left half in the matrix, not to the right of it.

# LED
The trackball features an integrated LED.
The easiest way to use it, is by copying the color of an underglow LED.
To configure which LED to mirror, set `TRACKBALL_RGBLIGHT` to the number
corresponding to that LED.

If this value is not defined, the trackball will remain dark.

# Custom code
## Input
The behaviour of the trackball on an input event can be changed by implementing
`void process_trackball_user(trackball_record_t *record)` and `void process_trackball_kb(trackball_record_t *record)`.

`record` contains the `x` and `y` movement, and `pressed` to represent the button state.
It also contains `type`, which is a bit field of `TB_MOVED` and `TB_BUTTON`.
When set, the bits indicate that an event has occured and should be handled.

If your code has handled an event, you can prevent the default behaviour from
executing by clearing the corresponding bit.

### Intercept movement
This example uses the trackball movement to control underglow color.
Note the last line, preventing the default behavour.
```
process_trackball_user(trackball_record_t *record) {
    if (record->type & TB_MOVED) {
        for (int i = record->x; i < 0; i++) {
            rgblight_increase_hue();
        }
        for (int i = record->x; i > 0; i--) {
            rgblight_decrease_hue();
        }
        for (int i = record->y; i < 0; i++) {
            rgblight_increase_sat();
        }
        for (int i = record->y; i > 0; i--) {
            rgblight_decrease_sat();
        }
        record->type &= ~TB_MOVED;
    }
}
```

### Custom acceleration
This example demonstrates how to change a movement while keeping the default behavour.
When the `M_FAST` key is held, the mouse will move faster.
```
enum custom_keycodes {
    M_FAST = SAFE_RANGE,
};

bool go_fast;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case M_FAST:
        go_fast = record->event.pressed;
        return false;
      default:
        break;
    }
    return true;
}

process_trackball_user(trackball_record_t *record) {
    if (record->type & TB_MOVED) {
        if (go_fast) {
            record->x *= 20;
            record->y *= 20;
        }
    }
}
```

## LED
You can use one of the following functions to control the integrated LED:
- `i2c_status_t trackball_setrgb(uint8_t r, uint8_t g, uint8_t b);`
- `i2c_status_t trackball_sethsv(uint8_t h, uint8_t s, uint8_t v);`

# Advanced configuration
I2C address: `TRACKBALL_ADDRESS` (default: 0x0A)
I2C timeout: `TRACKBALL_TIMEOUT` (default: 100ms)

*/

#ifndef TRACKBALL_ADDRESS
    #define TRACKBALL_ADDRESS 0x0A
#endif

#ifndef TRACKBALL_TIMEOUT
    #define TRACKBALL_TIMEOUT 100
#endif

#ifndef TRACKBALL_ORIENTATION
    #define TRACKBALL_ORIENTATION 0
#endif

#ifndef TRACKBALL_MOUSE_BTN
    #define TRACKBALL_MOUSE_BTN MOUSE_BTN1
#endif

typedef enum {
    TB_MOVED  = 0b01,
    TB_BUTTON = 0b10,
    TB_BOTH   = 0b11,
} trackball_flags_t;

typedef struct {
    int8_t x;
    int8_t y;
    bool pressed;
    trackball_flags_t type;
} trackball_record_t;

void trackball_init(void);
void trackball_task(void);

i2c_status_t trackball_setrgb(uint8_t r, uint8_t g, uint8_t b);
i2c_status_t trackball_sethsv(uint8_t h, uint8_t s, uint8_t v);

__attribute__((weak)) void process_trackball_kb(trackball_record_t *record);
__attribute__((weak)) void process_trackball_user(trackball_record_t *record);
