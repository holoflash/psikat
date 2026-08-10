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

    // TODO: an idea to list possible zoom levels for smarter scale down
    // const available_zooms = [];
    // let next_zoom = 0;

    // if (new_zoom <= cell.zoom && new_zoom % 2 === 0 && cell.zoom % 2 === 0) {
    //   next_zoom = cell.zoom / 2;
    // }
    // while (next_zoom <= cell.zoom && next_zoom > new_zoom && next_zoom > 6) {
    //   next_zoom = next_zoom / 2;
    //   available_zooms.push(next_zoom);
    // }

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

// TODO: Use ZOOM_LCD and tick values instead
// TODO: Merge with scale_down into one unified rescale_pattern function?
export function scale_up_pattern(pattern: Pattern, new_zoom: ZoomLevel): Pattern {
  let new_pattern: Pattern = [];

  for (let p = 0; p < pattern.length; p++) {
    const cell = pattern[p];
    const scale_up = new_zoom / cell.zoom;

    if (!(scale_up % 2 === 0 || scale_up % 3 === 0)) {
      new_pattern.push(cell);
      continue;
    }

    new_pattern.push({ value: cell.value, zoom: new_zoom });
    for (let s = 1; s < scale_up; s++) {
      new_pattern.push({ value: 0, zoom: new_zoom });
    }
  }

  return new_pattern;
}
