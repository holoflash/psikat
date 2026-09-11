#ifndef CONSTANTS_H
#define CONSTANTS_H

/* MAGIC NUMBERS */
#define TWO_PI 6.283185307

#define UNUSED __attribute__((unused))

/* NSEvent keyCode MAPPING */
// ROW 1 - 11 values
#define KEY_BRACK  50
#define KEY_Z      6
#define KEY_X      7
#define KEY_C      8
#define KEY_V      9
#define KEY_B      11
#define KEY_N      45
#define KEY_M      46
#define KEY_COMMA  43
#define KEY_PERIOD 47
#define KEY_DASH   44

// ROW 2 - 11 values
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_F 3
#define KEY_G 5
#define KEY_H 4
#define KEY_J 38
#define KEY_K 40
#define KEY_L 37
#define KEY_Ö 41
#define KEY_Ä 39

// ROW 3 - 11 values
#define KEY_Q 12
#define KEY_W 13
#define KEY_E 14
#define KEY_R 15
#define KEY_T 17
#define KEY_Y 16
#define KEY_U 32
#define KEY_I 34
#define KEY_O 31
#define KEY_P 35
#define KEY_Å 33

// ROW 4 - 11 values
#define KEY_1 18
#define KEY_2 19
#define KEY_3 20
#define KEY_4 21
#define KEY_5 23
#define KEY_6 22
#define KEY_7 26
#define KEY_8 28
#define KEY_9 25
#define KEY_0 29

// ARROWS
#define KEY_ARR_L 123
#define KEY_ARR_U 126
#define KEY_ARR_R 124
#define KEY_ARR_D 125

// COMMANDS
#define KEY_TAB   48
#define KEY_ENTER 36
#define KEY_SPACE 49
#define KEY_DEL   51

// EXTRAS
#define KEY_ASTER  42 // right of ä key
#define KEY_UMLAUT 30 // right of å key
#define KEY_DEG    10 // left of 1 key
#define KEY_PLUS   27 // right of 0 key
#define KEY_APOS   24 // right of + key

// extern const double N_FREQUENCY[128];
extern const char N_NAME[128][3];

#endif
