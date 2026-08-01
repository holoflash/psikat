import { enter_note_value } from "./enter_note_value";
import { toggle_arranger } from "./toggle_arranger";
import { toggle_command_palette } from "./toggle_command_palette";
import { toggle_playing } from "./toggle_playing";
import { transpose } from "./transpose";
import { MUSICAL_KEYBOARD } from "../data/musical_keyboard";

export function keyboard_event_to_command(event: KeyboardEvent) {
  const key = event.key.toUpperCase();
  const cmd_shift = event.metaKey && event.shiftKey;

  // Command+Shift | Ctrl+Shift commands
  if (cmd_shift) {
    event.preventDefault();
    event.stopPropagation();
    if (key === "ARROWUP") transpose("OCTAVE_UP");
    if (key === "ARROWDOWN") transpose("OCTAVE_DOWN");
    if (key === "ARROWRIGHT") transpose("SEMITONE_UP");
    if (key === "ARROWLEFT") transpose("SEMITONE_DOWN");
    if (key === "P") toggle_command_palette();
  } else {
    // Other commands
    if (key === "TAB") {
      event.preventDefault();
      event.stopPropagation();
      toggle_arranger();
    }
    if (key === "ENTER") {
      event.preventDefault();
      event.stopPropagation();
      toggle_playing();
    }
    // Musical Keyboard commands
    if (MUSICAL_KEYBOARD.includes(key)) {
      enter_note_value(MUSICAL_KEYBOARD.indexOf(key));
    }
  }
  return;
}
