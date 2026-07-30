import { attach_key_listener } from "./keys/attach_key_listener";
import { command_palette } from "./ui/command_palette/dialog";
import { generate_mock_grid } from "./ui/grid/generate_mock_grid";
import { reactive_ui } from "./ui/reactive_ui";

generate_mock_grid();
attach_key_listener();
reactive_ui();
command_palette();
