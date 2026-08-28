import { s_playing } from "../state";

export function toggle_playing() {
  s_playing.value = !s_playing.value;
}
