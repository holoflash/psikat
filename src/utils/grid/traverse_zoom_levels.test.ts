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
  test("Moves within row", () => {
    expect(next_zoom(4)).toEqual(5);
  });
  test("Moves within row", () => {
    expect(next_zoom(10)).toEqual(12);
  });
  test("Moves within row", () => {
    expect(next_zoom(192)).toEqual(224);
  });
  test("Moves across boundaries", () => {
    expect(next_zoom(112)).toEqual(128);
  });
  test("Moves across boundaries", () => {
    expect(next_zoom(448)).toEqual(512);
  });
});

describe("previous_zoom", () => {
  test("Moves within row", () => {
    expect(previous_zoom(320)).toEqual(256);
  });
  test("Moves within row", () => {
    expect(previous_zoom(20)).toEqual(16);
  });
  test("Moves within row", () => {
    expect(previous_zoom(56)).toEqual(48);
  });
  test("Moves across boundaries", () => {
    expect(previous_zoom(128)).toEqual(112);
  });
  test("Moves across boundaries", () => {
    expect(previous_zoom(512)).toEqual(448);
  });
});
