import { STATE } from "../state";

// This doesn't do anything important yet but will be crucial later
export function k_ToggleArranger() {
  STATE.arranger.value = !STATE.arranger.value;
}
