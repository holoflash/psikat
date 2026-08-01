// import { NOTE_NAMES } from "../../data/notes";

type Pattern = {
  name: string;
  voices: 4;
  data: number[];
};

type Track = {
  name: string;
  voices: number; // Needs this to know which patterns fit
  patterns: Pattern[];
};
const TEST_PATTERN: Pattern = {
  name: "Pattern 1",
  // The voices value let's us know in what chunks to split the pattern
  // In the future, if the voice count is changed, we can simply trim down the array
  voices: 4,
  data: [
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 999, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 999, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 999, 1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 999,
  ],
};

const track: Track = {
  name: "Track 1",
  voices: 4,
  patterns: [TEST_PATTERN], // this
};
//<table>
//  <thead id="grid-head">
//    <tr>
//     <th scope="col"></th> // BEAT HEADER
//      <th scope="col" colspan="4">Pattern 1</th> // PATTERN HEADER
//    </tr>
//  </thead>
//  <tbody id="mock-grid">
//    <tr>
//      <th scope="row">01</th>
//      <td>C#4</td>
//      <td>··</td>
//    </tr>
//  </tbody>
//</table>
// export function generate_empty_grid(
//   bars: number,
//   steps: number,
//   voices: number,
//   pattern_name: string,
// ) {
//   //GRID HEADER
// }

// Daamn this is cleeean :D
function create_dom_element<T extends keyof HTMLElementTagNameMap>(
  tag_name: T,
  params?: Partial<HTMLElementTagNameMap[T]>,
): HTMLElement {
  const element = document.createElement(tag_name);
  if (params) {
    return Object.assign(element, { ...params });
  } else {
    return element;
  }
}

export function generate_mock_grid() {
  const table = document.getElementById("pattern-grid");
  const tbody = create_dom_element("tbody");
  const thead = create_dom_element("thead");
  const tr = create_dom_element("tr");
  const beat_header = create_dom_element("th", { scope: "col" });
  const note_header = create_dom_element("th", {
    scope: "col",
    colSpan: 4,
    textContent: track.patterns[0].name,
  });
  tr.append(beat_header, note_header);
  thead.append(tr);
  table?.append(thead, tbody);
  // To be continued!
  // for (let i = 0; i <= 16; i++) {
  //   const table_tr = document.createElement("tr");
  //   // if (i % (track.pattern.data.length / track.voices) === 0) {
  //   const beat = document.createElement("th");
  //   beat.scope = "row";
  //   beat.textContent = i.toString().padStart(2, "0");
  //   table_tr.append(beat);

  //   const note = document.createElement("td");
  //   note.textContent = NOTE_NAMES[0];
  //   table_tr.append(note);
  //   tbody.append(table_tr);
  // }
}
