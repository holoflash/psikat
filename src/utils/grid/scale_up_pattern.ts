import type { Pattern, ZoomLevel } from "../../state/model";

// TODO: Use ZOOM_LCD and tick values instead
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
