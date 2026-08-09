import { describe, expect, test } from "vite-plus/test";
import { new_empty_pattern } from "./new_empty_pattern";

describe("new_empty_pattern", () => {
  test("Creates empty pattern of desired length and zoom", () => {
    expect(new_empty_pattern(4, 16)).toEqual([
      { value: 0, zoom: 16 },
      { value: 0, zoom: 16 },
      { value: 0, zoom: 16 },
      { value: 0, zoom: 16 },
    ]);
  });
  test("Handles 0 length", () => {
    expect(new_empty_pattern(0, 128)).toHaveLength(0);
  });
});
