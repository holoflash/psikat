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

    static struct PSK_String string = {.font_size = 4, .char_count = 28, .content = {"`ABCDEFGHIJKLMNOPQRSTUVWXYZ`"}};

    int string_width  = (PSK_GLYPH_W * string.font_size) * string.char_count;
    int string_height = (PSK_GLYPH_H * string.font_size);

    // If we gonna have newlines, calculating the center like this doesn't work!
    Vec2 start_position =
        get_coords_to_center((Vec2){bounds.size.width, bounds.size.height}, (Vec2){string_width, string_height});

    int size = string.char_count * PSK_GLYPH_H * PSK_GLYPH_W;

    PSK_Rect *string_rects = PSK_string_to_rects(&string, (Vec2){start_position.x, start_position.y}, size);

    for (int i = 0; i < size; i++) {
        CGContextSetRGBFillColor(ctx, 1.0, 1.0, 1.0, 1.0);
        CGContextFillRect(ctx,
                          CGRectMake(string_rects[i].position.x,
                                     string_rects[i].position.y,
                                     string_rects[i].dimensions.x,
                                     string_rects[i].dimensions.y));
    }

    free(string_rects);
    string_rects = NULL;
}

@end
