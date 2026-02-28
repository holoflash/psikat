use std::num::NonZero;
use std::time::Duration;

use rodio::Source;

use crate::project::{Envelope, Waveform};

impl Waveform {
    pub(crate) fn sample(self, phase: f32) -> f32 {
        match self {
            Self::Sine => (std::f32::consts::TAU * phase).sin(),
            Self::Triangle => 4.0f32.mul_add((phase - (phase + 0.5).floor()).abs(), -1.0),
            Self::Square => {
                if phase < 0.5 {
                    1.0
                } else {
                    -1.0
                }
            }
            Self::Saw => 2.0f32.mul_add(phase, -1.0),
            Self::Noise => fastrand::f32().mul_add(2.0, -1.0),
        }
    }
}

impl Envelope {
    pub(crate) fn amplitude(&self, time: f32, note_duration: f32) -> f32 {
        let release_start = note_duration - self.release;

        if time < self.attack {
            time / self.attack
        } else if time < self.attack + self.decay {
            let decay_progress = (time - self.attack) / self.decay;
            (1.0 - self.sustain).mul_add(-decay_progress, 1.0)
        } else if time < release_start {
            self.sustain
        } else if time < note_duration {
            let release_progress = (time - release_start) / self.release;
            self.sustain * (1.0 - release_progress)
        } else {
            0.0
        }
    }
}

pub struct SynthSource {
    waveform: Waveform,
    frequency: f32,
    envelope: Envelope,
    sample_rate: f32,
    sample_rate_u32: u32,
    phase: f32,
    elapsed_samples: u32,
    total_samples: u32,
    note_duration: f32,
    amplitude: f32,
    noise_held: f32,
}

impl SynthSource {
    pub fn new(
        waveform: Waveform,
        frequency: f32,
        duration: Duration,
        amplitude: f32,
        envelope: Envelope,
    ) -> Self {
        let sample_rate_u32: u32 = 44100;
        let sample_rate = 44100.0_f32;
        let note_duration = duration.as_secs_f32();
        #[allow(clippy::cast_possible_truncation, clippy::cast_sign_loss)]
        let total_samples = (note_duration * sample_rate).round() as u32;
        Self {
            waveform,
            frequency,
            envelope,
            sample_rate,
            sample_rate_u32,
            phase: 0.0,
            elapsed_samples: 0,
            total_samples,
            note_duration,
            amplitude,
            noise_held: fastrand::f32().mul_add(2.0, -1.0),
        }
    }
}

impl Iterator for SynthSource {
    type Item = f32;

    fn next(&mut self) -> Option<f32> {
        if self.elapsed_samples >= self.total_samples {
            return None;
        }

        #[allow(clippy::cast_precision_loss, clippy::cast_possible_truncation)]
        let time = f64::from(self.elapsed_samples) as f32 / self.sample_rate;
        let env_amp = self.envelope.amplitude(time, self.note_duration);
        let sample = if self.waveform == Waveform::Noise {
            self.noise_held
        } else {
            self.waveform.sample(self.phase)
        };

        self.phase += self.frequency / self.sample_rate;
        if self.phase >= 1.0 {
            self.phase -= 1.0;
            if self.waveform == Waveform::Noise {
                self.noise_held = fastrand::f32().mul_add(2.0, -1.0);
            }
        }

        self.elapsed_samples += 1;
        Some(sample * env_amp * self.amplitude)
    }
}

impl Source for SynthSource {
    fn current_span_len(&self) -> Option<usize> {
        Some((self.total_samples - self.elapsed_samples) as usize)
    }

    fn channels(&self) -> NonZero<u16> {
        NonZero::new(1).unwrap()
    }

    fn sample_rate(&self) -> NonZero<u32> {
        NonZero::new(self.sample_rate_u32).unwrap()
    }

    fn total_duration(&self) -> Option<Duration> {
        Some(Duration::from_secs_f32(self.note_duration))
    }
}
