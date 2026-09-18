#import "RenderGrid.h"
#include "app.h"
#include "font.h"

#define COLOR_BG   0.06, 0.016, 0.06, 1.0
#define COLOR_TEXT 1.0, 1.0, 1.0, 1.0
#define COLOR_DIM  0.5, 0.5, 0.5, 1.0

#define SIZE_CELL_H 50
#define SIZE_CELL_W 50

#define SIZE_STROKE 1

extern App g_app;

@implementation RenderGrid
- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    NSRect bounds = [self bounds];

    CGContextRef ctx = [[NSGraphicsContext currentContext] CGContext];

    CGContextSetRGBFillColor(ctx, COLOR_BG);
    CGContextFillRect(ctx, dirtyRect);

    CGContextSetRGBStrokeColor(ctx, COLOR_TEXT);
    CGContextSetLineWidth(ctx, SIZE_STROKE);

    // Grid drawing
    // for (int i = 0; i < g_app.project.pattern_len; i++) {
    //     int curr_y = bounds.size.height - SIZE_CELL_H - (i * (SIZE_CELL_H)) - SIZE_STROKE;
    //     CGContextStrokeRect(ctx, CGRectMake(SIZE_STROKE, curr_y, SIZE_CELL_W, SIZE_CELL_H));
    // }

    CGContextStrokePath(ctx);

    static struct PSK_String string = {.font_size   = 4,
                                       .line_height = PSK_GLYPH_H,
                                       .line_width  = PSK_GLYPH_W,
                                       .char_count  = 26,
                                       .content     = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}};

    int string_width  = ((string.line_width * string.font_size) - string.font_size) * string.char_count;
    int string_height = (string.line_height * string.font_size);

    int x = (bounds.size.width / 2) - (string_width / 2);
    int y = (bounds.size.height / 2) + (string_height / 2);

    int size = string.char_count * string.line_height * string.line_width;

    PSK_Rect *string_rects = PSK_string_to_rects(&string, x, y, size);

    for (int i = 0; i < size; i++) {
        CGRect string_rect = CGRectMake(string_rects[i].position[0],
                                        string_rects[i].position[1],
                                        string_rects[i].size[0],
                                        string_rects[i].size[1]);

        if (string_rects[i].filled == 1) {
            CGContextSetRGBFillColor(ctx, 1.0, 1.0, 1.0, 1.0);
            CGContextFillRect(ctx, string_rect);
        } else {
            CGContextSetRGBFillColor(ctx, 0.0, 0.0, 0.0, 0.0);
            CGContextFillRect(ctx, string_rect);
        }
    }

    free(string_rects);
    string_rects = NULL;
}

@end
