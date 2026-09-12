#include "font.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

PSK_Rect *PSK_string_to_rects(PSK_String *string, int start_x, int start_y, int capacity) {
    PSK_Rect *rects = calloc(capacity, sizeof(PSK_Rect));
    if (!rects) {
        return NULL;
    }

    int current_rect = 0;
    int char_stride  = string->line_width * string->font_size;

    for (int char_i = 0; char_i < string->char_count; char_i++) {
        int char_x = start_x + (char_i * char_stride);

        for (int row_i = 0; row_i < string->line_height; row_i++) {
            int bitmap_row = string->content[char_i][row_i];

            for (int col_i = string->line_width - 1; col_i >= 0; col_i--) {
                int pixel_x = char_x + ((string->line_width - col_i) * string->font_size);
                int pixel_y = start_y - (row_i * string->font_size);

                PSK_Rect rect = {.position = {pixel_x, pixel_y}, .size = {string->font_size, string->font_size}};

                if (((bitmap_row >> col_i) & 1) == 1) {
                    rect.filled = 1;
                } else {
                    rect.filled = 0;
                }
                rects[current_rect] = rect;
                current_rect++;
            }
        }
    }
    return rects;
}
