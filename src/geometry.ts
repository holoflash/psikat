import { s_current_zoom, ZOOM_LEVELS } from "./state";
import { get_css_var } from "./utils/dom/get_css_var";

const HALF_SIZE = 350;
const FULL_SIZE = 700;

function polar_to_cartesian(d: number, deg: number) {
  const rad = ((deg - 90) * Math.PI) / 180;
  return [d + d * Math.cos(rad), d + d * Math.sin(rad)];
}

export function geometry_circular() {
  // @ts-ignore trust me bro
  const canvas: HTMLCanvasElement = document.getElementById("geometry");
  if (!canvas) return;

  const ctx = canvas.getContext("2d")!;
  canvas.height = FULL_SIZE;
  canvas.width = FULL_SIZE;
  canvas.style.width = "700px";
  canvas.style.height = "700px";
  ctx.strokeStyle = get_css_var("--TEXT");
  ctx.lineWidth = 1;

  // Clearing out the labels before re-rendering
  const prev = document.querySelectorAll(".chart-label");
  if (prev) {
    prev.forEach((el) => {
      el.remove();
    });
  }

  const zoom = ZOOM_LEVELS[s_current_zoom.value];
  for (let i = 0; i < zoom + 1; i++) {
    const chunk = 360 / zoom;
    const [x, y] = polar_to_cartesian(HALF_SIZE, chunk * i);

    // ctx.lineTo(x, y);
    // ctx.lineTo(z, p);
    if (i !== zoom) {
      const cell_container = document.createElement("div");
      const cell = document.createElement("div");
      const cell2 = document.createElement("div");
      const cell3 = document.createElement("div");

      cell_container.className = "cell-container";
      cell.className = "chart-label";
      cell2.className = "chart-label";
      cell2.textContent = "F4";
      cell3.className = "chart-label";
      cell3.textContent = "··";

      cell.style.padding = `${chunk / 100}px`;
      cell.style.fontSize = `${Math.max(chunk / 1000, 14)}px`;

      cell.textContent = `${i + 1}/${zoom}`;
      cell_container.append(cell, cell2, cell3);

      cell.textContent = (i + 1).toString(16).padStart(2, "0").toUpperCase();
      cell_container.style.transform = `translate(${x}px, ${y}px) rotate(${chunk * i}deg)`;
      document.body.append(cell_container);
    }
    ctx.stroke();
  }
}
