import { describe, expect, test } from "vite-plus/test";
import { cell_is_editable } from "./cell_is_editable";

describe("cell_is_editable", () => {
  test("Same resolution", () => {
    expect(cell_is_editable(16, 16)).toBe(true);
  });
  test("Same resolution", () => {
    expect(cell_is_editable(6, 6)).toBe(true);
  });
  test("Low-to-high: both EVEN", () => {
    expect(cell_is_editable(4, 128)).toBe(true);
  });
  test("Low-to-high: both ODD", () => {
    expect(cell_is_editable(6, 96)).toBe(true);
  });
});
