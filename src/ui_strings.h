#ifndef UI_STRINGS_H
#define UI_STRINGS_H

#include "font.h"

// I'm thinking that defining all of the needed strings here might make sense
// then, whoever needs them can just get a pointer to one of these structs
static const PSK_String UI_STR_ALPHABET_UPPER = {
    .font_size  = 4,
    .char_count = 26,
    .content    = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}
};

static const PSK_String UI_STR_ALPHABET_LOWER = {
    .font_size  = 4,
    .char_count = 26,
    .content    = {"abcdefghijklmnopqrstuvwxyz"}
};

#endif
