import { AppState } from "../state";

// All of this can be moved out into "components" later on
// Just threw everything in here for now
export function reactive_ui() {
  const app_octave_state_display = document.getElementById("octave-state");
  const app_semitone_state_display = document.getElementById("semitone-state");
  const app_playing_state_display = document.getElementById("playing-state");
  const app_arranger_state_display = document.getElementById("arranger-state");
  const app_enable_audio_button = document.getElementById("worklet-init");

  AppState.audio_initialized.effect(() => {
    if (!app_enable_audio_button) return;
    app_enable_audio_button.textContent = AppState.audio_initialized.value
      ? "AUDIO ENGAGED"
      : "ENABLE AUDIO";
  });

  AppState.transposition.octave.effect(() => {
    if (!app_octave_state_display) return;
    app_octave_state_display.textContent = `OCTAVE ${AppState.transposition.octave.value}`;
  });

  AppState.transposition.semitone.effect(() => {
    if (!app_semitone_state_display) return;
    app_semitone_state_display.textContent = `SEMITONE ${AppState.transposition.semitone.value}`;
  });

  AppState.playing.effect(() => {
    if (!app_playing_state_display) return;
    app_playing_state_display.textContent = AppState.playing.value ? "PLAYING" : "STOPPED";
  });

  AppState.view.effect(() => {
    if (!app_arranger_state_display) return;
    app_arranger_state_display.textContent = AppState.view.value;
  });
}
