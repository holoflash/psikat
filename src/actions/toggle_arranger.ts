import { APP_STATE } from "../state";

const app_arranger_state_display = document.getElementById("arranger-state");

export function k_ToggleArranger() {
  APP_STATE.arranger = !APP_STATE.arranger;
  if (!app_arranger_state_display) return;
  app_arranger_state_display.textContent = APP_STATE.arranger ? "ARRANGER" : "PATTERN EDITOR";
}
