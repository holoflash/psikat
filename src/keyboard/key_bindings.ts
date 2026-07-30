import { k_note } from "../actions/note";
import { k_ToggleArranger } from "../actions/toggle_arranger";
import { k_TogglePlaying } from "../actions/toggle_playing";

// This is fine for single key presses but is gonna need to be a lot smarter
// to handle multiple modifier keys pressed etc.
export const key_bindings: Record<string, () => void> = {
  Enter: k_TogglePlaying,
  Tab: k_ToggleArranger,
  z: () => k_note(0),
  x: () => k_note(1),
  c: () => k_note(2),
  v: () => k_note(3),
  b: () => k_note(4),
  n: () => k_note(5),
  m: () => k_note(6),
  a: () => k_note(7),
  s: () => k_note(8),
  d: () => k_note(9),
  f: () => k_note(10),
  g: () => k_note(11),
  h: () => k_note(12),
  j: () => k_note(13),
  k: () => k_note(14),
  l: () => k_note(15),
  q: () => k_note(16),
  w: () => k_note(17),
  e: () => k_note(18),
  r: () => k_note(19),
  t: () => k_note(20),
  y: () => k_note(21),
  u: () => k_note(22),
  i: () => k_note(23),
  o: () => k_note(24),
  p: () => k_note(25),
};
