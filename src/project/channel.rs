use std::sync::Arc;

use serde::{Deserialize, Serialize};

use super::sample::SampleData;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub enum WaveformKind {
    Sample,
    Sine,
    Triangle,
    Square,
    Saw,
    Noise,
}

impl WaveformKind {
    pub fn label(self) -> &'static str {
        match self {
            Self::Sample => "Sample",
            Self::Sine => "Sine",
            Self::Triangle => "Triangle",
            Self::Square => "Square",
            Self::Saw => "Saw",
            Self::Noise => "Noise",
        }
    }

    pub fn generate(self) -> Arc<SampleData> {
        match self {
            Self::Sample => SampleData::silent(),
            Self::Sine => SampleData::sine(),
            Self::Triangle => SampleData::triangle(),
            Self::Square => SampleData::square(),
            Self::Saw => SampleData::saw(),
            Self::Noise => SampleData::noise(),
        }
    }

    pub const ALL: &'static [Self] = &[
        Self::Sample,
        Self::Sine,
        Self::Triangle,
        Self::Square,
        Self::Saw,
        Self::Noise,
    ];
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Track {
    pub name: String,
    pub waveform: WaveformKind,
    pub sample_data: Arc<SampleData>,
    pub default_volume: f32,
    pub samples: Vec<(Arc<SampleData>, f32)>,
    pub note_to_sample: Vec<u8>,
    pub default_panning: f32,
    pub coarse_tune: i8,
    pub fine_tune: i8,
    pub polyphony: u8,
}

impl Track {
    pub fn sample_for_note(&self, pitch: u8) -> (&Arc<SampleData>, f32) {
        if !self.note_to_sample.is_empty() && !self.samples.is_empty() {
            let map_idx = (pitch as usize).min(self.note_to_sample.len() - 1);
            let sample_idx = self.note_to_sample[map_idx] as usize;
            if sample_idx < self.samples.len() {
                let (ref sd, vol) = self.samples[sample_idx];
                return (sd, vol);
            }
        }
        (&self.sample_data, self.default_volume)
    }

    pub fn defaults() -> Vec<Self> {
        vec![Self::new_empty("Track 00")]
    }

    pub fn new_empty(name: &str) -> Self {
        Self {
            name: name.into(),
            waveform: WaveformKind::Square,
            sample_data: SampleData::square(),
            default_volume: 1.0,
            samples: Vec::new(),
            note_to_sample: Vec::new(),
            default_panning: 0.5,
            coarse_tune: 0,
            fine_tune: 0,
            polyphony: 1,
        }
    }
}
