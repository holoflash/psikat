export type PatternState = {
  name: string;
  voices: number;
  automation: number;
  data: number[][];
};

const TEST_PATTERN: PatternState = {
  name: "Pattern 1",
  voices: 4,
  automation: 1,
  data: [
    [1, 2, 3, 4, 5, 6, 7, 8, 9],
    [1, 2, 3, 4, 5, 6, 7, 8, 9],
    [1, 2, 3, 4, 5, 6, 7, 8, 9],
    [1, 2, 3, 4, 5, 6, 7, 8, 9],
    [999, 999, 999, 999, 999, 999, 999, 999, 999],
  ],
};

export const PatternState: PatternState = TEST_PATTERN;
