import { init_audio } from "./audio/audio";
import { command_palette } from "./interface/command_palette/dialog";
import { generate_mock_grid } from "./interface/grid/generate_mock_grid";
import { reactive_ui } from "./interface/reactive_ui";
import { attach_key_listener } from "./keys/attach_key_listener";

generate_mock_grid();
attach_key_listener();
reactive_ui();
command_palette();

// Can this be moved somewhere else?
document.getElementById("worklet-init")?.addEventListener("click", () => {
  void init_audio();
});
