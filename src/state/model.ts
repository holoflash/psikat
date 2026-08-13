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

export type ZoomLevel =
  | 4
  | 5
  | 6
  | 7
  | 8
  | 10
  | 12
  | 16
  | 20
  | 24
  | 28
  | 32
  | 40
  | 48
  | 56
  | 64
  | 80
  | 96
  | 112
  | 128;
