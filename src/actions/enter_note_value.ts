import { play_note } from "../audio/audio";
import { chromatic_notes } from "../data/notes";
import { AppState } from "../state";

function calculate_current_pitch(note_index: number, octave: number, semitone: number) {
  const octave_in_semitones = octave === 0 ? octave : octave * 12;
  let desired_note = note_index + octave_in_semitones + semitone;

  if (desired_note > 127) {
    return chromatic_notes[127];
  } else if (desired_note <= 0) {
    return chromatic_notes[0];
  } else {
    return chromatic_notes[desired_note];
  }
}

// Trying to keep ALL commands in this folder
// Gonna end up with a lot of wrapper functions
export function enter_note_value(note: number) {
  play_note(calculate_current_pitch(note, AppState.octave.value, AppState.semitone.value));
}
