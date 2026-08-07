import { signal, type Signal } from "../utils/signal";
import type { Pattern, TranspositionState, ArrangementState, CursorState } from "./model";

//##########################################################
//   Just for fun — prefixing all state variables with s_
//##########################################################

// State variables that don't need to be accessed together
export const s_view: Signal<"PATTERN_EDITOR" | "ARRANGER" | "OTHER"> = signal("PATTERN_EDITOR");
export const s_playing: Signal<boolean> = signal(false);
export const s_command_palette_open: Signal<boolean> = signal(false);
export const s_audio_initialized: Signal<boolean> = signal(false);

export const s_transposition: TranspositionState = {
  octave: signal(4),
  semitone: signal(0),
};

export const s_pattern_pool: Pattern[] = [
  {
    id: "pattern_1",
    voices: 4,
    fx: 1,
    data: [
      { value: 1, zoom: 16, type: "EMPTY" },
      { value: 1, zoom: 16, type: "EMPTY" },
      { value: 1, zoom: 16, type: "EMPTY" },
      { value: 1, zoom: 16, type: "EMPTY" },
      { value: 1, zoom: 16, type: "EMPTY" },
      { value: 1, zoom: 16, type: "EMPTY" },
      { value: 1, zoom: 16, type: "EMPTY" },
      { value: 1, zoom: 16, type: "EMPTY" },
    ],
  },
];

export const s_arrangement: ArrangementState = {
  tracks: [
    {
      id: "Bass",
      voices: 4,
      patterns: [s_pattern_pool[0]],
    },
    {
      id: "Drums",
      voices: 4,
      patterns: [s_pattern_pool[0]],
    },
  ],
  bpm: 120,
};

export const s_cursor: CursorState = {
  track: signal(0),
  position_x: signal(0),
  position_y: signal(1),
};
