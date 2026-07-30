import { AppState } from "../state";

export function reactive_ui() {
  const app_octave_state_display = document.getElementById("octave-state");
  const app_playing_state_display = document.getElementById("playing-state");
  const app_arranger_state_display = document.getElementById("arranger-state");

  AppState.octave.effect(() => {
    if (!app_octave_state_display) return;
    app_octave_state_display.textContent = `OCTAVE ${AppState.octave.value}`;
  });

  AppState.playing.effect(() => {
    if (!app_playing_state_display) return;
    app_playing_state_display.textContent = AppState.playing.value ? "PLAYING" : "STOPPED";
  });

  AppState.arranger.effect(() => {
    if (!app_arranger_state_display) return;
    app_arranger_state_display.textContent = AppState.arranger.value
      ? "ARRANGER"
      : "PATTERN EDITOR";
  });
}
