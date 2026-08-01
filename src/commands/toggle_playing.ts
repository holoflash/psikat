import { AppState } from "../state";

export function toggle_playing() {
  AppState.playing.value = !AppState.playing.value;
}
