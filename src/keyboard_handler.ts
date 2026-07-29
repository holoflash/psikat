export function attachKeyListener() {
  document.addEventListener("keyup", (event) => {
    console.log(event.code);
  });
}
