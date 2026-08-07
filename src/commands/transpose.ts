// The "whiles" are to cap how much the keyboard can be transposed
// There's out of bounds handling for pitch generation elsewhere

import { s_transposition } from "../state";

// So the safety is just to prevent UI from overflowing with large numbers
export function transpose(amount: "OCTAVE_UP" | "OCTAVE_DOWN" | "SEMITONE_UP" | "SEMITONE_DOWN") {
  if (amount === "OCTAVE_UP") {
    while (s_transposition.octave.value < 10) {
      s_transposition.octave.value += 1;
      break;
    }
  }
  if (amount === "OCTAVE_DOWN") {
    while (s_transposition.octave.value > -2) {
      s_transposition.octave.value -= 1;
      break;
    }
  }
  if (amount === "SEMITONE_UP") {
    while (s_transposition.semitone.value < 11) {
      s_transposition.semitone.value++;
      break;
    }
  }
  if (amount === "SEMITONE_DOWN") {
    while (s_transposition.semitone.value > -11) {
      s_transposition.semitone.value--;
      break;
    }
  }
}
