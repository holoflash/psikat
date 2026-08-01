import { enter_note_value } from "../commands/enter_note_value";
import { toggle_arranger } from "../commands/toggle_arranger";
import { toggle_command_palette } from "../commands/toggle_command_palette";
import { toggle_playing } from "../commands/toggle_playing";
import { transpose } from "../commands/transpose";
import { MUSICAL_KEYBOARD } from "../data/musical_keyboard";

function prevent_default(event: KeyboardEvent) {
  event.preventDefault();
  event.stopPropagation();
}

export function attach_key_listener() {
  document.addEventListener("keydown", (event: KeyboardEvent) => {
    const key = event.key.toUpperCase();
    const cmd_shift = event.metaKey && event.shiftKey; // Command+Shift | Ctrl+Shift

    if (cmd_shift) {
      prevent_default(event);
      if (key === "ARROWUP") transpose("OCTAVE_UP");
      if (key === "ARROWDOWN") transpose("OCTAVE_DOWN");
      if (key === "ARROWRIGHT") transpose("SEMITONE_UP");
      if (key === "ARROWLEFT") transpose("SEMITONE_DOWN");
      if (key === "P") toggle_command_palette();
    } else {
      if (key === "TAB") {
        prevent_default(event);
        toggle_arranger();
      }
      if (key === "ENTER") {
        prevent_default(event);
        toggle_playing();
      }
      // This is better than before but there may still be a way to do this better
      if (MUSICAL_KEYBOARD.includes(key)) {
        enter_note_value(MUSICAL_KEYBOARD.indexOf(key));
      }
    }
    return;
  });
}
