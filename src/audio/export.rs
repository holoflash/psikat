use std::path::Path;

use hound::{SampleFormat, WavSpec, WavWriter};

use super::mixer::{self, SAMPLE_RATE};

pub fn export_wav(
    patterns: &[crate::project::Pattern],
    order: &[usize],
    bpm: u16,
    path: &Path,
    instruments: &[crate::project::Instrument],
    master_volume: f32,
) -> Result<(), Box<dyn std::error::Error>> {
    let (mut source, total_samples) =
        mixer::export_source(patterns, order, bpm, instruments, master_volume);

    let spec = WavSpec {
        channels: 1,
        sample_rate: SAMPLE_RATE,
        bits_per_sample: 16,
        sample_format: SampleFormat::Int,
    };

    let mut writer = WavWriter::create(path, spec)?;

    for _ in 0..total_samples {
        if let Some(sample) = source.next() {
            let clamped = sample.clamp(-1.0, 1.0);
            let value = (clamped * f32::from(i16::MAX)).round() as i16;
            writer.write_sample(value)?;
        } else {
            writer.write_sample(0i16)?;
        }
    }

    writer.finalize()?;
    Ok(())
}
