// Default state
window.psikat_state = { playing: false, arranger: false };
const state = window.psikat_state;

// These are just for debugging
const app_playing_state_display = document.getElementById("playing-state");
const app_arranger_state_display = document.getElementById("arranger-state");

type RegisteredKeys = "Enter" | "Tab";

function k_TogglePlaying() {
  state.playing = !state.playing;
  if (!app_playing_state_display) return;
  app_playing_state_display.textContent = state.playing ? "PLAYING" : "STOPPED";
}

function k_ToggleArranger() {
  state.arranger = !state.arranger;
  if (!app_arranger_state_display) return;
  app_arranger_state_display.textContent = state.arranger ? "ARRANGER" : "PATTERN EDITOR";
}

const KEY_BINDINGS: Record<RegisteredKeys, () => void> = {
  Enter: k_TogglePlaying,
  Tab: k_ToggleArranger,
};

function resolveKeyCommand(key_pressed: KeyboardEvent) {
  switch (key_pressed.code) {
    case "Enter":
      KEY_BINDINGS[key_pressed.code]();
      break;
    case "Tab":
      KEY_BINDINGS[key_pressed.code]();
      break;
    default:
      return;
  }
}

// This is for catching keys and preventing their default behaviour so that we can use them for our purposes
// Should be avoided if possible but Tab is essential to the behaviour of psikat
window.addEventListener("load", () => {
  window.document.body.addEventListener("keydown", (event) => {
    if (event.key == "Tab") {
      event.stopPropagation();
      event.preventDefault();
      return false;
    }
    return true;
  });
});

export function attachKeyListener() {
  document.addEventListener("keyup", (event: KeyboardEvent) => {
    resolveKeyCommand(event);
  });
}
