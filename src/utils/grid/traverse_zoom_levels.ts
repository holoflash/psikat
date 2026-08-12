// TODO: Expand Zoom type to include all subdivisions from the psikat_maths doc
export function next_zoom(current: number) {
  const z = 2 ** (Math.floor(Math.log2(current)) - 2);
  return current + z;
}

export function previous_zoom(current: number) {
  const z = 2 ** (Math.floor(Math.log2(current - 1)) - 2);
  return current - z;
}
