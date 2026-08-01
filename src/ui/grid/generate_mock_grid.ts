import { create_dom_element } from "../../utils/create_dom_element";

type Pattern = {
  name: string;
  voices: number;
  data: number[];
};

type Track = {
  name: string;
  voices: number; // Needs this to know which patterns fit
  patterns: Pattern;
};
const TEST_PATTERN: Pattern = {
  name: "Pattern 1",
  // The voices value let's us know in what chunks to split the pattern
  // In the future, if the voice count is changed, we can simply trim down the array
  voices: 1,
  data: [
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 999, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 999,
  ],
};

const TEST_TRACK: Track = {
  name: "Track 1",
  voices: 1,
  patterns: TEST_PATTERN,
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
//    </tr>
//  </tbody>
//</table>
export function generate_mock_grid() {
  const table = document.getElementById("pattern-grid");
  const body = create_dom_element("tbody");
  const thead = create_dom_element("thead");
  const head_tr = create_dom_element("tr");

  const beat_header = create_dom_element("th", { scope: "col", textContent: "BEAT" });
  head_tr.append(beat_header);

  const note_header = create_dom_element("th", {
    scope: "col",
    colSpan: TEST_TRACK.patterns.voices,
    textContent: TEST_TRACK.patterns.name,
  });
  head_tr.append(note_header);

  thead.append(head_tr);
  table?.append(thead);

  // beat markers
  for (let i = 0; i < TEST_TRACK.patterns.data.length; i++) {
    const body_tr = create_dom_element("tr");
    const beat_th = create_dom_element("th", {
      scope: "row",
      textContent: (i + 1).toString().padStart(2, "0"),
    });
    const note_td = create_dom_element("td", {
      textContent: (i + 1).toString().padStart(2, "0"),
    });
    body_tr.append(beat_th, note_td);
    body.append(body_tr);
  }

  table?.append(body);
  console.log(table);
  // To be continued!
}

// const note_td = create_dom_element("td", {
//   textContent: NOTE_NAMES[TEST_TRACK.patterns[i].data[j]],
// });
// body_tr.append(note_td);
// if (i % (track.pattern.data.length / track.voices) === 0) {
