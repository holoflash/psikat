import { enter_note_value } from "./enter_note_value";
import { toggle_view } from "./toggle_view";
import { toggle_command_palette } from "./toggle_command_palette";
import { toggle_playing } from "./toggle_playing";
import { transpose } from "./transpose";
import { MUSICAL_KEYBOARD } from "../data/musical_keyboard";
import { AppState } from "../state/app_state";
import { CursorState } from "../state/cursor";

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
    // oxlint-disable-next-line --- just sketching...
    const table = document.getElementById("pattern") as HTMLTableElement;

    // Some real bs down here but it's working (for now)
    function toggle_cell() {
      table.querySelectorAll(".active").forEach((element) => {
        element.className = "";
      });
      table.rows[CursorState.position_y.value].cells[CursorState.position_x.value].className =
        "active";
    }
    if (key === "ARROWUP") {
      CursorState.position_y.value--;
      if (CursorState.position_y.value < 1) {
        CursorState.position_y.value = 4;
      }
      toggle_cell();
    }
    if (key === "ARROWDOWN") {
      // read from pattern data later
      if (CursorState.position_y.value === 4) {
        CursorState.position_y.value = 0;
      }
      CursorState.position_y.value++;
      toggle_cell();
    }
    if (key === "ARROWRIGHT") {
      // read from pattern data later
      CursorState.position_x.value++;
      if (CursorState.position_x.value === 5) {
        CursorState.position_x.value = 0;
      }
      toggle_cell();
    }
    if (key === "ARROWLEFT") {
      if (CursorState.position_x.value < 1) {
        CursorState.position_x.value = 5;
      }
      CursorState.position_x.value--; // read from pattern data later
      toggle_cell();
    }
    toggle_cell();
  }
  return;
}
