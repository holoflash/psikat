import { AppState } from "../state/app_state";

export function toggle_playing() {
  AppState.playing.value = !AppState.playing.value;
}
