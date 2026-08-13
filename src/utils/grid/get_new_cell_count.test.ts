import { describe, expect, test } from "vite-plus/test";
import { get_new_cell_count } from "./get_new_cell_count";

describe("get_new_cell_count", () => {
  test("Length:16; Zoom:16 -> Zoom:4", () => {
    expect(get_new_cell_count(16, 4, 16)).toEqual(4);
  });
  test("Length:4; Zoom:16 -> Zoom:4", () => {
    expect(get_new_cell_count(16, 4, 4)).toEqual(1);
  });
  test("Length:4; Zoom:4 -> Zoom:6", () => {
    expect(get_new_cell_count(4, 6, 4)).toEqual(6);
  });
  test("Length:6; Zoom:24 -> Zoom:16", () => {
    expect(get_new_cell_count(24, 16, 6)).toEqual(4);
  });
  test("Length:4; Zoom:16 -> Zoom:20", () => {
    expect(get_new_cell_count(16, 20, 4)).toEqual(5);
  });
});
