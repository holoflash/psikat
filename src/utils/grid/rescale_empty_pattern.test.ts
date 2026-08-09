import { describe, expect, test } from "vite-plus/test";
import { new_empty_pattern } from "./new_empty_pattern";
import { rescale_empty_pattern } from "./rescale_empty_pattern";

describe("Rescale pattern", () => {
  test("16 -> 4", () => {
    const old_l = 16;
    const old_z = 16;
    const new_l = 4;
    const new_z = 4;
    expect(rescale_empty_pattern(new_empty_pattern(old_l, old_z), old_z, new_z)).toEqual(
      new_empty_pattern(new_l, new_z),
    );
  });
  test("128 -> 48", () => {
    const old_l = 128;
    const old_z = 128;
    const new_l = 48;
    const new_z = 48;
    expect(rescale_empty_pattern(new_empty_pattern(old_l, old_z), old_z, new_z)).toEqual(
      new_empty_pattern(new_l, new_z),
    );
  });
});
