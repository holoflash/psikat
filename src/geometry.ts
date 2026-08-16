import { SUBDIVISIONS_PLAIN } from "./data/subdivisions";

const one = 13440;
// @ts-ignore
// oxlint-disable
// playing around
const canvas = <HTMLCanvasElement>document.getElementById("geometry");
const ctx = canvas.getContext("2d")!;
canvas.height = one;
canvas.width = one;
canvas.style.width = "1000px";
canvas.style.height = "1000px";
ctx.fillStyle = "#000000";
ctx.fillRect(0, 0, one, one);
export function geometry() {
  ctx.lineWidth = 5;

  ctx.moveTo(one / 2, one / 2);
  ctx.beginPath();
  SUBDIVISIONS_PLAIN.forEach((s) => {
    for (let i = 0; i < s; i++) {
      ctx.arc(one / 2, one / 2, one / 2, i, 3.14 * 2 - (one / s + i));
      ctx.strokeStyle = "#fff";
    }
  });

  ctx.stroke();
}
// dunno what this is going to be yet.
// Gonna see if my subdivisions math can yield some cool geometrical patterns
// Just gotta wrap my head around this line moving first
