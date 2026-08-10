import type { Pattern } from "../../state/model";

// To avoid floating point math, I had to find a common denominator for all of the zoom values
// I think I should change how I store the zoom values internally
export function is_pattern_correct(pattern: Pattern): boolean | number {
  let total_count = 0;

  for (let c = 0; c < pattern.length; c++) {
    total_count += 384 / pattern[c].zoom;
  }
  // If the sum of all the cells is 384 we know we have a pattern that is 1/1 long
  return total_count === 384;
}
