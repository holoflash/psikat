import type { ZoomLevel } from "../../state/model";

export function next_zoom(current: ZoomLevel) {
  const z = 2 ** (Math.floor(Math.log2(current)) - 2);
  return current + z;
}

export function previous_zoom(current: ZoomLevel) {
  const z = 2 ** (Math.floor(Math.log2(current - 1)) - 2);
  return current - z;
}
