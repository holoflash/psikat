// OK gonna try to work this out...
// Here's a very basic pattern.

import type { Pattern } from "../../state/model";

// ZOOM = 4
//   { value: 1, zoom: 4 },
//   { value: 1, zoom: 4 },
//   { value: 1, zoom: 4 },
//   { value: 1, zoom: 4 },

// Patterns in the pattern pool could be transformed in memory when changing resolution
// Here we multiply each cell by the zoom factor and add missing cells
// ZOOM = 8
//   { value: 1, zoom: 4 },
//   { value: 0, zoom: 8 },
//   { value: 1, zoom: 4 },
//   { value: 0, zoom: 8 },
//   { value: 1, zoom: 4 },
//   { value: 0, zoom: 8 },
// Benefits: if you never go to a higher res, you preserve data size

// Ok, and then we can resolve back to a lower res by deleting all 0 values.

// Ok but how can I determine if a cell is editable. Let's try.
// ZOOM = 8
//   { value: 1, zoom: 8 },
//   { value: 0, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },

// When moving to ZOOM=4
//   { value: 1, zoom: 8 }, // I know intuitively that it's safe to insert a 1/4 note in this slot
//   { value: 0, zoom: 8 }, // because this one is empty.
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 }, // And all the remaining ones can't be edited in 1/4 resolution
//   { value: 1, zoom: 8 }, // now... how do I work out an algorithm for this ?
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },

// So based on the above. I can simplify the pattern after the move
//   { value: 1, zoom: 4 }, // merge the empty slot into one 1/4 slot
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },
//   { value: 1, zoom: 8 },

// Even-to-even moves should be straightforward to figure out.
// What about Even-to-odd and odd-to-even...
// ZOOM = 12
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },

// ZOOM = 6
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 1, zoom: 12 },

// ZOOM = 12
//   { value: 1, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },

// ZOOM = 6                    No problem. This resolves cleanly
//   { value: 1, zoom: 6 },
//   { value: 0, zoom: 6 },
//   { value: 0, zoom: 6 },
//   { value: 1, zoom: 6 },
//   { value: 0, zoom: 6 },
//   { value: 0, zoom: 6 },

// ZOOM = 12
//   { value: 1, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },

// ZOOM = 6          Since the above can't be neatly placed in ZOOM=6, we keep those values at ZOOM=12
//   { value: 1, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 1, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 0, zoom: 12 },
//   { value: 1, zoom: 6 },
//   { value: 0, zoom: 6 },
//   { value: 0, zoom: 6 },

// Visual representation:
// ZOOM = 6
// 12  These three 12 cells can't be edited in this resolution
// 12
// 12
// C4
// C4
// C4

// Ok, all good. Now I need to write a function that figures all of the above out ^
// Things are going to get hectic when we end up with a pattern that has a big variety of zoom levels within.
// Next time I'll try to construct such a pattern along with what it should look like when moving to a certain zoom level
// That will serve as input and output for a test and we can take it from there

//   Pattern.foreach(cell-i =>
//  Zoomfactor = newZoom/ cell.zoom
//  For(zoomFactor)
//    All zf values exlc first are null
//    Add 1 cell at desired zoom
//    With value of first checked cell
// Else
//   Cell-i += zoomFactor
//   Go to next unchecked cell
export function transform_pattern(pattern: Pattern, new_zoom: number): Pattern {
  let new_pattern: Pattern = [];
  for (let i = 0; i < pattern.length; i++) {
    const cells_to_check = pattern[i].zoom / new_zoom;
    // process the pattern in batches
    const can_add = can_compress(pattern.slice(i, cells_to_check + i));
    if (can_add) {
      new_pattern.push({ value: pattern[i].value, zoom: new_zoom });
      i += cells_to_check - 1;
    } else {
      new_pattern.push(pattern[i]);
    }
  }
  return new_pattern;
}
// This feels like a LeetCode challenge. If I only had spent more time there
// But hey, made the one test pass :D
function can_compress(cells_to_check: Pattern) {
  let ok = true;
  for (let i = 1; i < cells_to_check.length; i++) {
    if (cells_to_check[i].value === 0) {
      ok = true;
    } else {
      ok = false;
    }
  }
  return ok;
}
