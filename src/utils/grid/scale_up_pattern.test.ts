import { describe, expect, test } from "vite-plus/test";
import type { Pattern } from "../../state/model";
import { scale_up_pattern } from "./scale_up_pattern";
import { is_pattern_correct } from "./is_pattern_correct";

// It is pretty evident that I should add a "count" field to the Pattern type to avoid storing a bunch of empty data
// But it can be done later on.
// Writing this test data is very tedious.
// Wrote is_pattern_correct.ts helper just to check that I'm not making mistakes

const complex_pattern: Pattern = [
  // 1/4
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 0, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 0, zoom: 32 },

  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },

  { value: 1, zoom: 4 }, // 3/4

  { value: 1, zoom: 4 }, // 4/4
];

const complex_pattern_intermediate: Pattern = [
  // 1/4
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 0, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 0, zoom: 32 },

  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },

  { value: 1, zoom: 24 }, // 3/4
  { value: 0, zoom: 24 },
  { value: 0, zoom: 24 },
  { value: 0, zoom: 24 },
  { value: 0, zoom: 24 },
  { value: 0, zoom: 24 },

  { value: 1, zoom: 24 }, // 4/4
  { value: 0, zoom: 24 },
  { value: 0, zoom: 24 },
  { value: 0, zoom: 24 },
  { value: 0, zoom: 24 },
  { value: 0, zoom: 24 },
];

const scaled_up_complex: Pattern = [
  // 1/4
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  // 2/4
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  // 3/4
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  // 4/4
  { value: 1, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },

  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
  { value: 0, zoom: 96 },
];

const complex_pattern_unresolved: Pattern = [
  // 1/4
  { value: 1, zoom: 32 }, // 1/4
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },

  { value: 0, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 1, zoom: 32 },
  { value: 0, zoom: 32 },

  { value: 1, zoom: 24 }, // 2/4
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },

  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },
  { value: 1, zoom: 24 },

  { value: 1, zoom: 32 }, // 3/4
  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },

  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },

  { value: 1, zoom: 32 }, // 4/4
  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },

  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },
  { value: 0, zoom: 32 },
];

describe("scale_up_pattern", () => {
  test("Scales up when all cells can be resolved", () => {
    const scaled_up = scale_up_pattern(complex_pattern, 96);
    const is_correct = is_pattern_correct(scaled_up);

    expect(scaled_up).toEqual(scaled_up_complex);
    expect(is_correct).toEqual(true);
  });

  test("Scales up when all cells can't be resolved", () => {
    const scaled_up = scale_up_pattern(complex_pattern, 32);
    const is_correct = is_pattern_correct(scaled_up);

    expect(scaled_up).toEqual(complex_pattern_unresolved);
    expect(is_correct).toEqual(true);
  });

  test("Scales up to an intermediate value when all cells can't be resolved", () => {
    const scaled_up = scale_up_pattern(complex_pattern, 24);
    const is_correct = is_pattern_correct(scaled_up);

    expect(scaled_up).toEqual(complex_pattern_intermediate);
    expect(is_correct).toEqual(true);
  });
});
