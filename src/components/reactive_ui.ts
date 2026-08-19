import { geometry_circular } from "../geometry";
import {
  s_audio_initialized,
  s_playing,
  s_view,
  s_transposition,
  s_current_zoom,
  ZOOM_LEVELS,
} from "../state";

// Just threw everything in here for now
export function reactive_ui() {
  const app_octave_state_display = document.getElementById("octave-state");
  const app_semitone_state_display = document.getElementById("semitone-state");
  const app_playing_state_display = document.getElementById("playing-state");
  const app_arranger_state_display = document.getElementById("arranger-state");
  const app_zooom_state_display = document.getElementById("zoom-state");
  const app_enable_audio_button = document.getElementById("worklet-init");

  s_audio_initialized.effect(() => {
    if (!app_enable_audio_button) return;
    app_enable_audio_button.textContent = s_audio_initialized.value
      ? "AUDIO ENGAGED"
      : "ENABLE AUDIO";
  });

  s_transposition.octave.effect(() => {
    if (!app_octave_state_display) return;
    app_octave_state_display.textContent = `OCTAVE ${s_transposition.octave.value}`;
  });

  s_transposition.semitone.effect(() => {
    if (!app_semitone_state_display) return;
    app_semitone_state_display.textContent = `SEMITONE ${s_transposition.semitone.value}`;
  });

  s_playing.effect(() => {
    if (!app_playing_state_display) return;
    app_playing_state_display.textContent = s_playing.value ? "PLAYING" : "STOPPED";
  });

  s_view.effect(() => {
    if (!app_arranger_state_display) return;
    app_arranger_state_display.textContent = s_view.value;
  });

  s_current_zoom.effect(() => {
    if (!app_zooom_state_display) return;
    app_zooom_state_display.textContent = ZOOM_LEVELS[s_current_zoom.value].toString();

    geometry_circular();
  });
}
