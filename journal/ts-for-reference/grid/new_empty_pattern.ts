import type { Pattern, ZoomLevel } from "../../state/model";

// According to jsbench this is 73% faster than:
//   return Array.from({ length: zoom }, () => {
//     return { value: 0, zoom };
//   });
export function new_empty_pattern(length: number, zoom: ZoomLevel): Pattern {
  const p: Pattern = [];
  for (let i = 0; i < length; i++) {
    p.push({ value: 0, zoom });
  }
  return p;
}
