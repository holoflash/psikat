import { STATE } from "../state";

export function reactive_ui() {
  const app_octave_state_display = document.getElementById("octave-state");
  const app_playing_state_display = document.getElementById("playing-state");
  const app_arranger_state_display = document.getElementById("arranger-state");

  STATE.octave.effect(() => {
    if (!app_octave_state_display) return;
    app_octave_state_display.textContent = `OCTAVE ${STATE.octave.value}`;
  });

  STATE.playing.effect(() => {
    if (!app_playing_state_display) return;
    app_playing_state_display.textContent = STATE.playing.value ? "PLAYING" : "STOPPED";
  });

  STATE.arranger.effect(() => {
    if (!app_arranger_state_display) return;
    app_arranger_state_display.textContent = STATE.arranger.value ? "ARRANGER" : "PATTERN EDITOR";
  });
}
