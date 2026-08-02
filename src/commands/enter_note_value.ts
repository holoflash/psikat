import { play_note } from "../audio/audio";
import { NOTE_FREQUENCIES } from "../data/notes";
import { AppState } from "../state/app_state";

// Some magic numbers in this file.
// Can for sure be avoided but ok for now
// 127 is the length of our notes array
function select_pitch(note_index: number, octave: number, semitone: number) {
  const octave_to_semitones = octave !== 0 ? octave * 12 : octave;
  const desired_note = note_index + octave_to_semitones + semitone;

  if (desired_note >= 127) {
    return NOTE_FREQUENCIES[127];
  } else if (desired_note <= 0) {
    return NOTE_FREQUENCIES[0];
  } else {
    return NOTE_FREQUENCIES[desired_note];
  }
}

// This is gonna be "Preview" later on.
// The same play_note method should be called both by the user - during input; and by the program during playback.
export function enter_note_value(note: number) {
  play_note(
    select_pitch(note, AppState.transposition.octave.value, AppState.transposition.semitone.value),
  );
}
