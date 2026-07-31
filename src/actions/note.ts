import { play_note } from "../audio/audio";
import { AppState } from "../state";

const chromatic_notes = [
  130.81, // C3
  138.59, // C#3
  146.83, // D3
  155.56, // D#3
  164.81, // E3
  174.61, // F3
  185.0, // F#3
  196.0, // G3
  207.65, // G#3
  220.0, // A3
  233.08, // A#3
  246.94, // B3
  261.63, // C4
  277.18, // C#4
  293.66, // D4
  311.13, // D#4
  329.63, // E4
  349.23, // F4
  369.99, // F#4
  392.0, // G4
  415.3, // G#4
  440.0, // A4
  466.16, // A#4
  493.88, // B4
  523.25, // C5
  554.37, // C#5
];

function calculate_current_pitch(frequency: number, octave: number, semitone: number) {
  // Can probably be done in a cleaner way but it works
  const octave_in_semitones = octave === 0 ? octave : octave * 12;
  const desired_transpostion = octave_in_semitones + semitone;
  return frequency * 2 ** (desired_transpostion / 12);
}

// Trying to keep ALL commands in this folder
// Gonna end up with a lot of wrapper functions
export function key_note(note: number) {
  play_note(
    calculate_current_pitch(chromatic_notes[note], AppState.octave.value, AppState.semitone.value),
  );
}
