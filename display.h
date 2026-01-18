#ifndef DISPLAY_H
#define DISPLAY_H

#define DIGIT_ON_TIME_US 2000
// display_main should loop to this value to take exactly 1s
#define DISPLAY_MAIN_LOOP_TICK_MAX 250000 / DIGIT_ON_TIME_US

void display_main(void);

void display_set_state(uint8_t, uint8_t, uint8_t, uint8_t);

void display_set_dp(bool, bool, bool, bool);

// Displays current state. Sleeps for 4*DIGIT_ON_TIME_US
void _display_show(void);

void _display_setup_gpio(void);
void _display_all_segments_off(void);
void _display_show_number(uint8_t, uint8_t, bool);
void _display_set_common(uint8_t, bool);
uint8_t _display_set_segments(uint8_t, uint8_t, bool);
#endif