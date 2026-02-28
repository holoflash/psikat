use std::time::{Duration, Instant};

use super::App;

pub struct PlaybackState {
    pub playing: bool,
    pub row: usize,
    pub last_step_time: Option<Instant>,
}

impl PlaybackState {
    pub const fn new() -> Self {
        Self {
            playing: false,
            row: 0,
            last_step_time: None,
        }
    }
}

impl App {
    pub fn step_duration(&self) -> Duration {
        let seconds = 60.0 / f64::from(self.project.bpm) / 4.0;
        Duration::from_secs_f64(seconds)
    }

    pub fn start_playback(&mut self, from_cursor: bool) {
        self.playback.playing = true;
        self.playback.row = if from_cursor { self.cursor.row } else { 0 };
        self.playback.last_step_time = Some(Instant::now());
        self.audio.play_row(
            &self.project.pattern,
            self.playback.row,
            self.step_duration(),
            &self.project.channel_settings,
            self.project.master_volume_linear(),
        );
    }

    pub fn stop_playback(&mut self) {
        self.playback.playing = false;
        self.playback.last_step_time = None;
        self.audio.stop_all();
    }

    pub fn tick(&mut self) {
        if !self.playback.playing {
            return;
        }

        if let Some(last) = self.playback.last_step_time
            && last.elapsed() >= self.step_duration()
        {
            self.playback.row = (self.playback.row + 1) % self.project.pattern.rows;
            self.audio.play_row(
                &self.project.pattern,
                self.playback.row,
                self.step_duration(),
                &self.project.channel_settings,
                self.project.master_volume_linear(),
            );
            self.playback.last_step_time = Some(Instant::now());
        }
    }
}
