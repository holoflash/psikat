use std::sync::Arc;

use super::sample::SampleData;

#[derive(Debug, Clone, Copy)]
pub struct Envelope {
    pub attack: f32,
    pub decay: f32,
    pub sustain: f32,
    pub release: f32,
}

impl Envelope {
    pub fn amplitude(&self, time: f32, note_duration: f32) -> f32 {
        let release_start = note_duration - self.release;

        if self.attack > 0.0 && time < self.attack {
            time / self.attack
        } else if self.decay > 0.0 && time < self.attack + self.decay {
            let decay_progress = (time - self.attack) / self.decay;
            (1.0 - self.sustain).mul_add(-decay_progress, 1.0)
        } else if time < release_start {
            self.sustain
        } else if self.release > 0.0 && time < note_duration {
            let release_progress = (time - release_start) / self.release;
            self.sustain * (1.0 - release_progress)
        } else if time >= note_duration {
            0.0
        } else {
            self.sustain
        }
    }
}

const DEFAULT_ENVELOPE: Envelope = Envelope {
    attack: 0.005,
    decay: 0.08,
    sustain: 0.8,
    release: 0.05,
};

const NOISE_ENVELOPE: Envelope = Envelope {
    attack: 0.001,
    decay: 0.05,
    sustain: 0.3,
    release: 0.02,
};

#[derive(Debug, Clone)]
pub struct XmVolEnvelope {
    pub points: Vec<(u16, u16)>,
    pub sustain_point: Option<usize>,
    pub loop_range: Option<(usize, usize)>,
    pub enabled: bool,
}

impl XmVolEnvelope {
    pub fn amplitude_at_tick(&self, tick: u16) -> f32 {
        if !self.enabled || self.points.is_empty() {
            return 1.0;
        }

        let points = &self.points;

        if tick <= points[0].0 {
            return points[0].1 as f32 / 64.0;
        }

        if tick >= points[points.len() - 1].0 {
            return points[points.len() - 1].1 as f32 / 64.0;
        }

        for i in 0..points.len() - 1 {
            let (t0, v0) = points[i];
            let (t1, v1) = points[i + 1];
            if tick >= t0 && tick < t1 {
                if t1 == t0 {
                    return v0 as f32 / 64.0;
                }
                let frac = (tick - t0) as f32 / (t1 - t0) as f32;
                let vol = v0 as f32 + (v1 as f32 - v0 as f32) * frac;
                return vol / 64.0;
            }
        }

        points[points.len() - 1].1 as f32 / 64.0
    }

    pub fn advance_tick(&self, current_tick: u16, note_released: bool) -> u16 {
        if !note_released
            && let Some(sus_idx) = self.sustain_point
                && sus_idx < self.points.len() && current_tick >= self.points[sus_idx].0 {
                    return self.points[sus_idx].0;
                }

        let next = current_tick + 1;

        if let Some((loop_start, loop_end)) = self.loop_range
            && loop_start < self.points.len() && loop_end < self.points.len() {
                let loop_end_tick = self.points[loop_end].0;
                if next >= loop_end_tick {
                    return self.points[loop_start].0;
                }
            }

        next
    }
}

#[derive(Debug, Clone)]
pub struct Instrument {
    pub name: String,
    pub envelope: Envelope,
    pub sample_data: Arc<SampleData>,
    pub default_volume: f32,
    pub samples: Vec<(Arc<SampleData>, f32)>,
    pub note_to_sample: Vec<u8>,
    pub xm_vol_envelope: Option<XmVolEnvelope>,
}

impl Instrument {
    pub fn sample_for_note(&self, pitch: u8) -> (&Arc<SampleData>, f32) {
        if !self.note_to_sample.is_empty() && !self.samples.is_empty() {
            let xm_note = pitch.saturating_sub(12) as usize;
            let map_idx = xm_note.min(self.note_to_sample.len() - 1);
            let sample_idx = self.note_to_sample[map_idx] as usize;
            if sample_idx < self.samples.len() {
                let (ref sd, vol) = self.samples[sample_idx];
                return (sd, vol);
            }
        }
        (&self.sample_data, self.default_volume)
    }

    pub fn defaults() -> Vec<Self> {
        vec![
            Self {
                name: "Square".into(),
                envelope: DEFAULT_ENVELOPE,
                sample_data: SampleData::square(),
                default_volume: 1.0,
                samples: Vec::new(),
                note_to_sample: Vec::new(),
                xm_vol_envelope: None,
            },
            Self {
                name: "Saw".into(),
                envelope: DEFAULT_ENVELOPE,
                sample_data: SampleData::saw(),
                default_volume: 1.0,
                samples: Vec::new(),
                note_to_sample: Vec::new(),
                xm_vol_envelope: None,
            },
            Self {
                name: "Triangle".into(),
                envelope: DEFAULT_ENVELOPE,
                sample_data: SampleData::triangle(),
                default_volume: 1.0,
                samples: Vec::new(),
                note_to_sample: Vec::new(),
                xm_vol_envelope: None,
            },
            Self {
                name: "Sine".into(),
                envelope: Envelope {
                    attack: 0.01,
                    decay: 0.05,
                    sustain: 0.9,
                    release: 0.05,
                },
                sample_data: SampleData::sine(),
                default_volume: 1.0,
                samples: Vec::new(),
                note_to_sample: Vec::new(),
                xm_vol_envelope: None,
            },
            Self {
                name: "Noise".into(),
                envelope: NOISE_ENVELOPE,
                sample_data: SampleData::noise(),
                default_volume: 1.0,
                samples: Vec::new(),
                note_to_sample: Vec::new(),
                xm_vol_envelope: None,
            },
            Self {
                name: "Empty 1".into(),
                envelope: DEFAULT_ENVELOPE,
                sample_data: SampleData::silent(),
                default_volume: 1.0,
                samples: Vec::new(),
                note_to_sample: Vec::new(),
                xm_vol_envelope: None,
            },
            Self {
                name: "Empty 2".into(),
                envelope: DEFAULT_ENVELOPE,
                sample_data: SampleData::silent(),
                default_volume: 1.0,
                samples: Vec::new(),
                note_to_sample: Vec::new(),
                xm_vol_envelope: None,
            },
            Self {
                name: "Empty 3".into(),
                envelope: DEFAULT_ENVELOPE,
                sample_data: SampleData::silent(),
                default_volume: 1.0,
                samples: Vec::new(),
                note_to_sample: Vec::new(),
                xm_vol_envelope: None,
            },
        ]
    }
}
