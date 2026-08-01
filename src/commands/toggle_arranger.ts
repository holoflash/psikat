import { AppState } from "../state";

export function toggle_arranger() {
  AppState.arranger.value = !AppState.arranger.value;
}
