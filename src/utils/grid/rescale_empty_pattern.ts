import type { Pattern, ZoomLevel } from "../../state/model";
import { new_empty_pattern } from "./new_empty_pattern";

// TODO: This should not call new_empty_pattern
// Just return the new count number after the calculation
export function rescale_empty_pattern(
  pattern: Pattern,
  current_zoom: ZoomLevel,
  new_zoom: ZoomLevel,
): Pattern {
  const factor = current_zoom / new_zoom;
  const count = Math.ceil(pattern.length / factor);
  return new_empty_pattern(count, new_zoom);
}
