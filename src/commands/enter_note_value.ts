import { play_note } from "../audio/audio";
import { chromatic_notes } from "../data/notes";
import { AppState } from "../state";

// Some magic numbers in this file.
// Can for sure be avoided but ok for now
// 127 is the length of our notes array
// 36 is the keyboard offset so that there's room to transpose down

function select_pitch(note_index: number, octave: number, semitone: number) {
  const desired_note = note_index + octave + semitone;
  AppState.transposition.value = desired_note;

  if (desired_note >= 127) {
    return chromatic_notes[127];
  } else if (desired_note <= 0) {
    return chromatic_notes[0];
  } else {
    return chromatic_notes[desired_note];
  }
}

// This is gonna be "Preview" later on.
// The same play_note method should be called both by the user - during input; and by the program during playback.
export function enter_note_value(note: number) {
  play_note(select_pitch(note + 36, AppState.octave.value, AppState.semitone.value));
}
