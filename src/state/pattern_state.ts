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
    [1, 5, -1, -1, 999],
    [2, 6, -1, -1, 999],
    [3, 7, -1, -1, 999],
    [4, 8, -1, -1, 999],
  ],
};

export const PatternState: PatternState = TEST_PATTERN;
