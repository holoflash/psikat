import { key_bindings } from "./key_bindings";

export function attach_key_listener() {
  document.addEventListener("keydown", (event: KeyboardEvent) => {
    // Steal default Tab behaviour
    if (event.key in key_bindings) {
      if (event.key == "Tab") {
        event.preventDefault();
        event.stopPropagation();
      }
      key_bindings[event.key]();
    }
    return;
  });
}
