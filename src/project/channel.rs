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

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize, Default)]
#[allow(clippy::enum_variant_names)]
pub enum FilterType {
    #[default]
    LowPass,
    HighPass,
    BandPass,
}

impl FilterType {
    pub fn label(self) -> &'static str {
        match self {
            Self::LowPass => "LP",
            Self::HighPass => "HP",
            Self::BandPass => "BP",
        }
    }
    pub const ALL: &'static [Self] = &[Self::LowPass, Self::HighPass, Self::BandPass];
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AdsrEnvelope {
    pub enabled: bool,
    pub attack_ms: f32,
    pub decay_ms: f32,
    pub sustain: f32,
    pub release_ms: f32,
}

impl AdsrEnvelope {
    pub fn disabled() -> Self {
        Self {
            enabled: false,
            attack_ms: 0.0,
            decay_ms: 0.0,
            sustain: 1.0,
            release_ms: 0.0,
        }
    }

    pub fn default_preset() -> Self {
        Self {
            enabled: false,
            attack_ms: 10.0,
            decay_ms: 100.0,
            sustain: 0.8,
            release_ms: 200.0,
        }
    }

    pub fn amplitude(&self, elapsed_samples: f64, released_samples: Option<f64>, sample_rate: f64) -> f32 {
        if !self.enabled {
            return 1.0;
        }

        let attack_s = self.attack_ms as f64 / 1000.0;
        let decay_s = self.decay_ms as f64 / 1000.0;
        let sustain = self.sustain as f64;
        let release_s = self.release_ms as f64 / 1000.0;

        let attack_samples = attack_s * sample_rate;
        let decay_samples = decay_s * sample_rate;

        let env_level = if elapsed_samples < attack_samples {
            if attack_samples > 0.0 {
                elapsed_samples / attack_samples
            } else {
                1.0
            }
        } else {
            let after_attack = elapsed_samples - attack_samples;
            if after_attack < decay_samples {
                if decay_samples > 0.0 {
                    1.0 - (1.0 - sustain) * (after_attack / decay_samples)
                } else {
                    sustain
                }
            } else {
                sustain
            }
        };

        if let Some(rel_samples) = released_samples {
            let release_total = release_s * sample_rate;
            if release_total > 0.0 {
                let release_factor = (1.0 - rel_samples / release_total).max(0.0);
                (env_level * release_factor) as f32
            } else {
                0.0
            }
        } else {
            env_level as f32
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct FilterSettings {
    pub enabled: bool,
    pub filter_type: FilterType,
    pub cutoff: f32,
    pub resonance: f32,
    pub env_depth: f32,
    pub envelope: AdsrEnvelope,
}

impl Default for FilterSettings {
    fn default() -> Self {
        Self {
            enabled: false,
            filter_type: FilterType::LowPass,
            cutoff: 20000.0,
            resonance: 0.0,
            env_depth: 0.0,
            envelope: AdsrEnvelope::disabled(),
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Track {
    pub name: String,
    pub waveform: WaveformKind,
    pub vol_envelope: AdsrEnvelope,
    pub sample_data: Arc<SampleData>,
    pub default_volume: f32,
    pub samples: Vec<(Arc<SampleData>, f32)>,
    pub note_to_sample: Vec<u8>,
    pub default_panning: f32,
    pub coarse_tune: i8,
    pub fine_tune: i8,
    pub pitch_env_enabled: bool,
    pub pitch_env_depth: f32,
    pub pitch_envelope: AdsrEnvelope,
    pub filter: FilterSettings,
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
            vol_envelope: AdsrEnvelope::default_preset(),
            sample_data: SampleData::square(),
            default_volume: 1.0,
            samples: Vec::new(),
            note_to_sample: Vec::new(),
            default_panning: 0.5,
            coarse_tune: 0,
            fine_tune: 0,
            pitch_env_enabled: false,
            pitch_env_depth: 12.0,
            pitch_envelope: AdsrEnvelope::disabled(),
            filter: FilterSettings::default(),
            polyphony: 1,
        }
    }
}
