import { attachKeyListener } from "./keyboard_handler";

// This is all really stupid but it's just a placeholder.
const mock_grid = document.getElementById("mock-grid");
const notes = [
  "C-4",
  "C#4",
  "D-4",
  "D#4",
  "E-4",
  "F-4",
  "F#4",
  "G-4",
  "G#4",
  "A-4",
  "A#4",
  "B-4",
  "C-5",
  "···",
];
function getRandomNote() {
  return notes[Math.floor(Math.random() * notes.length)];
}

// <tr>
//   <th scope="row">01</th>
//   <td>C#4</td>
//   <td>··</td>
// </tr>

// Feels insane writing this by hand in 2026 but it's relaxing
for (let i = 0; i <= 10; i++) {
  const table_tr = document.createElement("tr");

  const beat = document.createElement("th");
  beat.scope = "row";
  beat.textContent = i.toString().padStart(2, "0");

  table_tr.append(beat);

  for (let j = 0; j < 4; j++) {
    const note = document.createElement("td");
    note.textContent = getRandomNote();
    table_tr.append(note);
  }

  const fx = document.createElement("td");
  fx.textContent = "···";
  table_tr.append(fx);
  mock_grid?.append(table_tr);
}

attachKeyListener();
