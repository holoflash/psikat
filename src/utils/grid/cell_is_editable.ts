/**
 * Determines if a cell can be edited in the current zoom level
 */
export function cell_is_editable(curr_zoom: number, new_zoom: number, _curr_pos?: number): boolean {
  if (curr_zoom === new_zoom) {
    return true;
  }
  const is_curr_even = curr_zoom % 2 === 0;
  const is_new_even = new_zoom % 2 === 0;

  if (is_curr_even && is_new_even && new_zoom > curr_zoom) {
    return true;
  }
  if (!is_curr_even && !is_new_even && new_zoom > curr_zoom) {
    return true;
  }
  // There is going to be a lot more to this and the cell position must also be taken into account
  return false;
}
