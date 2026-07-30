import { octave_down, octave_up } from "../actions/note";
import { AppState } from "../state";
import { key_bindings } from "./key_bindings";

export function attach_key_listener() {
  document.addEventListener("keydown", (event: KeyboardEvent) => {
    const cmd_shift = event.metaKey && event.shiftKey;
    // Steal default Tab behaviour
    if (event.key in key_bindings) {
      if (event.key === "Tab") {
        event.preventDefault();
        event.stopPropagation();
      }
      if (!cmd_shift) {
        key_bindings[event.key]();
      }
    }
    if (event.key === "ArrowUp" && cmd_shift) {
      event.preventDefault();
      event.stopPropagation();
      octave_up();
    }
    if (event.key === "ArrowDown" && cmd_shift) {
      event.preventDefault();
      event.stopPropagation();
      octave_down();
    }
    if (event.key === "p" && cmd_shift) {
      AppState.command_palette_open.value = !AppState.command_palette_open.value;
    }
    return;
  });
}
