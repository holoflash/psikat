use std::sync::atomic::Ordering;

use super::App;

pub struct PlaybackState {
    pub playing: bool,
}

impl PlaybackState {
    pub const fn new() -> Self {
        Self { playing: false }
    }
}

impl App {
    pub fn start_playback(&mut self, from_cursor: bool) {
        let row = if from_cursor { self.cursor.row } else { 0 };
        self.playback.playing = true;
        self.audio.start_playback(
            row,
            &self.project.pattern,
            &self.project.channel_settings,
            self.project.bpm,
            self.project.master_volume_linear(),
        );
    }

    pub fn stop_playback(&mut self) {
        self.playback.playing = false;
        self.audio.stop_all();
    }

    pub fn tick(&mut self) {
        if !self.playback.playing {
            return;
        }
        let row = self.playback_row.load(Ordering::Relaxed);
        self.playback_row_display = row;

        self.audio.update_settings(
            &self.project.channel_settings,
            self.project.bpm,
            self.project.master_volume_linear(),
        );
        self.audio.update_pattern(&self.project.pattern);
    }
}
