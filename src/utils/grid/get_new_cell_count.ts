import type { ZoomLevel } from "../../state/model";

export function get_new_cell_count(
  current_zoom: ZoomLevel,
  new_zoom: ZoomLevel,
  pattern_length: number,
) {
  return Math.ceil(pattern_length / (current_zoom / new_zoom));
}
