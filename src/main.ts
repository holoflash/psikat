import { init_audio } from "./audio/audio";
import { command_palette } from "./ui/command_palette/dialog";
import { generate_mock_grid } from "./ui/grid/generate_mock_grid";
import { print_mock } from "./ui/grid/model";
import { reactive_ui } from "./ui/reactive_ui";
import { attach_key_listener } from "./keyboard/attach_key_listener";

generate_mock_grid();
attach_key_listener();
reactive_ui();
command_palette();

// Can this be moved somewhere else?
document.getElementById("worklet-init")?.addEventListener("click", () => {
  void init_audio();
});

print_mock();
