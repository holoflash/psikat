Not sure if I'll need this or not yet. Keeping for reference.
```ts
function next_zoom(current: ZoomLevel) {
  const z = 2 ** (Math.floor(Math.log2(current)) - 2);
  return current + z;
}

function previous_zoom(current: ZoomLevel) {
  const z = 2 ** (Math.floor(Math.log2(current - 1)) - 2);
  return current - z;
}
```