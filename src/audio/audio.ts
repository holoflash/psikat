import { AppState } from "../state";
import { draw_waveform } from "../ui/draw_waveform";

let audio_context: AudioContext | null = null;
let square_node: AudioWorkletNode | null = null;

export function play_note(freq: number) {
  AppState.pitch.value = freq;
  if (!square_node || !audio_context) return;
  const frequency: AudioParam | undefined = square_node.parameters.get("frequency");

  // Surely this isn't a good idea, but it's working!!!
  AppState.pitch.effect(() => {
    frequency!.setValueAtTime(AppState.pitch.value, audio_context!.currentTime);
  });

  square_node.connect(audio_context.destination);
}

export async function init_audio() {
  // Doesn't feel right but prevents multiple instances from being created
  await audio_context?.close();
  AppState.audio_initialized.value = true;

  audio_context = new AudioContext({ latencyHint: 0, sampleRate: 48000 });
  const worklet_url = new URL("./square_wave.ts", import.meta.url);
  await audio_context.audioWorklet.addModule(worklet_url);
  square_node = new AudioWorkletNode(audio_context, "square_wave");

  draw_waveform(square_node, audio_context);
}
