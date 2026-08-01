import { enter_note_value } from "./enter_note_value";
import { toggle_view } from "./toggle_view";
import { toggle_command_palette } from "./toggle_command_palette";
import { toggle_playing } from "./toggle_playing";
import { transpose } from "./transpose";
import { MUSICAL_KEYBOARD } from "../data/musical_keyboard";
import { AppState } from "../state";

export function keyboard_event_to_command(event: KeyboardEvent) {
  const key = event.key.toUpperCase();
  const cmd_shift = event.metaKey && event.shiftKey;
  if (key === "TAB" || key == "ENTER" || cmd_shift) {
    event.preventDefault();
    event.stopPropagation();
  }

  // We'll need to handle key events while the command palette is open differently
  // This blocks all other registered commands except the exit command
  if (AppState.command_palette_open.value) {
    if (key === "P" && cmd_shift) toggle_command_palette();
    return;
  }

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
    if (key === "TAB") toggle_view();
    if (key === "ENTER") {
      toggle_playing();
    }
    // Musical Keyboard commands
    if (MUSICAL_KEYBOARD.includes(key)) {
      enter_note_value(MUSICAL_KEYBOARD.indexOf(key));
    }
  }
  return;
}
