class SquareWave extends AudioWorkletProcessor {
  static get parameterDescriptors() {
    return [
      {
        name: "frequency",
        default: 440,
        min: 20,
        max: 20000,
      },
    ];
  }
  private phase = 0;

  process(
    _inputs: Float32Array[][],
    outputs: Float32Array[][],
    parameters: Record<string, Float32Array>,
  ): boolean {
    const output = outputs[0];
    if (!output || output.length === 0) return true;

    const left_channel = output[0];
    const right_channel = output[1] || left_channel[0];

    for (let i = 0; i < left_channel.length; i++) {
      const sample_value = this.phase < 0.5 ? 0.2 : -0.2;
      left_channel[i] = sample_value;
      if (output[1]) {
        right_channel[i] = sample_value;
      }
      const frequency = parameters.frequency[i] ?? parameters.frequency[0];

      this.phase += frequency / sampleRate;
      if (this.phase >= 1.0) {
        this.phase -= 1.0;
      }
    }

    return true;
  }
}

registerProcessor("square_wave", SquareWave);
