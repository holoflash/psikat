Not sure if I'll need this or not yet. Keeping for reference.
```ts
function is_pattern_correct(pattern: Pattern): boolean | number {
  let total_count = 0;

  for (let c = 0; c < pattern.length; c++) {
    total_count += ZOOM_LCD / pattern[c].zoom;
  }

  return total_count === ZOOM_LCD;
}
```