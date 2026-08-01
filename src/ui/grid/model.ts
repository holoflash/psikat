// What is the grid? really?
// Break it down!...

// type Divisor = 4 | 6 | 8 | 12 | 16 | 24 | 32 | 48 | 64 | 96 | 128;
// type Cell = {
//   type: "NOTE" | "COMMAND" | "FX" | "AUTOMATION";
//   divisor: Divisor; // we need to know at what division the cell got its value assigned
//   value: number;
// };
console.log("shhhhhh");

// Since save file size is a concern. What are the smallest possible ways to express the above data:
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
