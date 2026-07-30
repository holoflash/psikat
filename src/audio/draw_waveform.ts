import { get_css_var } from "../utils/css_root_var";

const canvas = document.createElement("canvas");
const instrument_panel = document.getElementById("instrument-panel")!;
instrument_panel.append(canvas);

// MDN tips for canvas optimization
const dpr = window.devicePixelRatio;
const rect = canvas.getBoundingClientRect();
canvas.width = rect.width * dpr;
canvas.height = rect.height * dpr;

const canvas_context = canvas.getContext("2d", { alpha: false })!;
canvas_context.scale(dpr, dpr);
canvas_context.fillStyle = get_css_var("--TEXT");
canvas_context.fillRect(0, 0, canvas.width, canvas.height);

export function draw_waveform(node: AudioWorkletNode, context: AudioContext) {
  let analyzer: AnalyserNode | null = null;
  let bufferLength = 0;
  let dataArray: Uint8Array<ArrayBuffer>;

  analyzer = context.createAnalyser();
  node.connect(analyzer);

  analyzer.fftSize = 2048;
  bufferLength = analyzer.frequencyBinCount;
  dataArray = new Uint8Array(bufferLength);
  analyzer.getByteTimeDomainData(dataArray);
  function draw() {
    canvas_context.fillRect(0, 0, canvas.width, canvas.height);
    canvas_context.lineWidth = 1;
    canvas_context.strokeStyle = get_css_var("--BG_1");
    canvas_context.beginPath();
    if (!canvas_context) return;

    const sliceWidth = (canvas.width * 1.0) / bufferLength;
    let x = 0;

    analyzer!.getByteTimeDomainData(dataArray);
    for (let i = 0; i < bufferLength; i++) {
      const v = dataArray[i] / 128.0;
      // Centered waveform.
      const y = (v * canvas.height) / 4;
      if (i === 0) {
        canvas_context.moveTo(x, y);
      } else {
        canvas_context.lineTo(x, y);
      }

      x += sliceWidth;
    }

    canvas_context.lineTo(canvas.width, canvas.height / 2);
    canvas_context.stroke();
    requestAnimationFrame(draw);
  }
  draw();
}
