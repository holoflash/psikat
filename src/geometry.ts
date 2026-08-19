import { SUBDIVISIONS } from "./data/subdivisions";
import { s_current_zoom, ZOOM_LEVELS } from "./state";
import { get_css_var } from "./utils/dom/get_css_var";

const HALF_SIZE = 350;
const FULL_SIZE = 700;

function polar_to_cartesian(d: number, deg: number) {
  const rad = ((deg - 135) * Math.PI) / 180;
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

  // Clearing out the labels before re-rendering
  const prev = document.querySelectorAll(".chart-label");
  if (prev) {
    prev.forEach((el) => {
      el.remove();
    });
  }

  const zoom = ZOOM_LEVELS[s_current_zoom.value];
  const chunk = 360 / zoom;
  for (let i = 0; i < zoom + 1; i++) {
    const [x, y] = polar_to_cartesian(HALF_SIZE, chunk * i);
    const [z, p] = polar_to_cartesian(HALF_SIZE, chunk * (i - 1));

    ctx.lineTo(x, y);
    ctx.moveTo(HALF_SIZE, HALF_SIZE);
    ctx.lineTo(z, p);

    const label = document.createElement("p");
    label.textContent = `${i + 1}/${zoom}`;
    label.className = "chart-label";
    label.style.transform = `translate(${x}px, ${y}px)`;
    document.body.append(label);
  }
  ctx.stroke();
}

export function geometry_grid() {
  const prev = document.querySelectorAll(".cell");
  if (prev) {
    prev.forEach((el) => {
      el.remove();
    });
  }
  const chunk = SUBDIVISIONS[ZOOM_LEVELS[s_current_zoom.value]];
  const zoom = ZOOM_LEVELS[s_current_zoom.value];

  for (let i = 0; i < zoom; i++) {
    const cell = document.createElement("div");
    cell.className = "cell";
    cell.style.width = "100px";
    cell.style.textAlign = "center";
    cell.style.padding = `${chunk / 100}px`;
    cell.style.fontSize = `${Math.max(chunk / 1000, 14)}px`;

    cell.textContent = `${i + 1}/${zoom}`;
    document.getElementById("grid")?.append(cell);
  }
}
