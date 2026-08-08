import { describe, expect, test } from "vite-plus/test";
import { transform_pattern } from "./transform_pattern";
import type { Pattern } from "../../state/model";

describe("transform pattern", () => {
  test("Even: high to low", () => {
    const before: Pattern = [
      { value: 1, zoom: 8 },
      { value: 1, zoom: 8 },
      { value: 1, zoom: 8 },
      { value: 0, zoom: 8 },
      { value: 1, zoom: 8 },
      { value: 0, zoom: 8 },
      { value: 1, zoom: 8 },
      { value: 0, zoom: 8 },
    ];

    const after: Pattern = [
      { value: 1, zoom: 8 },
      { value: 1, zoom: 8 },
      { value: 1, zoom: 4 },
      { value: 1, zoom: 4 },
      { value: 1, zoom: 4 },
    ];
    expect(transform_pattern(before, 4)).toEqual(after);
  });
});
