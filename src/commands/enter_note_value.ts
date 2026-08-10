import { play_note } from "../audio/audio";
import { NOTE_FREQUENCIES } from "../data/notes";
import { MAX_NOTE_RANGE, OCTAVE, s_transposition } from "../state";

function select_pitch(note_index: number) {
  const octave_to_semitones =
    s_transposition.octave.value !== 0
      ? s_transposition.octave.value * OCTAVE
      : s_transposition.octave.value;
  const desired_note = note_index + octave_to_semitones + s_transposition.semitone.value;

  if (desired_note >= MAX_NOTE_RANGE) {
    return MAX_NOTE_RANGE;
  } else if (desired_note <= 0) {
    return 0;
  } else {
    return desired_note;
  }
}

// This is gonna be "Preview" later on.
// The same play_note method should be called both by the user - during input; and by the program during playback.
export function enter_note_value(note: number) {
  play_note(NOTE_FREQUENCIES[select_pitch(note)]);
}
