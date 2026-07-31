import { enter_note_value } from "../actions/enter_note_value";
import { k_ToggleArranger } from "../actions/toggle_arranger";
import { k_TogglePlaying } from "../actions/toggle_playing";

// This is fine for single key presses but is gonna need to be a lot smarter
// to handle multiple modifier keys pressed etc.
export const key_bindings: Record<string, () => void> = {
  Enter: k_TogglePlaying,
  Tab: k_ToggleArranger,
  // Starting from what I'm calling Octave 0 in the chromatic_notes
  z: () => enter_note_value(48),
  x: () => enter_note_value(49),
  c: () => enter_note_value(50),
  v: () => enter_note_value(51),
  b: () => enter_note_value(52),
  n: () => enter_note_value(53),
  m: () => enter_note_value(54),
  a: () => enter_note_value(55),
  s: () => enter_note_value(56),
  d: () => enter_note_value(57),
  f: () => enter_note_value(58),
  g: () => enter_note_value(59),
  h: () => enter_note_value(60),
  j: () => enter_note_value(61),
  k: () => enter_note_value(62),
  l: () => enter_note_value(63),
  q: () => enter_note_value(64),
  w: () => enter_note_value(65),
  e: () => enter_note_value(66),
  r: () => enter_note_value(67),
  t: () => enter_note_value(68),
  y: () => enter_note_value(69),
  u: () => enter_note_value(70),
  i: () => enter_note_value(71),
  o: () => enter_note_value(72),
  p: () => enter_note_value(73),
};
