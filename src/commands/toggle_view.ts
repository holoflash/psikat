import { AppState } from "../state";

export function toggle_view() {
  if (AppState.view.value === "PATTERN_EDITOR") {
    AppState.view.value = "ARRANGER";
  } else if (AppState.view.value === "ARRANGER") {
    AppState.view.value = "OTHER";
  } else if (AppState.view.value === "OTHER") {
    AppState.view.value = "PATTERN_EDITOR";
  }
}
