import { NOTE_NAMES } from "../data/notes";
import { s_pattern_pool } from "../state";
import type { ArrangementState } from "../state/model";
import { dom_element } from "../utils/dom_element";

// Simplest full grid rendering thus far
// However.. I wonder if I can express all of this in a shallow array instead of a deeply nested object
export function render_arrangement(arrangement: ArrangementState) {
  const e_container = document.getElementById("arrangement");
  arrangement.value.forEach((pattern_reference) => {
    const e_pattern_container = dom_element("div", { className: "pattern-container" });
    s_pattern_pool.value[pattern_reference].forEach((cell) => {
      const e_cell = dom_element("div", {
        className: "pattern-cell",
        textContent: NOTE_NAMES[cell.value],
      });

      e_pattern_container.append(e_cell);
    });
    e_container?.append(e_pattern_container);
  });
}
