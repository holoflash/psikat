type PatternCell = {
  value: number;
  subdivision: number;
  type: "NOTE" | "COMMAND" | "FX";
};

type Pattern = {
  name: string;
  voices: 1 | 2 | 3 | 4 | 5 | 6 | 8;
  steps: 8;
  fx: number;
  data: PatternCell[][];
};

type Track = {
  voices: number;
  isMaster?: boolean;
  patterns: Pattern[];
};

type ArrangementState = {
  tracks: Track[];
  bpm: number;
};

const DEFAULT_ARRANGEMENT_STATE: ArrangementState = {
  tracks: [
    {
      voices: 4,
      patterns: [
        {
          name: "pattern_1",
          voices: 4,
          steps: 8,
          fx: 1,
          data: [[{ value: 1, subdivision: 16, type: "NOTE" }]],
        },
      ],
    },
  ],
  bpm: 120,
};

void DEFAULT_ARRANGEMENT_STATE;
