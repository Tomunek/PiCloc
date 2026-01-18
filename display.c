#include "pico/stdlib.h"

#include "display.h"
#include "display_hw.h"

static uint8_t display_state[4];
static bool display_dp_state[4];

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
            display_set_dp(false, state_dp, state_dp, false);
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
    gpio_init(COMMON_1);
    gpio_init(COMMON_2);
    gpio_init(COMMON_3);
    gpio_init(COMMON_4);

    gpio_set_dir(COMMON_1, 1);
    gpio_set_dir(COMMON_2, 1);
    gpio_set_dir(COMMON_3, 1);
    gpio_set_dir(COMMON_4, 1);

    gpio_put(COMMON_1, 1);
    gpio_put(COMMON_2, 1);
    gpio_put(COMMON_3, 1);
    gpio_put(COMMON_4, 1);

    gpio_init(SEGMENT_A);
    gpio_init(SEGMENT_B);
    gpio_init(SEGMENT_C);
    gpio_init(SEGMENT_D);
    gpio_init(SEGMENT_E);
    gpio_init(SEGMENT_F);
    gpio_init(SEGMENT_G);
    gpio_init(SEGMENT_DP);

    gpio_set_dir(SEGMENT_A, 1);
    gpio_set_dir(SEGMENT_B, 1);
    gpio_set_dir(SEGMENT_C, 1);
    gpio_set_dir(SEGMENT_D, 1);
    gpio_set_dir(SEGMENT_E, 1);
    gpio_set_dir(SEGMENT_F, 1);
    gpio_set_dir(SEGMENT_G, 1);
    gpio_set_dir(SEGMENT_DP, 1);

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
        if (pos != 2) {
            gpio_put(DIGIT_SEGMENTS[number][i], 1);
        } else {
            gpio_put(DIGIT_SEGMENTS_R[number][i], 1);
        }
    }
    if (dp) {
        if (pos != 2) {
            gpio_put(SEGMENT_DP, 1);
        } else {
            gpio_put(SEGMENT_R_DP, 1);
        }
        segment_count++;
    }
    return segment_count;
}
