import { ZOOM_LCD } from "../../state";
import type { Pattern } from "../../state/model";

export function is_pattern_correct(pattern: Pattern): boolean | number {
  let total_count = 0;

  for (let c = 0; c < pattern.length; c++) {
    total_count += ZOOM_LCD / pattern[c].zoom;
  }

  return total_count === ZOOM_LCD;
}
