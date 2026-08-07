import { s_view } from "../state";

export function toggle_view() {
  if (s_view.value === "PATTERN_EDITOR") {
    s_view.value = "ARRANGER";
  } else if (s_view.value === "ARRANGER") {
    s_view.value = "OTHER";
  } else if (s_view.value === "OTHER") {
    s_view.value = "PATTERN_EDITOR";
  }
}
