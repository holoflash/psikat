function is_even(value: number) {
  return value % 2 === 0;
}

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
