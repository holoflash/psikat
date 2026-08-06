import { NOTE_NAMES } from "../data/notes";
import type { ArrangementState } from "../state/arrangement_state";
import { create_dom_element } from "../utils/create_dom_element";

// Simplest full grid rendering thus far
// However.. I wonder if I can express all of this in a shallow array instead of a deeply nested object
export function render_arrangement(arrangement: ArrangementState) {
  const container = document.getElementById("arrangement");
  //-------------- BEAT COUNT ROW--------------------------------------------------
  const beatRow = create_dom_element("div");
  const beatCount = arrangement.tracks[0].patterns[0].data.length;
  for (let i = 0; i < beatCount; i++) {
    beatRow.append(create_dom_element("div", { textContent: (i + 1).toString() }));
  }
  container?.append(beatRow);
  //--------------------------------------------------------------------------------

  arrangement.tracks.forEach((track) => {
    const trackContainer = create_dom_element("div");
    trackContainer.append(create_dom_element("div", { textContent: track.id }));

    track.patterns.forEach((pattern) => {
      pattern.data.forEach((cell) => {
        trackContainer.append(create_dom_element("div", { textContent: NOTE_NAMES[cell.value] }));
      });
    });
    container?.append(trackContainer);
  });
}
