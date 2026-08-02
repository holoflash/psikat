import { NOTE_NAMES } from "../../data/notes";
import { create_dom_element } from "../../utils/create_dom_element";

type Pattern = {
  name: string;
  voices: number;
  automation: number;
  data: number[][];
};

const TEST_PATTERN: Pattern = {
  name: "Pattern 1",
  voices: 4,
  automation: 1,
  data: [
    [1, 5, -1, -1, 999],
    [2, 6, -1, -1, 999],
    [3, 7, -1, -1, 999],
    [4, 8, -1, -1, 999],
  ],
};

// STEP 1. Convert THAT ^ to this v
// ["NOTE", "NOTE", "NOTE", "NOTE", "FX" ],
// ["···",  "···",  "···",  "···",  "···"],
// ["···",  "···",  "···",  "···",  "···"],
// ["···",  "···",  "···",  "···",  "···"],
// ["···",  "···",  "···",  "···",  "···"],
// ["···",  "···",  "···",  "···",  "···"],
export function prep_data(pattern: Pattern) {
  const table_array = [];
  // HEADER
  const header_array = [];

  for (let i = 0; i < pattern.voices + pattern.automation; i++) {
    if (i < pattern.voices) {
      header_array.push("NOTE");
    } else {
      header_array.push("FX");
    }
  }
  table_array.push(header_array);

  // BODY
  // this can probably be done simpler with reduce or something,
  // but I'll come back to it
  pattern.data.forEach((row) => {
    const sub_array: string[] = [];
    row.forEach((value) => {
      if (value > NOTE_NAMES.length) {
        sub_array.push(value.toString());
      } else if (value === -1) {
        sub_array.push("···");
      } else {
        sub_array.push(NOTE_NAMES[value]);
      }
    });
    table_array.push(sub_array);
  });
  return table_array;
}

export function generate_grid(pattern = TEST_PATTERN) {
  const data = prep_data(pattern);
  const table = create_dom_element("table", { id: "pattern" });
  for (var i = 0; i < data.length; i++) {
    var tr = table.insertRow();
    for (var j = 0; j < data[i].length; j++) {
      var td = tr.insertCell();
      td.appendChild(document.createTextNode(data[i][j]));
    }
  }
  document.getElementById("main-grid")!.appendChild(table);
}

// The fun (and pain) of developing without AI!
// I got to discover on my own that there are HTMLTableElement methods,
// that let you create tables without having to manually add each required element!!!
// I spent hours trying to keep in my head where tr/thd/td goes and what props they need
// before discovering insertRow() and insertCell() on stack overflow out of frustration
// I will remember this forever!
