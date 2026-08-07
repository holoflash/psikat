// Every pattern cell has a zoom value attached to it
// This function should check the index of the cell's position in in the pattern
// And see if based om the position and zoom value, it can be cleanly resolved
// When changing the grid to a new size

// For now, all patterns will be of a fixed length, so that is not a concern.

// all this does for now is return the new position
export function get_cell_multiplier(
  current_zoom_level: number,
  next_zoom_level: number,
  position_in_pattern: number,
) {
  // 4 6 8 12 16 24 32 48 64 96 128
  const new_position = (position_in_pattern / current_zoom_level) * next_zoom_level;

  if (current_zoom_level === next_zoom_level) {
    return position_in_pattern;
  } else {
    return new_position;
  }
}
