import { s_current_zoom, ZOOM_LEVELS } from "./state";
import { get_css_var } from "./utils/dom/get_css_var";

const HALF_SIZE = 350;
const FULL_SIZE = 700;

export function geometry() {
  const canvas = document.getElementById("geometry") as HTMLCanvasElement;
  if (!canvas) return;
  const ctx = canvas.getContext("2d")!;
  canvas.height = FULL_SIZE;
  canvas.width = FULL_SIZE;
  canvas.style.width = "700px";
  canvas.style.height = "700px";

  const zoom = ZOOM_LEVELS[s_current_zoom.value];

  ctx.strokeStyle = get_css_var("--ACCENT");
  const chunk = (360 * Math.PI) / 180.0 / zoom;

  // Clearing out the labels before re-rendering
  const prev = document.querySelectorAll("#chart-label");
  if (prev) {
    prev.forEach((el) => {
      el.remove();
    });
  }

  for (let i = 1; i < zoom + 1; i++) {
    const [x, y] = polar_to_cartesian(chunk * i);
    const [z, p] = polar_to_cartesian(chunk * (i - 1));
    ctx.moveTo(HALF_SIZE, HALF_SIZE);
    ctx.lineTo(z, p);
    ctx.lineTo(x, y);

    const label = document.createElement("p");
    label.textContent = `${i}`;
    label.id = "chart-label";
    label.style.transform = `translate(${x}px, ${y}px)`;
    document.body.append(label);
  }
  ctx.stroke();
}

function polar_to_cartesian(rad: number) {
  return [HALF_SIZE + HALF_SIZE * Math.cos(rad), HALF_SIZE + HALF_SIZE * Math.sin(rad)];
}
