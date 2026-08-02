import { AppState } from "../state/app_state";

// The "whiles" are to cap how much the keyboard can be transposed
// There's out of bounds handling for pitch generation elsewhere

// So the safety is just to prevent UI from overflowing with large numbers
export function transpose(amount: "OCTAVE_UP" | "OCTAVE_DOWN" | "SEMITONE_UP" | "SEMITONE_DOWN") {
  if (amount === "OCTAVE_UP") {
    while (AppState.transposition.octave.value < 10) {
      AppState.transposition.octave.value += 1;
      break;
    }
  }
  if (amount === "OCTAVE_DOWN") {
    while (AppState.transposition.octave.value > -2) {
      AppState.transposition.octave.value -= 1;
      break;
    }
  }
  if (amount === "SEMITONE_UP") {
    while (AppState.transposition.semitone.value < 11) {
      AppState.transposition.semitone.value++;
      break;
    }
  }
  if (amount === "SEMITONE_DOWN") {
    while (AppState.transposition.semitone.value > -11) {
      AppState.transposition.semitone.value--;
      break;
    }
  }
}
