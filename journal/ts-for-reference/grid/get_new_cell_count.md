Not sure if I'll need this or not yet. Keeping for reference.
```ts
export function get_new_cell_count(
  current_zoom: ZoomLevel,
  new_zoom: ZoomLevel,
  pattern_length: number,
) {
  return Math.ceil(pattern_length / (current_zoom / new_zoom));
}
```