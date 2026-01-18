#include "pico/stdlib.h"
#include "settings.h"

#include "display.h"
#include "hardware.h"

static uint8_t display_state[4];
static bool display_dp_state[4];

// defined at the bottom
const uint8_t COMMONS[4];
const uint8_t SEGMENTS[8];
const uint8_t DIGIT_SEGMENTS[10][7];
const uint8_t DIGIT_SEGMENT_COUNT[10];
const uint8_t DIGIT_SEGMENTS_R[10][7];

void display_main(void) {
    _display_setup_gpio();

    uint32_t val = 0;
    uint16_t tick = 0;
    bool state_dp = false;
    while (true) {
        _display_show();

        if (tick != 0 && tick % (DISPLAY_MAIN_LOOP_TICK_MAX / 2) == 0) {
            if (!state_dp) {
                state_dp = true;
            } else {
                state_dp = false;
            }
            #ifdef ROTATE_THIRD_DISPLAY
            display_set_dp(false, state_dp, state_dp, false);
            #else
            display_set_dp(false, state_dp, false, false);
            #endif
        }

        tick++;
        if (tick >= DISPLAY_MAIN_LOOP_TICK_MAX) {
            tick = 0;
        }
    }
}

void display_set_state(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
    display_state[0] = a;
    display_state[1] = b;
    display_state[2] = c;
    display_state[3] = d;
}

void display_set_dp(bool a, bool b, bool c, bool d) {
    display_dp_state[0] = a;
    display_dp_state[1] = b;
    display_dp_state[2] = c;
    display_dp_state[3] = d;
}

void _display_setup_gpio(void) {
    for (int i = 0; i < 4; i++) {
        gpio_init(COMMONS[i]);
        gpio_set_dir(COMMONS[i], 1);
        gpio_put(COMMONS[i], 1);
    }

    for (int i = 0; i < 8; i++) {
        gpio_init(SEGMENTS[i]);
        gpio_set_dir(SEGMENTS[i], 1);
    }
    _display_all_segments_off();
}

void _display_show(void) {
    for (uint8_t i = 0; i < 4; i++) {
        _display_show_number(i, display_state[i], display_dp_state[i]);
    }
}

void _display_all_segments_off(void) {
    gpio_put(SEGMENT_A, 0);
    gpio_put(SEGMENT_B, 0);
    gpio_put(SEGMENT_C, 0);
    gpio_put(SEGMENT_D, 0);
    gpio_put(SEGMENT_E, 0);
    gpio_put(SEGMENT_F, 0);
    gpio_put(SEGMENT_G, 0);
    gpio_put(SEGMENT_DP, 0);
}

void _display_show_number(uint8_t pos, uint8_t number, bool dp) {
    _display_set_common(pos, true);
    uint8_t segment_count = _display_set_segments(pos, number, dp);

    uint16_t sleep_time = (DIGIT_ON_TIME_US / 8) * segment_count;
    sleep_us(sleep_time);
    _display_all_segments_off();
    _display_set_common(pos, false);
    sleep_us(DIGIT_ON_TIME_US - sleep_time);
}

void _display_set_common(uint8_t pos, bool enabled) {
    gpio_put(COMMONS[pos], !enabled);
}

uint8_t _display_set_segments(uint8_t pos, uint8_t number, bool dp) {
    number = number % 10;
    uint8_t segment_count = DIGIT_SEGMENT_COUNT[number];
    for (uint8_t i = 0; i < segment_count; i++) {
#ifdef ROTATE_THIRD_DISPLAY
        if (pos != 2) {
            gpio_put(DIGIT_SEGMENTS[number][i], 1);
        } else {
            gpio_put(DIGIT_SEGMENTS_R[number][i], 1);
        }
#else
        gpio_put(DIGIT_SEGMENTS[number][i], 1);
#endif
    }
    if (dp) {
#ifdef ROTATE_THIRD_DISPLAY
        if (pos != 2) {
            gpio_put(SEGMENT_DP, 1);
        } else {
            gpio_put(SEGMENT_R_DP, 1);
        }
#else
        gpio_put(SEGMENT_DP, 1);
#endif

        segment_count++;
    }
    return segment_count;
}

// all displays' common GPIOs
const uint8_t COMMONS[4] = {
    COMMON_1,
    COMMON_2,
    COMMON_3,
    COMMON_4,
};

// all displays' segment GPIOs
const uint8_t SEGMENTS[8] = {
    SEGMENT_A,
    SEGMENT_B,
    SEGMENT_C,
    SEGMENT_D,
    SEGMENT_E,
    SEGMENT_F,
    SEGMENT_G,
    SEGMENT_DP,
};

// segments needed for every digit
const uint8_t DIGIT_SEGMENTS[10][7] = {
    {
        // 0
        SEGMENT_A,
        SEGMENT_B,
        SEGMENT_C,
        SEGMENT_D,
        SEGMENT_E,
        SEGMENT_F,
    },
    {
        // 1
        SEGMENT_B,
        SEGMENT_C,
    },
    {
        // 2
        SEGMENT_A,
        SEGMENT_B,
        SEGMENT_D,
        SEGMENT_E,
        SEGMENT_G,
    },
    {
        // 3
        SEGMENT_A,
        SEGMENT_B,
        SEGMENT_C,
        SEGMENT_D,
        SEGMENT_G,
    },
    {
        // 4
        SEGMENT_B,
        SEGMENT_C,
        SEGMENT_F,
        SEGMENT_G,
    },
    {
        // 5
        SEGMENT_A,
        SEGMENT_C,
        SEGMENT_D,
        SEGMENT_F,
        SEGMENT_G,
    },
    {
        // 6
        SEGMENT_A,
        SEGMENT_C,
        SEGMENT_D,
        SEGMENT_E,
        SEGMENT_F,
        SEGMENT_G,
    },
    {
        // 7
        SEGMENT_A,
        SEGMENT_B,
        SEGMENT_C,
    },
    {
        // 8
        SEGMENT_A,
        SEGMENT_B,
        SEGMENT_C,
        SEGMENT_D,
        SEGMENT_E,
        SEGMENT_F,
        SEGMENT_G,
    },
    {
        // 9
        SEGMENT_A,
        SEGMENT_B,
        SEGMENT_C,
        SEGMENT_D,
        SEGMENT_F,
        SEGMENT_G,
    },
};

const uint8_t DIGIT_SEGMENT_COUNT[10] = {
    6, // 0
    2, // 1
    5, // 2
    5, // 3
    4, // 4
    5, // 5
    6, // 6
    3, // 7
    7, // 8
    6  // 9
};

// segments needed for every digit (for rotated third display)
const uint8_t DIGIT_SEGMENTS_R[10][7] = {
    {
        // 0
        SEGMENT_R_A,
        SEGMENT_R_B,
        SEGMENT_R_C,
        SEGMENT_R_D,
        SEGMENT_R_E,
        SEGMENT_R_F,
    },
    {
        // 1
        SEGMENT_R_E,
        SEGMENT_R_F,
    },
    {
        // 2
        SEGMENT_R_A,
        SEGMENT_R_B,
        SEGMENT_R_D,
        SEGMENT_R_E,
        SEGMENT_R_G,
    },
    {
        // 3
        SEGMENT_R_A,
        SEGMENT_R_D,
        SEGMENT_R_E,
        SEGMENT_R_F,
        SEGMENT_R_G,
    },
    {
        // 4
        SEGMENT_R_C,
        SEGMENT_R_E,
        SEGMENT_R_F,
        SEGMENT_R_G,
    },
    {
        // 5
        SEGMENT_R_A,
        SEGMENT_R_C,
        SEGMENT_R_D,
        SEGMENT_R_F,
        SEGMENT_R_G,
    },
    {
        // 6
        SEGMENT_R_A,
        SEGMENT_R_B,
        SEGMENT_R_C,
        SEGMENT_R_D,
        SEGMENT_R_F,
        SEGMENT_R_G,
    },
    {
        // 7
        SEGMENT_R_D,
        SEGMENT_R_E,
        SEGMENT_R_F,
    },
    {
        // 8
        SEGMENT_R_A,
        SEGMENT_R_B,
        SEGMENT_R_C,
        SEGMENT_R_D,
        SEGMENT_R_E,
        SEGMENT_R_F,
        SEGMENT_R_G,
    },
    {
        // 9
        SEGMENT_R_A,
        SEGMENT_R_C,
        SEGMENT_R_D,
        SEGMENT_R_E,
        SEGMENT_R_F,
        SEGMENT_R_G,
    },
};
