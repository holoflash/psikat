import { play_note } from "../audio/audio";
import { chromatic_notes } from "../data/notes";
import { AppState } from "../state";

function calculate_current_pitch(frequency: number, octave: number, semitone: number) {
  // Now that I have the full midi range hardcoded, I don't need to calculate the frequency like this!
  const octave_in_semitones = octave === 0 ? octave : octave * 12;
  const desired_transpostion = octave_in_semitones + semitone;
  console.log(desired_transpostion);
  return frequency * 2 ** (desired_transpostion / 12);
}

// Trying to keep ALL commands in this folder
// Gonna end up with a lot of wrapper functions
export function enter_note_value(note: number) {
  play_note(
    calculate_current_pitch(chromatic_notes[note], AppState.octave.value, AppState.semitone.value),
  );
}
