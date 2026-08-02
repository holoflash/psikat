import { AppState } from "../state/app_state";

export function toggle_command_palette() {
  AppState.command_palette_open.value = !AppState.command_palette_open.value;
}
