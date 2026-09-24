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
**Benchtesting**
```c
    struct timespec begin, end;
    timespec_get(&begin, TIME_UTC);

    int bench_test = expensive_function();

    timespec_get(&end, TIME_UTC);

    double time_spent =
        (end.tv_sec - begin.tv_sec) * 1000.0 + (end.tv_nsec - begin.tv_nsec) / 1000000.0;
```