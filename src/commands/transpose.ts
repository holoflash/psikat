import { AppState } from "../state";

// Should I attach all of these to one object/class instead?

export function transpose(amount: "OCTAVE_UP" | "OCTAVE_DOWN" | "SEMITONE_UP" | "SEMITONE_DOWN") {
  if (amount === "OCTAVE_UP") {
    AppState.octave.value += 12;
  }
  if (amount === "OCTAVE_DOWN") {
    AppState.octave.value -= 12;
  }
  if (amount === "SEMITONE_UP") {
    AppState.semitone.value++;
  }
  if (amount === "SEMITONE_DOWN") {
    AppState.semitone.value--;
  }
}
