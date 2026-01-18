#include "settings.h"
#include "hardware/rtc.h"
#include "pico/multicore.h"
#include "pico/util/datetime.h"
#include "pico/stdlib.h"
#ifdef SERIAL_DEBUG
#include <stdio.h>
#endif

#include "display.h"
#include "hardware.h"


#define MAIN_TICK_MAX 1000
#define HOW_OFTEN_REGISTER_BTN 250

void init_buttons(void) {
    gpio_init(GPIO_BTN_R);
    gpio_init(GPIO_BTN_L);

    gpio_set_dir(GPIO_BTN_R, 0);
    gpio_set_dir(GPIO_BTN_L, 0);

    gpio_pull_up(GPIO_BTN_R);
    gpio_pull_up(GPIO_BTN_L);
}

bool is_pressed(uint8_t btn) {
    return !gpio_get(btn);
}

bool has_time_passed(uint32_t tick_now, uint32_t tick_last, uint32_t how_much) {
    if (tick_last < 0) {
        return true;
    }
    if (tick_now <= tick_last) {
        tick_now += MAIN_TICK_MAX;
    }
    if (tick_now - tick_last > how_much) {
        return true;
    }
    return false;
}

#ifdef SERIAL_DEBUG
void dt_to_str(char *buf, uint buf_size, const datetime_t *t) {
    snprintf(buf,
             buf_size,
             "%02d:%02d:%02d",
             t->hour,
             t->min,
             t->sec);
};
#endif

void adjust_rtc(uint32_t btn_hold_count, bool up) {
    datetime_t t;
    rtc_get_datetime(&t);
    if (up) {
        if (btn_hold_count > 10) {
            t.min += 20;
        } else if (btn_hold_count > 5) {
            t.min += 5;
        } else {
            t.min++;
        }
        if (t.min >= 60) {
            t.min = t.min % 60;
            t.hour++;
        }
        if (t.hour >= 24) {
            t.hour = 0;
        }
    } else {
        if (btn_hold_count > 10) {
            t.min -= 20;
        } else if (btn_hold_count > 5) {
            t.min -= 5;
        } else {
            t.min--;
        }
        if (t.min < 0) {
            t.min = 59 + t.min;
            t.hour--;
        }
        if (t.hour < 0) {
            t.hour = 23;
        }
    }
    rtc_set_datetime(&t);
}

int main() {
    init_buttons();
#ifdef SERIAL_DEBUG
    stdio_init_all();
#endif

    datetime_t t = {
        .year = 2000,
        .month = 1,
        .day = 1,
        .hour = 0,
        .min = 0,
        .sec = 0};
    rtc_init();
    rtc_set_datetime(&t);
    sleep_us(64);

    multicore_launch_core1(display_main);

    uint32_t tick = 0;
    int32_t tick_last_btn_pressed = -1;
    uint32_t btn_hold_count = 0;
#ifdef SERIAL_DEBUG
    char datetime_buf[256];
    char *datetime_str = &datetime_buf[0];
#endif
    while (true) {
        if (tick % 200 == 0) {
            rtc_get_datetime(&t);
#ifdef SERIAL_DEBUG
            dt_to_str(datetime_str, sizeof(datetime_buf), &t);
            printf("%s %d\n", datetime_str, btn_hold_count);
#endif
            display_set_state(t.hour / 10, t.hour % 10, t.min / 10, t.min % 10);
        }

        if (has_time_passed(tick, tick_last_btn_pressed, HOW_OFTEN_REGISTER_BTN)) {
            if (is_pressed(GPIO_BTN_R)) {
                adjust_rtc(btn_hold_count, true);
                btn_hold_count++;
                tick_last_btn_pressed = tick;
            } else if (is_pressed(GPIO_BTN_L)) {
                adjust_rtc(btn_hold_count, false);
                btn_hold_count++;
                tick_last_btn_pressed = tick;
            } else {
                btn_hold_count = 0;
                tick_last_btn_pressed = -1;
            }
        }

        sleep_ms(1);
        tick++;
        if (tick >= MAIN_TICK_MAX) {
            tick = 0;
        }
    }
}
