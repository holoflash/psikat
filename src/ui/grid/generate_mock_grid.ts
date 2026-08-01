import { NOTE_NAMES } from "../../data/notes";

// Started out as a mock grid but gonna try this approach
// fully and see how much can be done before getting canvas involved
const mock_grid = document.getElementById("mock-grid");
// <tr>
//   <th scope="col"></th>
//   <th scope="col" colspan="4">Pattern 1</th>
//   <th scope="col">FX</th>
// </tr>

// <tr>
//   <th scope="row">01</th>
//   <td>C#4</td>
//   <td>··</td>
// </tr>
export function generate_mock_grid() {
  const grid_header = document.getElementById("grid-head");
  const beat_header = document.createElement("th");
  beat_header.scope = "col";
  const note_header = document.createElement("th");
  note_header.scope = "col";
  note_header.colSpan = 4;
  note_header.textContent = "PATTERN 1";
  const fx_header = document.createElement("th");
  fx_header.scope = "col";
  fx_header.textContent = "FX";
  grid_header?.append(beat_header, note_header, fx_header);

  for (let i = 0; i <= 10; i++) {
    const table_tr = document.createElement("tr");

    const beat = document.createElement("th");
    beat.scope = "row";
    beat.textContent = i.toString().padStart(2, "0");

    table_tr.append(beat);

    for (let j = 0; j < 4; j++) {
      const note = document.createElement("td");
      note.textContent = NOTE_NAMES[Math.floor(Math.random() * NOTE_NAMES.length)];
      table_tr.append(note);
    }

    const fx = document.createElement("td");
    fx.textContent = "···";
    table_tr.append(fx);
    mock_grid?.append(table_tr);
  }
}
