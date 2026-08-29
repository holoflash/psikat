import { describe, expect, test } from "vite-plus/test";
import type { Pattern } from "../../state/model";
import { is_pattern_correct } from "./is_pattern_correct";
import { scale_down_pattern } from "./rescale_pattern";

const simple_scale_down: Pattern = [
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

  { value: 1, zoom: 4 }, // 3/4

  { value: 1, zoom: 4 }, // 4/4
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

describe("scale_up_pattern", () => {
  test("Scales up when all cells can be resolved", () => {
    const scaled_up = scale_down_pattern(scaled_up_complex, 4);
    const is_correct = is_pattern_correct(scaled_up);

    expect(scaled_up).toEqual(simple_scale_down);
    expect(is_correct).toEqual(true);
  });
});
