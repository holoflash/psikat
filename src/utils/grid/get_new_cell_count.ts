export function get_new_cell_count(current_zoom: number, new_zoom: number, pattern_length: number) {
  return Math.ceil(pattern_length / (current_zoom / new_zoom));
}
