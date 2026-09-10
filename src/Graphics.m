#import "Graphics.h"
#include "app.h"

#define COLOR_BG   0.06, 0.016, 0.06, 1.0
#define COLOR_TEXT 1.0, 1.0, 1.0, 1.0

#define CELL_H 50
#define CELL_W 40

#define SIZE_STROKE 1

extern App g_app;

// NSRect bounds = [self bounds];
// To get the window bounds:
// bounds.size.width, bounds.size.height

@implementation Graphics
- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    NSRect bounds = [self bounds];

    CGContextRef ctx = [[NSGraphicsContext currentContext] CGContext];

    // TODO: write a function to convert HEX to these kinds of RGBA values
    CGContextSetRGBFillColor(ctx, COLOR_BG);
    CGContextFillRect(ctx, dirtyRect);

    CGContextSetRGBStrokeColor(ctx, COLOR_TEXT);
    CGContextSetLineWidth(ctx, SIZE_STROKE);

    for (int i = 0; i < g_app.project.pattern_len; i++) {
        int    curr_y = bounds.size.height - (i * (CELL_H - SIZE_STROKE));
        CGRect cell   = CGRectMake(SIZE_STROKE, curr_y, CELL_W, CELL_H);
        CGContextStrokeRect(ctx, cell);
    }

    CGContextStrokePath(ctx);
}

@end
