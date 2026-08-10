import { signal, type Signal } from "../utils/dom/signal";
import type {
  Pattern,
  TranspositionState,
  CursorState,
  ArrangementState,
  ZoomLevel,
} from "./model";

//##########################################################
//                    CONSTANTS
//##########################################################
export const ZOOM_LEVELS: ZoomLevel[] = [4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128];
export const ZOOM_LCD = 384; // Lowest zoom level common denominator
export const OCTAVE = 12;
export const MAX_NOTE_RANGE = 127; // TODO: should get this from the NOTES array instead

//##########################################################
//   Just for fun — prefixing all state variables with s_
//##########################################################

// State variables that don't need to be accessed together
export const s_view: Signal<"PATTERN_EDITOR" | "ARRANGER" | "OTHER"> = signal("PATTERN_EDITOR");
export const s_playing: Signal<boolean> = signal(false);
export const s_command_palette_open: Signal<boolean> = signal(false);
export const s_audio_initialized: Signal<boolean> = signal(false);
export const s_current_zoom: Signal<ZoomLevel> = signal(4);

export const s_transposition: TranspositionState = {
  octave: signal(4),
  semitone: signal(0),
};

export const s_pattern_pool: Signal<Pattern[]> = signal([
  [
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 1, zoom: 16 },
  ],
  [
    { value: 4, zoom: 16 },
    { value: 12, zoom: 16 },
    { value: 100, zoom: 16 },
    { value: 20, zoom: 16 },
    { value: 3, zoom: 16 },
    { value: 4, zoom: 16 },
    { value: 2, zoom: 16 },
    { value: 1, zoom: 16 },
    { value: 4, zoom: 16 },
    { value: 12, zoom: 16 },
    { value: 100, zoom: 16 },
    { value: 20, zoom: 16 },
    { value: 3, zoom: 16 },
    { value: 4, zoom: 16 },
    { value: 2, zoom: 16 },
    { value: 1, zoom: 16 },
  ],
]);

/**  Array of pattern pool entries by index */
export const s_arrangement: ArrangementState = signal([1]);

export const s_cursor: CursorState = {
  arranger_pattern: signal(0),
  pattern_cell: signal(0),
};
