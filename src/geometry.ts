import { SUBDIVISIONS } from "./data/subdivisions";

const one_fourth = 3360;
// const one = 13440;
// @ts-ignore
// oxlint-disable
// playing around
const canvas = <HTMLCanvasElement>document.getElementById("geometry");
const ctx = canvas.getContext("2d")!;
canvas.height = one_fourth;
canvas.width = one_fourth;
canvas.style.width = "500px";
canvas.style.height = "500px";
ctx.fillStyle = "#FFF";
ctx.fillRect(0, 0, one_fourth, one_fourth);
export function geometry() {
  triplet();
}
// dunno what this is going to be yet.
// Gonna see if my subdivisions math can yield some cool geometrical patterns
// Just gotta wrap my head around this line moving first
function triplet() {
  ctx.lineWidth = 100;
  ctx.strokeStyle = "#9d2677";
  ctx.beginPath();
  ctx.moveTo(0, 0);
  ctx.lineTo(SUBDIVISIONS[6], 0);
  ctx.stroke();

  ctx.lineTo(one_fourth - SUBDIVISIONS[6], one_fourth - SUBDIVISIONS[6]);
  ctx.stroke();

  ctx.lineTo(one_fourth - SUBDIVISIONS[6] * 2, one_fourth - SUBDIVISIONS[6] * 2);
  ctx.stroke();
}
