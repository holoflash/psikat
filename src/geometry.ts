import { s_current_zoom, ZOOM_LEVELS } from "./state";

const polarToCartesian = (r: number, degrees: number) => {
  const radians = (degrees * Math.PI) / 180.0;
  return [r + r * Math.cos(radians), r + r * Math.sin(radians)];
};
const one_half = 350;
const one = 700;

export function geometry() {
  // @ts-ignore
  // oxlint-disable
  // playing around
  const canvas = <HTMLCanvasElement>document.getElementById("geometry");
  const ctx = canvas.getContext("2d")!;
  canvas.height = one;
  canvas.width = one;
  canvas.style.width = "700px";
  canvas.style.height = "700px";
  ctx.fillStyle = "rgb(0, 0, 0, 0)";

  ctx.fillRect(0, 0, one, one);
  ctx.beginPath();
  const zoom = ZOOM_LEVELS[s_current_zoom.value];

  ctx.lineWidth = 1;
  ctx.strokeStyle = "#fff";
  const chunk = 360 / zoom;
  const prev = document.querySelectorAll("#chart-label");
  if (prev) {
    prev.forEach((el) => {
      el.remove();
    });
  }

  for (let i = 1; i <= zoom + 1; i++) {
    const [x, y] = polarToCartesian(one_half, chunk * i);
    ctx.lineTo(x, y);

    if (i < zoom + 1) {
      const label = document.createElement("p");
      label.textContent = `${i}/${zoom}`;
      label.id = "chart-label";
      label.style.transform = `translate(${x}px, ${y}px)`;
      document.body.append(label);
    }
  }
  ctx.stroke();
}
