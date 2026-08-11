import { describe, test, expect } from "vite-plus/test";
import { next_zoom, previous_zoom } from "./traverse_zoom_levels";

// | 4   | 5   | 6   | 7   |
// | 8   | 10  | 12  | 14  |
// | 16  | 20  | 24  | 28  |
// | 32  | 40  | 48  | 56  |
// | 64  | 80  | 96  | 112 |
// | 128 | 160 | 192 | 224 |
// | 256 | 320 | 384 | 448 |
// | 512 | 640 | 768 | 896 |

describe("next_zoom", () => {
  test("Moves to the next zoom level in the scale", () => {
    expect(next_zoom(4)).toEqual(5);
    expect(next_zoom(10)).toEqual(12);
    expect(next_zoom(192)).toEqual(224);
    expect(next_zoom(112)).toEqual(128);
  });
});

describe("prev_zoom", () => {
  test("Moves to the next zoom level in the scale", () => {
    expect(previous_zoom(320)).toEqual(256);
    // TODO: Previous zoom algorithm doesn't work when traversing across boundaries!
    expect(previous_zoom(128)).toEqual(112);
  });
});
