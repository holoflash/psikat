import { ZOOM_LCD } from "../../state";
import type { Pattern, ZoomLevel } from "../../state/model";

// TODO: make this scale down smart and resolve to intermediate zoom values if possible
export function scale_down_pattern(pattern: Pattern, new_zoom: ZoomLevel): Pattern {
  let new_pattern: Pattern = [];

  for (let p = 0; p < pattern.length; p++) {
    const cell = pattern[p];
    const normalized_new_zoom = ZOOM_LCD / new_zoom;
    const normalized_cell_zoom = ZOOM_LCD / cell.zoom;

    // Amount of cells of current zoom that fit in new zoom
    const scale_up = normalized_new_zoom / normalized_cell_zoom;

    const lookahead = pattern.slice(p + 1, p + scale_up);
    const can_merge = lookahead.length === scale_up - 1 && !lookahead.some((c) => c.value !== 0);
    if (!can_merge) {
      new_pattern.push(cell);
    }
    if (can_merge) {
      new_pattern.push({ value: cell.value, zoom: new_zoom });
      p += scale_up - 1;
    }
  }

  return new_pattern;
}
