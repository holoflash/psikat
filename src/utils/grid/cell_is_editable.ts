function is_even(value: number) {
  return value % 2 === 0;
}

// OK gonna try to work this out...
// Here's a very basic pattern.

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

/**
 * Determines if a cell can be edited in the current zoom level
 */
export function cell_is_editable(curr_zoom: number, new_zoom: number, _curr_pos?: number): boolean {
  if (curr_zoom === new_zoom) {
    return true;
  }
  const both_even = is_even(curr_zoom) && is_even(new_zoom);

  if (both_even && new_zoom > curr_zoom) {
    return true;
  }
  if (!both_even && new_zoom > curr_zoom) {
    return true;
  }
  // There is going to be a lot more to this and the cell position must also be taken into account
  // Also, neighboring cells will also affect the result so this function should take a full pattern
  // - then assign an "editable" flag to each cell in a pattern
  return false;
}
