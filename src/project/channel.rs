#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Waveform {
    Sine,
    Triangle,
    Square,
    Saw,
    Noise,
}

impl Waveform {
    pub const fn name(self) -> &'static str {
        match self {
            Self::Sine => "SIN",
            Self::Triangle => "TRI",
            Self::Square => "SQR",
            Self::Saw => "SAW",
            Self::Noise => "NOS",
        }
    }

    pub const fn next(self) -> Self {
        match self {
            Self::Sine => Self::Triangle,
            Self::Triangle => Self::Square,
            Self::Square => Self::Saw,
            Self::Saw => Self::Noise,
            Self::Noise => Self::Sine,
        }
    }

    pub const fn prev(self) -> Self {
        match self {
            Self::Sine => Self::Noise,
            Self::Triangle => Self::Sine,
            Self::Square => Self::Triangle,
            Self::Saw => Self::Square,
            Self::Noise => Self::Saw,
        }
    }

    pub const fn default_envelope(self) -> Envelope {
        match self {
            Self::Sine => Envelope {
                attack: 0.01,
                decay: 0.05,
                sustain: 0.9,
                release: 0.05,
            },
            Self::Triangle => Envelope {
                attack: 0.01,
                decay: 0.06,
                sustain: 0.9,
                release: 0.05,
            },
            Self::Square => Envelope {
                attack: 0.005,
                decay: 0.1,
                sustain: 0.8,
                release: 0.03,
            },
            Self::Saw => Envelope {
                attack: 0.005,
                decay: 0.08,
                sustain: 0.6,
                release: 0.04,
            },
            Self::Noise => Envelope {
                attack: 0.001,
                decay: 0.05,
                sustain: 0.3,
                release: 0.02,
            },
        }
    }
}

pub const DEFAULT_INSTRUMENTS: [Waveform; 8] = [
    Waveform::Square,
    Waveform::Square,
    Waveform::Saw,
    Waveform::Saw,
    Waveform::Triangle,
    Waveform::Sine,
    Waveform::Noise,
    Waveform::Noise,
];

#[derive(Debug, Clone, Copy)]
pub struct Envelope {
    pub attack: f32,
    pub decay: f32,
    pub sustain: f32,
    pub release: f32,
}

#[derive(Debug, Clone, Copy)]
pub struct ChannelSettings {
    pub waveform: Waveform,
    pub envelope: Envelope,
    pub volume: f32,
}

impl ChannelSettings {
    pub const fn default_for(waveform: Waveform) -> Self {
        Self {
            envelope: waveform.default_envelope(),
            waveform,
            volume: 0.8,
        }
    }

    pub fn defaults() -> Vec<Self> {
        DEFAULT_INSTRUMENTS
            .iter()
            .map(|w| Self::default_for(*w))
            .collect()
    }
}
