import { signal, type Signal } from "../utils/dom/signal";
import type { TranspositionState, ZoomLevel } from "./model";

//##########################################################
//                    CONSTANTS
//##########################################################
// TODO: consider making ZOOM_LEVELS an object
export const ZOOM_LEVELS: ZoomLevel[] = [
  4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 24, 28, 32, 40, 48, 56, 64, 80, 96, 112, 128,
];

/**
 * @deprecated new one is 13340
 */
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
