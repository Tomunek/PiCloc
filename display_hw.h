#ifndef DISPLAY_HW_H
#define DISPLAY_HW_H

// Assume common cathode 7-segment LED displays (Kingbright SC52-11GWA)
// SEGMENT GPIO
#define SEGMENT_A 3
#define SEGMENT_B 2
#define SEGMENT_C 26
#define SEGMENT_D 19
#define SEGMENT_E 18
#define SEGMENT_F 4
#define SEGMENT_G 5
#define SEGMENT_DP 27

// COMMON GPIO
#define COMMON_1 17
#define COMMON_2 16
#define COMMON_3 15
#define COMMON_4 14

const uint8_t COMMONS[4] = {
    COMMON_1,
    COMMON_2,
    COMMON_3,
    COMMON_4,
};

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
#endif