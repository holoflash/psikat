import { keyboard_event_to_command } from "./commands/keyboard_event_to_command";
import { init_audio } from "./audio/audio";
import { reactive_ui } from "./components/reactive_ui";
import { command_palette } from "./components/command_palette/dialog";
import { render_arrangement } from "./components/arrangement";
import { s_arrangement } from "./state";

// Listeners go here
document.addEventListener("keydown", keyboard_event_to_command);

document.getElementById("worklet-init")?.addEventListener("click", () => {
  void init_audio();
});

// Later on, all of these should be a single function call: initialize_UI() or something.
// Besides, I want to handwrite as much as possible in HTML
reactive_ui();
command_palette();
render_arrangement(s_arrangement);
