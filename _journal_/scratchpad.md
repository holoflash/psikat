```c
#define SIZE_CELL_H 50
#define SIZE_CELL_W 50
#define SIZE_STROKE 1
    
Grid drawing
for (int i = 0; i < g_app.project.pattern_len; i++) {
    int curr_y = bounds.size.height - SIZE_CELL_H - (i * (SIZE_CELL_H)) - SIZE_STROKE;
    CGContextStrokeRect(ctx, CGRectMake(SIZE_STROKE, curr_y, SIZE_CELL_W, SIZE_CELL_H));
}
```