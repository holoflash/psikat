// What is the grid? really?
// Break it down!...

type Divisor = 4 | 6 | 8 | 12 | 16 | 24 | 32 | 48 | 64 | 96 | 128;
type Cell = {
  type: "NOTE" | "COMMAND" | "FX" | "AUTOMATION";
  divisor: Divisor; // we need to know at what division the cell got its value assigned
  value: number;
};

type Column = {
  type: "VOICE" | "FX";
  rows: Cell[]; // tempted to add "steps" property, but that's just rows.length
};

type Pattern = { name: string; columns: Column[] };

type Track = {
  name: string;
  patterns: Pattern[];
};

type Arrangement = Track[];

// Sooomething like this:
const MOCK_ARRANGEMENT: Arrangement = [
  {
    name: "Track 1",
    patterns: [
      {
        name: "Pattern 1",
        columns: [
          {
            type: "VOICE",
            rows: [
              { type: "NOTE", divisor: 16, value: 0 },
              { type: "NOTE", divisor: 16, value: 1 },
              { type: "NOTE", divisor: 16, value: 2 },
              { type: "NOTE", divisor: 16, value: 3 },
              { type: "NOTE", divisor: 16, value: 4 },
              { type: "NOTE", divisor: 16, value: 5 },
              { type: "NOTE", divisor: 16, value: 6 },
              { type: "NOTE", divisor: 16, value: 7 },
              { type: "NOTE", divisor: 16, value: 8 },
              { type: "NOTE", divisor: 16, value: 9 },
              { type: "NOTE", divisor: 16, value: 10 },
              { type: "NOTE", divisor: 16, value: 11 },
              { type: "NOTE", divisor: 16, value: 12 },
              { type: "NOTE", divisor: 16, value: 13 },
              { type: "NOTE", divisor: 16, value: 14 },
              { type: "NOTE", divisor: 16, value: 15 },
            ],
          },
        ],
      },
    ],
  },
];

export function print_mock() {
  MOCK_ARRANGEMENT.forEach((track) => {
    console.log(`|  |  ${track.name}  |`);
    track.patterns.forEach((pattern) => {
      pattern.columns.forEach((col) => {
        console.log(`|  | ${pattern.name} |`);
        col.rows.forEach((row, i) => {
          console.log(
            `|${i.toString().padStart(2, "0")}| 1/${row.divisor} | ${row.value.toString().padStart(2, "0")} |`,
          );
        });
      });
    });
  });
}

// The above produces this:
// |  |  Track 1  |
// |  | Pattern 1 |
// |00| 1/16 | 00 |
// |01| 1/16 | 01 |
// |02| 1/16 | 02 |
// |03| 1/16 | 03 |
// |04| 1/16 | 04 |
// |05| 1/16 | 05 |
// |06| 1/16 | 06 |
// |07| 1/16 | 07 |
// |08| 1/16 | 08 |
// |09| 1/16 | 09 |
// |10| 1/16 | 10 |
// |11| 1/16 | 11 |
// |12| 1/16 | 12 |
// |13| 1/16 | 13 |
// |14| 1/16 | 14 |
// |15| 1/16 | 15 |

// But since save file size is a concern. What are the smallest possible ways to express the above data:
// How many bytes does one cell really need to occupy?

// 16-bit might me enough?
// HEX | 0                    | 0                  | 00
//     | 0 = CELL TYPE (0-F); | 0 = DIVISOR (0-F); | VALUE (00-FF)

// DIVISOR at the moment only needs to go to 11 but the added range can come in handy somehow.
// CELL TYPE can say if the value is a NOTE, FX, AUTOMATION, COMMAND
// THEN, we know which table to look at when reading the VALUE byte

// Ok, so the cells themselves can be quite small
// A pattern can be an Cell[] and reading the bytes would be enough to know how to interpret them.

// I'll leave this here for later when it's type to start thinking about optimization.
