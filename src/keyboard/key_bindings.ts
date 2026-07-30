import { k_ToggleArranger } from "../actions/toggle_arranger";
import { k_TogglePlaying } from "../actions/toggle_playing";

export const key_bindings: Record<string, () => void> = {
  Enter: k_TogglePlaying,
  Tab: k_ToggleArranger,
};
