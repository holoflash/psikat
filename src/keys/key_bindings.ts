import { key_note } from "../actions/note";
import { k_ToggleArranger } from "../actions/toggle_arranger";
import { k_TogglePlaying } from "../actions/toggle_playing";

// This is fine for single key presses but is gonna need to be a lot smarter
// to handle multiple modifier keys pressed etc.
export const key_bindings: Record<string, () => void> = {
  Enter: k_TogglePlaying,
  Tab: k_ToggleArranger,
  z: () => key_note(0),
  x: () => key_note(1),
  c: () => key_note(2),
  v: () => key_note(3),
  b: () => key_note(4),
  n: () => key_note(5),
  m: () => key_note(6),
  a: () => key_note(7),
  s: () => key_note(8),
  d: () => key_note(9),
  f: () => key_note(10),
  g: () => key_note(11),
  h: () => key_note(12),
  j: () => key_note(13),
  k: () => key_note(14),
  l: () => key_note(15),
  q: () => key_note(16),
  w: () => key_note(17),
  e: () => key_note(18),
  r: () => key_note(19),
  t: () => key_note(20),
  y: () => key_note(21),
  u: () => key_note(22),
  i: () => key_note(23),
  o: () => key_note(24),
  p: () => key_note(25),
};
