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

function transpose_by_octave(frequency: number, octave: number) {
  return frequency * 2 ** octave;
}

export function key_note(note: number) {
  if (AppState.octave.value === 0) {
    play_note(chromatic_notes[note]);
  } else {
    play_note(transpose_by_octave(chromatic_notes[note], AppState.octave.value));
  }
}

export function octave_up() {
  AppState.octave.value += 1;
}

export function octave_down() {
  AppState.octave.value -= 1;
}
