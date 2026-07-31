// What is the grid? really?
// Break it down!...

type Divisor = 4 | 6 | 8 | 12 | 16 | 24 | 32 | 48 | 64 | 96 | 128;
type Cell = {
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
              { divisor: 16, value: 0xaa },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
              { divisor: 16, value: 0xbb },
            ],
          },
        ],
      },
    ],
  },
];

void MOCK_ARRANGEMENT;

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
