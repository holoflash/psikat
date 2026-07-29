// This is all really stupid but it's just a placeholder.
const mock_grid = document.getElementById("mock-grid");
const notes = ["C-4", "D-4", "E-4", "F-4", "G-4", "A-4", "B-4", "C-5", "···"];
function getRandomNote() {
  return notes[Math.floor(Math.random() * notes.length)];
}

// <tr>
//   <th scope="row">01</th>
//   <td>C#4</td>
//   <td>··</td>
// </tr>

// Feels insane writing this by hand in 2026 but it's relaxing
for (let i = 0; i < 11; i++) {
  const table_tr = document.createElement("tr");

  const beat = document.createElement("th");
  beat.scope = "row";
  beat.textContent = i.toString().padStart(2, "0");

  const note1 = document.createElement("td");
  note1.textContent = getRandomNote();
  const note2 = document.createElement("td");
  note2.textContent = getRandomNote();
  const note3 = document.createElement("td");
  note3.textContent = getRandomNote();
  const note4 = document.createElement("td");
  note4.textContent = getRandomNote();

  const fx = document.createElement("td");
  fx.textContent = "···";
  table_tr.append(beat, note1, note2, note3, note4, fx);
  mock_grid?.append(table_tr);
}
