import { init_audio } from "./audio/audio";
import { command_palette } from "./ui/command_palette/dialog";
import { reactive_ui } from "./ui/reactive_ui";
import { keyboard_event_to_command } from "./commands/keyboard_event_to_command";

// Listeners go here
document.addEventListener("keydown", keyboard_event_to_command);
document.getElementById("worklet-init")?.addEventListener("click", () => {
  void init_audio();
});

// Later on, all of these should be a single function call: initialize_UI() or something.
// Besides, I want to handwrite as much as possible in HTML
reactive_ui();
command_palette();
