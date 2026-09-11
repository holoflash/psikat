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

    for (int i = 0; i < g_app.project.pattern_len; i++) {
        int curr_y = bounds.size.height - SIZE_CELL_H - (i * (SIZE_CELL_H)) - SIZE_STROKE;
        CGContextStrokeRect(ctx, CGRectMake(SIZE_STROKE, curr_y, SIZE_CELL_W, SIZE_CELL_H));
    }

    CGContextStrokePath(ctx);

    // TODO: This should live elsewhere
    static struct PSK_String psikat = {.font_size   = 4,
                                       .line_height = 6,
                                       .line_width  = 8,
                                       .char_count  = 7,
                                       .content     = {
                                           // Shouldn't have to do this manually once all characters are defined
                                           {
                                               OOO_____,
                                               O__OO___,
                                               O___OOO_,
                                               OOOOO___,
                                               OO______,
                                               OO______,
                                           },
                                           {
                                               ________,
                                               _OOOOOO_,
                                               OO____O_,
                                               __OOO___,
                                               O____OO_,
                                               OOOOOO__,
                                           },
                                           {
                                               ________,
                                               OOOOOO__,
                                               __O_____,
                                               __OO____,
                                               ___O____,
                                               OOOOOO__,
                                           },
                                           {
                                               _____O__,
                                               OO___O__,
                                               _O__OO__,
                                               _OOOO___,
                                               _O__OO__,
                                               OO____O_,
                                           },
                                           {
                                               ________,
                                               _OOOOO__,
                                               OO___OO_,
                                               OOOOOOO_,
                                               O_____O_,
                                               OO___OO_,
                                           },
                                           {
                                               O_____O_,
                                               OOOOOOO_,
                                               ___OO___,
                                               ___O____,
                                               ___O____,
                                               __OOO___,
                                           },
                                           {
                                               __O_____,
                                               __O_____,
                                               __O_____,
                                               __O_____,
                                               ________,
                                               __O_____,
                                           },
                                       }};

    // LET'S GOO! Drawing text like it's the 80s :)
    int x = bounds.size.height / 2 + (psikat.font_size * psikat.line_width);
    int y = bounds.size.width / 2 + (psikat.font_size * psikat.line_width);

    int shift = psikat.line_width * psikat.font_size;

    // TODO: This should be a more flexible function in font.c
    // void render_string(PSK_String string, int position_x, int position_y );
    // Maybe a Coordinates struct too ^
    for (int c = 0; c < psikat.char_count; c++) {
        int char_x = x + (c * shift);

        for (int row = 0; row < psikat.line_height; row++) {
            int curr_byte = psikat.content[c][row];

            for (int col = psikat.line_width - 1; col >= 0; col--) {
                int pixel_x = char_x + ((psikat.line_width - col) * psikat.font_size);
                int pixel_y = y - (row * psikat.font_size);

                CGRect rectangle = CGRectMake(pixel_x, pixel_y, psikat.font_size, psikat.font_size);

                if (((curr_byte >> col) & 1) == 1) {
                    CGContextSetRGBFillColor(ctx, COLOR_TEXT);
                    CGContextFillRect(ctx, rectangle);
                } else {
                    CGContextSetRGBFillColor(ctx, COLOR_BG);
                    CGContextFillRect(ctx, rectangle);
                }
            }
        }
    }
}

@end
