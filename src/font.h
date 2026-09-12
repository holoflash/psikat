#ifndef FONT_H
#define FONT_H

// Holds maximum 32 characters. Each character 6 rows tall
typedef struct PSK_String {
    int font_size;
    int line_height;
    int line_width;
    int char_count;
    int content[32][6];
} PSK_String;

typedef struct PSK_Rect {
    double position[2];
    double size[2];
    int    filled; // 1 || 0
    // TODO: Add RGB color too
} PSK_Rect;

PSK_Rect *PSK_string_to_rects(PSK_String *string, int x, int y, int size);

// Helper for drawing!
// The idea is:
// OOOOOOOO = 0b11111111 = 0xFF

// Once I've defined the full character set, I can get rid of this intermediate step
// and define each character as an array of ints directly.
#define ________ 0x00
#define _______O 0x01
#define ______O_ 0x02
#define ______OO 0x03
#define _____O__ 0x04
#define _____O_O 0x05
#define _____OO_ 0x06
#define _____OOO 0x07
#define ____O___ 0x08
#define ____O__O 0x09
#define ____O_O_ 0x0A
#define ____O_OO 0x0B
#define ____OO__ 0x0C
#define ____OO_O 0x0D
#define ____OOO_ 0x0E
#define ____OOOO 0x0F
#define ___O____ 0x10
#define ___O___O 0x11
#define ___O__O_ 0x12
#define ___O__OO 0x13
#define ___O_O__ 0x14
#define ___O_O_O 0x15
#define ___O_OO_ 0x16
#define ___O_OOO 0x17
#define ___OO___ 0x18
#define ___OO__O 0x19
#define ___OO_O_ 0x1A
#define ___OO_OO 0x1B
#define ___OOO__ 0x1C
#define ___OOO_O 0x1D
#define ___OOOO_ 0x1E
#define ___OOOOO 0x1F
#define __O_____ 0x20
#define __O____O 0x21
#define __O___O_ 0x22
#define __O___OO 0x23
#define __O__O__ 0x24
#define __O__O_O 0x25
#define __O__OO_ 0x26
#define __O__OOO 0x27
#define __O_O___ 0x28
#define __O_O__O 0x29
#define __O_O_O_ 0x2A
#define __O_O_OO 0x2B
#define __O_OO__ 0x2C
#define __O_OO_O 0x2D
#define __O_OOO_ 0x2E
#define __O_OOOO 0x2F
#define __OO____ 0x30
#define __OO___O 0x31
#define __OO__O_ 0x32
#define __OO__OO 0x33
#define __OO_O__ 0x34
#define __OO_O_O 0x35
#define __OO_OO_ 0x36
#define __OO_OOO 0x37
#define __OOO___ 0x38
#define __OOO__O 0x39
#define __OOO_O_ 0x3A
#define __OOO_OO 0x3B
#define __OOOO__ 0x3C
#define __OOOO_O 0x3D
#define __OOOOO_ 0x3E
#define __OOOOOO 0x3F
#define _O______ 0x40
#define _O_____O 0x41
#define _O____O_ 0x42
#define _O____OO 0x43
#define _O___O__ 0x44
#define _O___O_O 0x45
#define _O___OO_ 0x46
#define _O___OOO 0x47
#define _O__O___ 0x48
#define _O__O__O 0x49
#define _O__O_O_ 0x4A
#define _O__O_OO 0x4B
#define _O__OO__ 0x4C
#define _O__OO_O 0x4D
#define _O__OOO_ 0x4E
#define _O__OOOO 0x4F
#define _O_O____ 0x50
#define _O_O___O 0x51
#define _O_O__O_ 0x52
#define _O_O__OO 0x53
#define _O_O_O__ 0x54
#define _O_O_O_O 0x55
#define _O_O_OO_ 0x56
#define _O_O_OOO 0x57
#define _O_OO___ 0x58
#define _O_OO__O 0x59
#define _O_OO_O_ 0x5A
#define _O_OO_OO 0x5B
#define _O_OOO__ 0x5C
#define _O_OOO_O 0x5D
#define _O_OOOO_ 0x5E
#define _O_OOOOO 0x5F
#define _OO_____ 0x60
#define _OO____O 0x61
#define _OO___O_ 0x62
#define _OO___OO 0x63
#define _OO__O__ 0x64
#define _OO__O_O 0x65
#define _OO__OO_ 0x66
#define _OO__OOO 0x67
#define _OO_O___ 0x68
#define _OO_O__O 0x69
#define _OO_O_O_ 0x6A
#define _OO_O_OO 0x6B
#define _OO_OO__ 0x6C
#define _OO_OO_O 0x6D
#define _OO_OOO_ 0x6E
#define _OO_OOOO 0x6F
#define _OOO____ 0x70
#define _OOO___O 0x71
#define _OOO__O_ 0x72
#define _OOO__OO 0x73
#define _OOO_O__ 0x74
#define _OOO_O_O 0x75
#define _OOO_OO_ 0x76
#define _OOO_OOO 0x77
#define _OOOO___ 0x78
#define _OOOO__O 0x79
#define _OOOO_O_ 0x7A
#define _OOOO_OO 0x7B
#define _OOOOO__ 0x7C
#define _OOOOO_O 0x7D
#define _OOOOOO_ 0x7E
#define _OOOOOOO 0x7F
#define O_______ 0x80
#define O______O 0x81
#define O_____O_ 0x82
#define O_____OO 0x83
#define O____O__ 0x84
#define O____O_O 0x85
#define O____OO_ 0x86
#define O____OOO 0x87
#define O___O___ 0x88
#define O___O__O 0x89
#define O___O_O_ 0x8A
#define O___O_OO 0x8B
#define O___OO__ 0x8C
#define O___OO_O 0x8D
#define O___OOO_ 0x8E
#define O___OOOO 0x8F
#define O__O____ 0x90
#define O__O___O 0x91
#define O__O__O_ 0x92
#define O__O__OO 0x93
#define O__O_O__ 0x94
#define O__O_O_O 0x95
#define O__O_OO_ 0x96
#define O__O_OOO 0x97
#define O__OO___ 0x98
#define O__OO__O 0x99
#define O__OO_O_ 0x9A
#define O__OO_OO 0x9B
#define O__OOO__ 0x9C
#define O__OOO_O 0x9D
#define O__OOOO_ 0x9E
#define O__OOOOO 0x9F
#define O_O_____ 0xA0
#define O_O____O 0xA1
#define O_O___O_ 0xA2
#define O_O___OO 0xA3
#define O_O__O__ 0xA4
#define O_O__O_O 0xA5
#define O_O__OO_ 0xA6
#define O_O__OOO 0xA7
#define O_O_O___ 0xA8
#define O_O_O__O 0xA9
#define O_O_O_O_ 0xAA
#define O_O_O_OO 0xAB
#define O_O_OO__ 0xAC
#define O_O_OO_O 0xAD
#define O_O_OOO_ 0xAE
#define O_O_OOOO 0xAF
#define O_OO____ 0xB0
#define O_OO___O 0xB1
#define O_OO__O_ 0xB2
#define O_OO__OO 0xB3
#define O_OO_O__ 0xB4
#define O_OO_O_O 0xB5
#define O_OO_OO_ 0xB6
#define O_OO_OOO 0xB7
#define O_OOO___ 0xB8
#define O_OOO__O 0xB9
#define O_OOO_O_ 0xBA
#define O_OOO_OO 0xBB
#define O_OOOO__ 0xBC
#define O_OOOO_O 0xBD
#define O_OOOOO_ 0xBE
#define O_OOOOOO 0xBF
#define OO______ 0xC0
#define OO_____O 0xC1
#define OO____O_ 0xC2
#define OO____OO 0xC3
#define OO___O__ 0xC4
#define OO___O_O 0xC5
#define OO___OO_ 0xC6
#define OO___OOO 0xC7
#define OO__O___ 0xC8
#define OO__O__O 0xC9
#define OO__O_O_ 0xCA
#define OO__O_OO 0xCB
#define OO__OO__ 0xCC
#define OO__OO_O 0xCD
#define OO__OOO_ 0xCE
#define OO__OOOO 0xCF
#define OO_O____ 0xD0
#define OO_O___O 0xD1
#define OO_O__O_ 0xD2
#define OO_O__OO 0xD3
#define OO_O_O__ 0xD4
#define OO_O_O_O 0xD5
#define OO_O_OO_ 0xD6
#define OO_O_OOO 0xD7
#define OO_OO___ 0xD8
#define OO_OO__O 0xD9
#define OO_OO_O_ 0xDA
#define OO_OO_OO 0xDB
#define OO_OOO__ 0xDC
#define OO_OOO_O 0xDD
#define OO_OOOO_ 0xDE
#define OO_OOOOO 0xDF
#define OOO_____ 0xE0
#define OOO____O 0xE1
#define OOO___O_ 0xE2
#define OOO___OO 0xE3
#define OOO__O__ 0xE4
#define OOO__O_O 0xE5
#define OOO__OO_ 0xE6
#define OOO__OOO 0xE7
#define OOO_O___ 0xE8
#define OOO_O__O 0xE9
#define OOO_O_O_ 0xEA
#define OOO_O_OO 0xEB
#define OOO_OO__ 0xEC
#define OOO_OO_O 0xED
#define OOO_OOO_ 0xEE
#define OOO_OOOO 0xEF
#define OOOO____ 0xF0
#define OOOO___O 0xF1
#define OOOO__O_ 0xF2
#define OOOO__OO 0xF3
#define OOOO_O__ 0xF4
#define OOOO_O_O 0xF5
#define OOOO_OO_ 0xF6
#define OOOO_OOO 0xF7
#define OOOOO___ 0xF8
#define OOOOO__O 0xF9
#define OOOOO_O_ 0xFA
#define OOOOO_OO 0xFB
#define OOOOOO__ 0xFC
#define OOOOOO_O 0xFD
#define OOOOOOO_ 0xFE
#define OOOOOOOO 0xFF

#endif
