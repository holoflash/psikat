// TODO: Expand Zoom type to include all subdivisions from the psikat_maths doc
export function next_zoom(current: number) {
  return current + current / (current / 2 ** (Math.floor(Math.log2(current)) - 2));
}

// TODO: This doesn't actually work across boundaries!
export function previous_zoom(current: number) {
  return current - current / (current / 2 ** (Math.floor(Math.log2(current)) - 2));
}
