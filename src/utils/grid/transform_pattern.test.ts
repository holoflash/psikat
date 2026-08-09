import { describe, expect, test } from "vite-plus/test";
import { transform_pattern } from "./transform_pattern";
import type { Pattern } from "../../state/model";

const zoom_8: Pattern = [
  { value: 1, zoom: 8 },
  { value: 1, zoom: 8 },
  { value: 1, zoom: 8 },
  { value: 0, zoom: 8 },
  { value: 1, zoom: 8 },
  { value: 0, zoom: 8 },
  { value: 1, zoom: 8 },
  { value: 0, zoom: 8 },
];

const zoom_4: Pattern = [
  { value: 1, zoom: 8 },
  { value: 1, zoom: 8 },
  { value: 1, zoom: 4 },
  { value: 1, zoom: 4 },
  { value: 1, zoom: 4 },
];

describe("transform pattern", () => {
  test("Even: high to low", () => {
    expect(transform_pattern(zoom_8, 4)).toEqual(zoom_4);
  });

  test("Empty: high to low", () => {
    expect(transform_pattern(zoom_8, 4)).toEqual(zoom_4);
  });
});
