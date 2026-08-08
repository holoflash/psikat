import { describe, expect, test } from "vite-plus/test";
import { transform_pattern } from "./transform_pattern";
import { simple_4, simple_8 } from "../mocks";

describe("transform pattern", () => {
  test("Same resolution", () => {
    expect(transform_pattern(simple_8, 4)).toEqual(simple_4);
  });
});
