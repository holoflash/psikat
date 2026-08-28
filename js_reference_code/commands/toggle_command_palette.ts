import { s_command_palette_open } from "../state";

export function toggle_command_palette() {
  s_command_palette_open.value = !s_command_palette_open.value;
}
