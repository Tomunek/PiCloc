#ifndef HARDWARE_H
#define HARDWARE_H

// BUTTON GPIO
#define GPIO_BTN_R 20
#define GPIO_BTN_L 21

// Assume common cathode 7-segment LED displays (Kingbright SC52-11GWA)
// DISPLAY SEGMENT GPIO
#define SEGMENT_A 3
#define SEGMENT_B 2
#define SEGMENT_C 26
#define SEGMENT_D 19
#define SEGMENT_E 18
#define SEGMENT_F 4
#define SEGMENT_G 5
#define SEGMENT_DP 27

// DISPLAY COMMON GPIO
#define COMMON_1 17
#define COMMON_2 16
#define COMMON_3 15
#define COMMON_4 14

// Rotated third display (to get ":" between hours and minutes)
// ROTATED SEGMENT GPIO
#define SEGMENT_R_A SEGMENT_D
#define SEGMENT_R_B SEGMENT_E
#define SEGMENT_R_C SEGMENT_F
#define SEGMENT_R_D SEGMENT_A
#define SEGMENT_R_E SEGMENT_B
#define SEGMENT_R_F SEGMENT_C
#define SEGMENT_R_G SEGMENT_DP
#define SEGMENT_R_DP SEGMENT_G

#endif