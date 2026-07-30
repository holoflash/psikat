import { STATE } from "../state";

// This doesn't do anything important yet but will be crucial later
export function k_TogglePlaying() {
  STATE.playing.value = !STATE.playing.value;
}
