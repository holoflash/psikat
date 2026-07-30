import { AppState } from "../../state";

const dialog = document.createElement("dialog");
export function command_palette() {
  dialog.id = "command-palette";
  dialog.closedBy = "any";
  dialog.addEventListener("close", () => {
    AppState.command_palette_open.value = false;
  });

  const content = document.createElement("p");
  content.textContent = "Hello piskat command palette";

  dialog.appendChild(content);
  document.body.append(dialog);
}

AppState.command_palette_open.effect(() => {
  if (AppState.command_palette_open.value) {
    dialog.showModal();
  } else {
    dialog.close();
  }
});
