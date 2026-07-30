import { APP_STATE } from "../state";

const app_playing_state_display = document.getElementById("playing-state");

export function k_TogglePlaying() {
  APP_STATE.playing = !APP_STATE.playing;
  if (!app_playing_state_display) return;
  app_playing_state_display.textContent = APP_STATE.playing ? "PLAYING" : "STOPPED";
}
