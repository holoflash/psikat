// This can be used for determining the new cursor position when changing resolutions

import type { ZoomLevel } from "../../state/model";

/**
 * Resolves the new position of a cell when changing zoom levels.
 */
export function get_pos_in_new_res(
  curr_zoom: ZoomLevel,
  new_zoom: ZoomLevel,
  curr_pos: number,
): number {
  if (curr_zoom === new_zoom) {
    return curr_pos;
  } else {
    const zoom_ratio = new_zoom / curr_zoom;
    return Math.trunc(curr_pos * zoom_ratio);
  }
}
