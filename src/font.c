#include "font.h"
#include "helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include <CoreGraphics/CoreGraphics.h>

void draw_psk_string(CGContextRef ctx, const PSK_String *string, Vec2 destination) {
    Vec2 start_position =
        get_coords_to_center((Vec2){destination.x, destination.y},
                             (Vec2){(PSK_GLYPH_W * string->font_size) * string->char_count,
                                    (PSK_GLYPH_H * string->font_size)});

    int max_rect_count = string->char_count * PSK_GLYPH_H * PSK_GLYPH_W;

    CGRect rect_buffer[max_rect_count];

    int rect_count =
        PSK_string_to_rects(string, (Vec2){start_position.x, start_position.y}, rect_buffer);

    CGContextSetRGBFillColor(ctx, 1.0, 1.0, 1.0, 1.0);
    CGContextFillRects(ctx, rect_buffer, rect_count);
}

int PSK_string_to_rects(const PSK_String *string, Vec2 start_pos, CGRect *rects) {
    int rect_count  = 0;
    int char_stride = PSK_GLYPH_W * string->font_size;

    for (int char_i = 0; char_i < string->char_count; char_i++) {
        int char_x = start_pos.x + (char_i * char_stride);

        char            ascii_char = string->content[char_i];
        const PSK_Glyph glyph      = PSK_glyph_from_char(ascii_char);

        for (int row_i = 0; row_i < PSK_GLYPH_H; row_i++) {
            int bitmap_row = glyph.rows[row_i];

            for (int col_i = PSK_GLYPH_W - 1; col_i >= 0; col_i--) {

                if (((bitmap_row >> col_i) & 1) == 1) {
                    int pixel_x = char_x + ((PSK_GLYPH_W - col_i) * string->font_size);
                    int pixel_y = start_pos.y - (row_i * string->font_size);

                    rects[rect_count++] =
                        CGRectMake(pixel_x, pixel_y, string->font_size, string->font_size);
                }
            }
        }
    }
    return rect_count;
}

// Patiently handwritten from a System font reference image
// skill: 0%; spectrum: yes
PSK_Glyph PSK_glyph_from_char(char ascii_value) {
    switch (ascii_value) {
    case 'A':
        return (PSK_Glyph){{________,
                            __OO____,
                            _OOOO___,
                            OO__OO__,
                            OO__OO__,
                            OOOOOO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            ________,
                            ________}};
    case 'B':
        return (PSK_Glyph){{________,
                            OOOOOO__,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            _OOOOO__,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            OOOOOO__,
                            ________,
                            ________}};
    case 'C':
        return (PSK_Glyph){{________,
                            __OOOO__,
                            _OO__OO_,
                            OO___OO_,
                            OO______,
                            OO______,
                            OO______,
                            OO___OO_,
                            _OO__OO_,
                            __OOOO__,
                            ________,
                            ________}};
    case 'D':
        return (PSK_Glyph){{________,
                            OOOOO___,
                            _OO_OO__,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            _OO_OO__,
                            OOOOO___,
                            ________,
                            ________}};
    case 'E':
        return (PSK_Glyph){{________,
                            OOOOOOO_,
                            _OO___O_,
                            _OO_____,
                            _OO__O__,
                            _OOOOO__,
                            _OO__O__,
                            _OO_____,
                            _OO___O_,
                            OOOOOOO_,
                            ________,
                            ________}};
    case 'F':
        return (PSK_Glyph){{________,
                            OOOOOOO_,
                            _OO___O_,
                            _OO_____,
                            _OO__O__,
                            _OOOOO__,
                            _OO__O__,
                            _OO_____,
                            _OO_____,
                            OOOO____,
                            ________,
                            ________}};
    case 'G':
        return (PSK_Glyph){{________,
                            __OOOO__,
                            _OO__OO_,
                            OO___OO_,
                            OO______,
                            OO______,
                            OO__OOO_,
                            OO___OO_,
                            _OO__OO_,
                            __OOOOO_,
                            ________,
                            ________}};
    case 'H':
        return (PSK_Glyph){{________,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OOOOOO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            ________,
                            ________}};
    case 'I':
        return (PSK_Glyph){{________,
                            _OOOO___,
                            __OO____,
                            __OO____,
                            __OO____,
                            __OO____,
                            __OO____,
                            __OO____,
                            __OO____,
                            _OOOO___,
                            ________,
                            ________}};
    case 'J':
        return (PSK_Glyph){{________,
                            ___OOOO_,
                            ____OO__,
                            ____OO__,
                            ____OO__,
                            ____OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            _OOOO___,
                            ________,
                            ________}};
    case 'K':
        return (PSK_Glyph){{________,
                            OOO__OO_,
                            _OO__OO_,
                            _OO_OO__,
                            _OO_OO__,
                            _OOO____,
                            _OO_OO__,
                            _OO_OO__,
                            _OO__OO_,
                            OOO__OO_,
                            ________,
                            ________}};
    case 'L':
        return (PSK_Glyph){{________,
                            OOOO____,
                            _OO_____,
                            _OO_____,
                            _OO_____,
                            _OO_____,
                            _OO___O_,
                            _OO__OO_,
                            _OO__OO_,
                            OOOOOOO_,
                            ________,
                            ________}};
    case 'M':
        return (PSK_Glyph){{________,
                            OO___OO_,
                            OOO_OOO_,
                            OOOOOOO_,
                            OOOOOOO_,
                            OO_O_OO_,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            ________,
                            ________}};
    case 'N':
        return (PSK_Glyph){{________,
                            OO___OO_,
                            OO___OO_,
                            OOO__OO_,
                            OOOO_OO_,
                            OOOOOOO_,
                            OO_OOOO_,
                            OO__OOO_,
                            OO___OO_,
                            OO___OO_,
                            ________,
                            ________}};
    case 'O':
        return (PSK_Glyph){{________,
                            __OOO___,
                            _OO_OO__,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            _OO_OO__,
                            __OOO___,
                            ________,
                            ________}};
    case 'P':
        return (PSK_Glyph){{________,
                            OOOOOO__,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            _OOOOO__,
                            _OO_____,
                            _OO_____,
                            _OO_____,
                            OOOO____,
                            ________,
                            ________}};
    case 'Q':
        return (PSK_Glyph){{________,
                            __OOO___,
                            _OO_OO__,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            _OOOOO__,
                            ____OO__,
                            _____OO_,
                            ________}};
    case 'R':
        return (PSK_Glyph){{________,
                            OOOOOO__,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            _OOOOO__,
                            _OO_OO__,
                            _OO__OO_,
                            _OO__OO_,
                            OOO__OO_,
                            ________,
                            ________}};
    case 'S':
        return (PSK_Glyph){{________,
                            _OOOO___,
                            OO__OO__,
                            OO__OO__,
                            OO______,
                            _OOO____,
                            ___OO___,
                            OO__OO__,
                            OO__OO__,
                            _OOOO___,
                            ________,
                            ________}};
    case 'T':
        return (PSK_Glyph){{________,
                            OOOOOO__,
                            O_OO_O__,
                            __OO____,
                            __OO____,
                            __OO____,
                            __OO____,
                            __OO____,
                            __OO____,
                            _OOOO___,
                            ________,
                            ________}};
    case 'U':
        return (PSK_Glyph){{________,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            _OOOO___,
                            ________,
                            ________}};
    case 'V':
        return (PSK_Glyph){{________,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            _OOOO___,
                            __OO____,
                            ________,
                            ________}};
    case 'W':
        return (PSK_Glyph){{________,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            OO___OO_,
                            OO_O_OO_,
                            OO_O_OO_,
                            _OO_OO__,
                            _OO_OO__,
                            _OO_OO__,
                            ________,
                            ________}};
    case 'X':
        return (PSK_Glyph){{________,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            _OOOO___,
                            __OO____,
                            _OOOO___,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            ________,
                            ________}};
    case 'Y':
        return (PSK_Glyph){{________,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            _OOOO___,
                            __OO____,
                            __OO____,
                            __OO____,
                            _OOOO___,
                            ________,
                            ________}};
    case 'Z':
        return (PSK_Glyph){{________,
                            OOOOOOO_,
                            OO__OOO_,
                            O__OO___,
                            ___OO___,
                            __OO____,
                            _OO_____,
                            _OO___O_,
                            OO___OO_,
                            OOOOOOO_,
                            ________,
                            ________}};
    case 'a':
        return (PSK_Glyph){{________,
                            ________,
                            ________,
                            ________,
                            _OOOO___,
                            ____OO__,
                            _OOOOO__,
                            OO__OO__,
                            OO__OO__,
                            _OOO_OO_,
                            ________,
                            ________}};
    case 'b':
        return (PSK_Glyph){{________,
                            OOO_____,
                            _OO_____,
                            _OO_____,
                            _OOOOO__,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            _OO__OO_,
                            OO_OOO__,
                            ________,
                            ________}};
    case 'c':
        return (PSK_Glyph){{________,
                            ________,
                            ________,
                            ________,
                            _OOOOO__,
                            OO___OO_,
                            OO______,
                            OO______,
                            OO___OO_,
                            _OOOOO__,
                            ________,
                            ________}};
    case 'd':
        return (PSK_Glyph){{________,
                            ___OOO__,
                            ____OO__,
                            ____OO__,
                            _OOOOO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            OO__OO__,
                            _OOO_OO_,
                            ________,
                            ________}};
    case 'e':
        return (PSK_Glyph){{________,
                            ________,
                            ________,
                            ________,
                            _OOOOO__,
                            OO___OO_,
                            OOOOOOO_,
                            OO______,
                            OO___OO_,
                            _OOOOO__,
                            ________,
                            ________}};
    case 'f':
        return (PSK_Glyph){{________,
                            __OOO___,
                            _OO_OO__,
                            _OO_____,
                            _OO_____,
                            OOOOO___,
                            _OO_____,
                            _OO_____,
                            _OO_____,
                            OOOOO___,
                            ________,
                            ________}};
    case 'g':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            _OOO_OO_,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            _OOOOO__,
            ____OO__,
            OO__OO__,
            _OOOO___,
        }};
    case 'h':
        return (PSK_Glyph){{
            ________,
            OOO_____,
            _OO_____,
            _OO_____,
            _OO_OO__,
            _OOO_OO_,
            _OO__OO_,
            _OO__OO_,
            _OO__OO_,
            OOO__OO_,
            ________,
            ________,
        }};
    case 'i':
        return (PSK_Glyph){{
            ________,
            __OO____,
            __OO____,
            ________,
            OOOO____,
            __OO____,
            __OO____,
            __OO____,
            __OO____,
            OOOOOO__,
            ________,
            ________,
        }};
    case 'j':
        return (PSK_Glyph){{
            ________,
            ____OO__,
            ____OO__,
            ________,
            _OOOOO__,
            ____OO__,
            ____OO__,
            ____OO__,
            ____OO__,
            OO__OO__,
            OO__OO__,
            _OOOO___,
        }};
    case 'k':
        return (PSK_Glyph){{
            ________,
            OOO_____,
            _OO_____,
            _OO_____,
            _OO__OO_,
            _OO_OO__,
            _OOOO___,
            _OO_OO__,
            _OO__OO_,
            OOO__OO_,
            ________,
            ________,
        }};
    case 'l':
        return (PSK_Glyph){{
            ________,
            OOOO____,
            __OO____,
            __OO____,
            __OO____,
            __OO____,
            __OO____,
            __OO____,
            __OO____,
            OOOOOO__,
            ________,
            ________,
        }};
    case 'm':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OOOOOO__,
            OO_O_OO_,
            OO_O_OO_,
            OO_O_OO_,
            OO_O_OO_,
            OO___OO_,
            ________,
            ________,
        }};
    case 'n':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OOOOO___,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            ________,
            ________,
        }};
    case 'o':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            _OOOO___,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            _OOOO___,
            ________,
            ________,
        }};
    case 'p':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OO_OOO__,
            _OO__OO_,
            _OO__OO_,
            _OO__OO_,
            _OO__OO_,
            _OOOOO__,
            _OO_____,
            OOOO____,
        }};
    case 'q':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            _OOO_OO_,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            _OOOOO__,
            ____OO__,
            ___OOOO_,
        }};
    case 'r':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OOO_OO__,
            _OO_OOO_,
            _OOO_OO_,
            _OO_____,
            _OO_____,
            OOOOO___,
            ________,
            ________,
        }};
    case 's':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            _OOOO___,
            OO__OO__,
            _OO_____,
            ___OO___,
            OO__OO__,
            _OOOO___,
            ________,
            ________,
        }};
    case 't':
        return (PSK_Glyph){{
            ________,
            ________,
            __O_____,
            _OO_____,
            OOOOOO__,
            _OO_____,
            _OO_____,
            _OO_____,
            _OO_OOO_,
            __OOOO__,
            ________,
            ________,
        }};
    case 'u':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            _OOO_OO_,
            ________,
            ________,
        }};
    case 'v':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            OO__OO__,
            _OOOO___,
            __OO____,
            ________,
            ________,
        }};
    case 'w':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OO___OO_,
            OO___OO_,
            OO_O_OO_,
            OO_O_OO_,
            _OO_OO__,
            _OO_OO__,
            ________,
            ________,
        }};
    case 'x':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OO___OO_,
            _OO_OO__,
            __OOO___,
            __OOO___,
            _OO_OO__,
            OO___OO_,
            ________,
            ________,
        }};
    case 'y':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            _OO__OO_,
            _OO__OO_,
            _OO__OO_,
            _OO__OO_,
            __OOOO__,
            ____OO__,
            ___OO___,
            OOOO____,
        }};
    case 'z':
        return (PSK_Glyph){{
            ________,
            ________,
            ________,
            ________,
            OOOOOO__,
            O___OO__,
            ___OO___,
            _OO_____,
            OO___O__,
            OOOOOO__,
            ________,
            ________,
        }};
    default:
        return (PSK_Glyph){{
            ___OO___,
            ___OO___,
            ___O_O__,
            ___OO_O_,
            ___O_O__,
            ___O__O_,
            ___O__O_,
            ___O_O__,
            ___O____,
            _OOO____,
            OOOO____,
            OOO_____,
        }};
    }
}
