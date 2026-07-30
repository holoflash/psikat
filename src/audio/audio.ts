const audio_context = new AudioContext({ latencyHint: 0, sampleRate: 48000 });
export function play_note(note: number) {
  const osc = new OscillatorNode(audio_context, {
    type: "square",
    frequency: note,
  });
  osc.connect(audio_context.destination);
  osc.start(audio_context.currentTime);
  osc.stop(audio_context.currentTime + 0.1);
}
