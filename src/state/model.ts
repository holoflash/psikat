import type { Signal } from "../utils/signal";

export type CursorState = {
  track: Signal<number>;
  position_x: Signal<number>;
  position_y: Signal<number>;
};
export type PatternCell = {
  value: number;
  zoom: number;
  type: "NOTE" | "COMMAND" | "FX" | "EMPTY";
};

export type Pattern = {
  id: string;
  voices: number;
  fx: number;
  data: PatternCell[];
};

export type TranspositionState = {
  octave: Signal<number>;
  semitone: Signal<number>;
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
