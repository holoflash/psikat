import { Signal, signal } from "./utils/signal";

type AppState = {
  view: Signal<"PATTERN_EDITOR" | "ARRANGER" | "OTHER">;
  playing: Signal<boolean>;
  transposition: {
    octave: Signal<number>;
    semitone: Signal<number>;
  };
  cursor_position: { x: Signal<number>; y: Signal<number> };
  command_palette_open: Signal<boolean>;
  pitch: Signal<number>; // just put this here for now
  audio_initialized: Signal<boolean>;
};

const DEFAULT_STATE: AppState = {
  view: signal("PATTERN_EDITOR"),
  playing: signal(false),
  transposition: {
    octave: signal(4),
    semitone: signal(0),
  },
  command_palette_open: signal(false),
  pitch: signal(0),
  audio_initialized: signal(false),
  cursor_position: { x: signal(0), y: signal(0) },
};
export const AppState: AppState = DEFAULT_STATE;
