export type PatternCell = {
  value: number;
  zoom: number;
  selected: boolean;
  type: "NOTE" | "COMMAND" | "FX" | "EMPTY";
};

export type Pattern = {
  id: string;
  voices: number;
  fx: number;
  data: PatternCell[];
};

export type Track = {
  id: string;
  voices: number;
  isMaster?: boolean;
  patterns: Pattern[];
};

export type ArrangementState = {
  tracks: Track[];
  bpm: number;
};

export type PatternPool = Pattern[];

const INIT_PATTERN_POOL_STATE: PatternPool = [
  {
    id: "pattern_1",
    voices: 4,
    fx: 1,
    data: [
      { value: 1, zoom: 16, type: "EMPTY", selected: false },
      { value: 1, zoom: 16, type: "EMPTY", selected: false },
      { value: 1, zoom: 16, type: "EMPTY", selected: false },
      { value: 1, zoom: 16, type: "EMPTY", selected: false },
      { value: 1, zoom: 16, type: "EMPTY", selected: false },
      { value: 1, zoom: 16, type: "EMPTY", selected: false },
      { value: 1, zoom: 16, type: "EMPTY", selected: false },
      { value: 1, zoom: 16, type: "EMPTY", selected: false },
    ],
  },
];

const DEFAULT_ARRANGEMENT_STATE: ArrangementState = {
  tracks: [
    {
      id: "Bass",
      voices: 4,
      patterns: [INIT_PATTERN_POOL_STATE[0]],
    },
    {
      id: "Drums",
      voices: 4,
      patterns: [INIT_PATTERN_POOL_STATE[0]],
    },
  ],
  bpm: 120,
};

export function getArrangementLength(arrangement: ArrangementState) {
  let arrangementLength = 0;

  arrangement.tracks[0].patterns.forEach((pattern) => (arrangementLength += pattern.data.length));
  return arrangementLength;
}

export const ArrangementState: ArrangementState = DEFAULT_ARRANGEMENT_STATE;
