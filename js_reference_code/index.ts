// // Listeners go here
document.addEventListener("keydown", keyboard_event_to_command);

import { init_audio } from "./audio/audio";
import { keyboard_event_to_command } from "./commands/keyboard_event_to_command";
import { command_palette } from "./components/command_palette/dialog";
import { reactive_ui } from "./components/reactive_ui";
import { dom_element } from "./utils/dom/dom_element";

document.getElementById("worklet-init")?.addEventListener("click", () => {
  void init_audio();
});

reactive_ui();
command_palette();

// I find myself refactoring too early, so I'll just inline a bunch of stuff in here for now
const SUBDIVISIONS = {
  4: 3360,
  5: 2688,
  6: 2240,
  7: 1920,
  8: 1680,
  10: 1344,
  12: 1120,
  14: 960,
  16: 840,
  20: 672,
  24: 560,
  28: 480,
  32: 420,
  40: 336,
  48: 280,
  56: 240,
  64: 210,
  80: 168,
  96: 140,
  112: 120,
  128: 105,
} as const;

const CELL = { value: 0xff, pitch: 0x40, velocity: 0x7f };

const DEFAULT_PATTERN = Array.from({ length: 16 * SUBDIVISIONS[16] }, () => {
  return CELL;
});

const pattern_container = dom_element("div", { className: "pattern-container" });

DEFAULT_PATTERN.forEach((cell, index) => {
  if (index % SUBDIVISIONS[16] !== 0) return;
  const row = dom_element("div", { className: "pattern-row" });
  row.append(
    dom_element("div", { className: "pattern-value", textContent: cell.value.toString() }),
  );
  row.append(
    dom_element("div", { className: "pattern-pitch", textContent: cell.pitch.toString() }),
  );
  row.append(
    dom_element("div", { className: "pattern-velocity", textContent: cell.velocity.toString() }),
  );
  pattern_container.append(row);
});

const arrangement = document.getElementById("arrangement")!;
arrangement.append(pattern_container);
