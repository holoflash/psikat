import { generate_mock_grid } from "./grid/generate_mock_grid";
import { attach_key_listener } from "./keyboard/attach_key_listener";
import { reactive_ui } from "./reactive_ui";

generate_mock_grid();
attach_key_listener();
reactive_ui();
