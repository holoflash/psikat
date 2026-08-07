import { expect, test } from "vite-plus/test";
import { get_cell_multiplier } from "./get_cell_multiplier";

test("should work", () => {
  expect(get_cell_multiplier(8, 48, 6)).toBe(36);
});
