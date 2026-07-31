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
      AppState.octave.value += 1;
    }
    if (event.key === "ArrowDown" && cmd_shift) {
      event.preventDefault();
      event.stopPropagation();
      AppState.octave.value -= 1;
    }
    if (event.key === "ArrowLeft" && cmd_shift) {
      event.preventDefault();
      event.stopPropagation();
      AppState.semitone.value -= 1;
    }
    if (event.key === "ArrowRight" && cmd_shift) {
      event.preventDefault();
      event.stopPropagation();
      AppState.semitone.value += 1;
    }
    if (event.key === "p" && cmd_shift) {
      AppState.command_palette_open.value = !AppState.command_palette_open.value;
    }
    return;
  });
}
