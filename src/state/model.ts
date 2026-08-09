import type { Signal } from "../utils/dom/signal";

export type CursorState = {
  arranger_pattern: Signal<number>;
  pattern_cell: Signal<number>;
};
export type PatternCell = {
  value: number;
  zoom: number;
};

export type Pattern = PatternCell[];

export type TranspositionState = {
  octave: Signal<number>;
  semitone: Signal<number>;
};

export type ArrangementState = Signal<number[]>;

export type ZoomLevel = 4 | 6 | 8 | 12 | 16 | 24 | 32 | 48 | 64 | 96 | 128;
