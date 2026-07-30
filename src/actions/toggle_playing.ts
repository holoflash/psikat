import { AppState } from "../state";

// This doesn't do anything important yet but will be crucial later
export function k_TogglePlaying() {
  AppState.playing.value = !AppState.playing.value;
}
