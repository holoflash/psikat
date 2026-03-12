use eframe::egui::{self, FontId, Pos2, RichText, Stroke, Vec2};

use crate::app::App;
use crate::audio::mixer::SCOPE_SIZE;

use super::{
    COLOR_ACCENT, COLOR_LAYOUT_BG_DARK, COLOR_LAYOUT_BG_PANEL, COLOR_PATTERN_PLAYBACK_TEXT,
    COLOR_TEXT, COLOR_TEXT_ACTIVE, COLOR_TEXT_DIM,
};

const STRIP_WIDTH: f32 = 64.0;
const MIXER_HEIGHT: f32 = 240.0;
const SCOPE_HEIGHT: f32 = 36.0;
const FADER_HEIGHT: f32 = 80.0;

const MUTED_COLOR: egui::Color32 = egui::Color32::from_rgb(180, 80, 70);

pub fn draw_mixer(ctx: &egui::Context, app: &mut App) {
    if !app.show_mixer {
        return;
    }
    let channels = app.project.current_pattern().channels;

    egui::TopBottomPanel::bottom("mixer")
        .resizable(false)
        .exact_height(MIXER_HEIGHT)
        .frame(
            egui::Frame::new()
                .fill(COLOR_LAYOUT_BG_PANEL)
                .inner_margin(egui::Margin::symmetric(4, 6))
                .stroke(Stroke::new(1.0, COLOR_LAYOUT_BG_DARK)),
        )
        .show(ctx, |ui| {
            ui.spacing_mut().item_spacing = egui::vec2(2.0, 2.0);

            egui::ScrollArea::horizontal()
                .id_salt("mixer_scroll")
                .auto_shrink([false; 2])
                .show(ui, |ui| {
                    ui.horizontal(|ui| {
                        for ch in 0..channels {
                            draw_channel_strip(ui, app, ch, channels);
                        }
                    });
                });
        });
}

fn draw_channel_strip(ui: &mut egui::Ui, app: &mut App, ch: usize, total_channels: usize) {
    let is_muted = app.muted_channels.get(ch).copied().unwrap_or(false);
    let is_current = ch == app.current_track;

    let border_color = if is_current {
        COLOR_ACCENT
    } else {
        COLOR_LAYOUT_BG_DARK
    };

    let strip = egui::Frame::new()
        .fill(COLOR_LAYOUT_BG_DARK)
        .inner_margin(egui::Margin::symmetric(4, 4))
        .stroke(Stroke::new(1.0, border_color))
        .show(ui, |ui| {
            ui.set_min_width(STRIP_WIDTH);
            ui.set_max_width(STRIP_WIDTH);

            ui.vertical(|ui| {
                ui.spacing_mut().item_spacing.y = 3.0;

                let label_color = if is_muted {
                    MUTED_COLOR
                } else if is_current {
                    COLOR_TEXT_ACTIVE
                } else {
                    COLOR_TEXT
                };
                ui.with_layout(egui::Layout::top_down(egui::Align::Center), |ui| {
                    ui.label(
                        RichText::new(format!("{}", ch + 1))
                            .font(FontId::monospace(11.0))
                            .color(label_color),
                    );
                });

                draw_mini_scope(ui, app, ch, is_muted);

                draw_pan_slider(ui, app, ch);

                ui.with_layout(egui::Layout::top_down(egui::Align::Center), |ui| {
                    ui.horizontal(|ui| {
                        let m_color = if is_muted {
                            MUTED_COLOR
                        } else {
                            COLOR_TEXT_DIM
                        };
                        let m_btn = ui.add(
                            egui::Button::new(
                                RichText::new("M")
                                    .font(FontId::monospace(10.0))
                                    .color(m_color),
                            )
                            .min_size(Vec2::new(24.0, 16.0))
                            .frame(is_muted),
                        );
                        if m_btn.clicked() {
                            if ch >= app.muted_channels.len() {
                                app.muted_channels.resize(ch + 1, false);
                            }
                            app.muted_channels[ch] = !app.muted_channels[ch];
                        }

                        let is_soloed = !is_muted
                            && app.muted_channels.len() >= total_channels
                            && (0..total_channels).all(|c| {
                                c == ch || app.muted_channels.get(c).copied().unwrap_or(false)
                            });
                        let s_color = if is_soloed {
                            COLOR_TEXT_ACTIVE
                        } else {
                            COLOR_TEXT_DIM
                        };
                        let s_btn = ui.add(
                            egui::Button::new(
                                RichText::new("S")
                                    .font(FontId::monospace(10.0))
                                    .color(s_color),
                            )
                            .min_size(Vec2::new(24.0, 16.0))
                            .frame(is_soloed),
                        );
                        if s_btn.clicked() {
                            toggle_solo(&mut app.muted_channels, ch, total_channels);
                        }
                    });
                });

                draw_volume_fader(ui, app, ch, is_muted);
            });
        });

    let strip_rect = strip.response.rect;
    if ui.input(|i| i.pointer.primary_pressed())
        && ui
            .input(|i| i.pointer.hover_pos())
            .is_some_and(|p| strip_rect.contains(p))
    {
        app.current_track = ch;
        app.cursor.channel = ch;
        app.cursor.voice = 0;
    }
}

fn draw_mini_scope(ui: &mut egui::Ui, app: &App, ch: usize, is_muted: bool) {
    let width = STRIP_WIDTH;
    let height = SCOPE_HEIGHT;

    let (rect, _) = ui.allocate_exact_size(Vec2::new(width, height), egui::Sense::hover());
    let painter = ui.painter_at(rect);

    painter.rect_filled(rect, 2.0, egui::Color32::from_rgb(12, 10, 20));

    let color = if is_muted {
        MUTED_COLOR
    } else if app.playback.playing {
        COLOR_PATTERN_PLAYBACK_TEXT
    } else {
        COLOR_TEXT_DIM
    };

    if let Some(data) = app.display_scopes.get(ch) {
        let w = rect.width();
        let h = rect.height();
        let mid_y = rect.min.y + h * 0.5;

        let step = SCOPE_SIZE as f32 / w;
        let points: Vec<Pos2> = (0..w as usize)
            .map(|px| {
                let idx = ((px as f32) * step) as usize;
                let sample = data[idx.min(SCOPE_SIZE - 1)];
                let y = mid_y - sample.clamp(-1.0, 1.0) * h * 0.4;
                Pos2::new(rect.min.x + px as f32, y)
            })
            .collect();

        if points.len() >= 2 {
            painter.add(egui::Shape::line(points, Stroke::new(1.0, color)));
        }
    }

    let mid_y = rect.min.y + height * 0.5;
    painter.line_segment(
        [
            Pos2::new(rect.left(), mid_y),
            Pos2::new(rect.right(), mid_y),
        ],
        Stroke::new(0.5, egui::Color32::from_rgba_premultiplied(80, 70, 90, 40)),
    );
}

fn draw_volume_fader(ui: &mut egui::Ui, app: &mut App, ch: usize, _is_muted: bool) {
    let vol = app.project.tracks[ch].default_volume;
    let mut db = if vol > 0.0 {
        20.0_f32 * vol.log10()
    } else {
        -60.0
    }
    .clamp(-60.0, 6.0);

    let width = STRIP_WIDTH;
    let slider_height = FADER_HEIGHT;

    let (rect, response) = ui.allocate_exact_size(
        Vec2::new(width, slider_height),
        egui::Sense::click_and_drag(),
    );
    let painter = ui.painter_at(rect);

    let track_x = rect.center().x;
    let track_top = rect.top() + 4.0;
    let track_bot = rect.bottom() - 4.0;
    let track_h = track_bot - track_top;

    painter.line_segment(
        [Pos2::new(track_x, track_top), Pos2::new(track_x, track_bot)],
        Stroke::new(2.0, egui::Color32::from_rgb(40, 36, 55)),
    );

    let db_zero_y = track_bot - ((0.0 - (-60.0)) / (6.0 - (-60.0))) * track_h;
    painter.line_segment(
        [
            Pos2::new(track_x - 6.0, db_zero_y),
            Pos2::new(track_x + 6.0, db_zero_y),
        ],
        Stroke::new(1.0, COLOR_TEXT_DIM),
    );

    let fader_frac = (db - (-60.0)) / (6.0 - (-60.0));
    let fader_y = track_bot - fader_frac * track_h;

    let fader_color = COLOR_ACCENT;
    let fader_rect =
        egui::Rect::from_center_size(Pos2::new(track_x, fader_y), Vec2::new(22.0, 6.0));
    painter.rect_filled(fader_rect, 2.0, fader_color);

    let fill_rect = egui::Rect::from_min_max(
        Pos2::new(track_x - 1.0, fader_y),
        Pos2::new(track_x + 1.0, track_bot),
    );
    painter.rect_filled(fill_rect, 0.0, fader_color.linear_multiply(0.3));

    if response.dragged()
        && let Some(pointer) = response.interact_pointer_pos()
    {
        let frac = ((track_bot - pointer.y) / track_h).clamp(0.0, 1.0);
        db = -60.0 + frac * 66.0;
        app.project.tracks[ch].default_volume = 10.0_f32.powf(db / 20.0).clamp(0.0, 2.0);
    }
    if response.double_clicked() {
        app.project.tracks[ch].default_volume = 1.0;
    }
    if response.hovered() {
        ui.ctx().set_cursor_icon(egui::CursorIcon::ResizeVertical);
    }

    ui.with_layout(egui::Layout::top_down(egui::Align::Center), |ui| {
        let r = ui
            .add(
                egui::DragValue::new(&mut db)
                    .range(-60.0..=6.0)
                    .speed(0.2)
                    .custom_formatter(|v, _| {
                        let i = v.round() as i32;
                        if i > 0 {
                            format!("+{i}")
                        } else {
                            format!("{i}")
                        }
                    })
                    .fixed_decimals(1),
            )
            .on_hover_cursor(egui::CursorIcon::ResizeHorizontal);
        if r.changed() {
            app.project.tracks[ch].default_volume = 10.0_f32.powf(db / 20.0).clamp(0.0, 2.0);
        }
        if r.has_focus() {
            app.text_editing = true;
        }
    });
}

fn draw_pan_slider(ui: &mut egui::Ui, app: &mut App, ch: usize) {
    let width = STRIP_WIDTH;
    let height = 14.0;

    let (rect, response) =
        ui.allocate_exact_size(Vec2::new(width, height), egui::Sense::click_and_drag());
    let painter = ui.painter_at(rect);

    let track_left = rect.left() + 8.0;
    let track_right = rect.right() - 8.0;
    let track_w = track_right - track_left;
    let mid_y = rect.center().y;

    painter.line_segment(
        [Pos2::new(track_left, mid_y), Pos2::new(track_right, mid_y)],
        Stroke::new(2.0, egui::Color32::from_rgb(40, 36, 55)),
    );

    let center_x = track_left + track_w * 0.5;
    painter.line_segment(
        [
            Pos2::new(center_x, mid_y - 3.0),
            Pos2::new(center_x, mid_y + 3.0),
        ],
        Stroke::new(1.0, COLOR_TEXT_DIM),
    );

    let pan = app.project.tracks[ch].default_panning;
    let knob_x = track_left + pan * track_w;

    let knob_rect = egui::Rect::from_center_size(Pos2::new(knob_x, mid_y), Vec2::new(6.0, 10.0));
    painter.rect_filled(knob_rect, 2.0, COLOR_ACCENT);

    if response.dragged()
        && let Some(pointer) = response.interact_pointer_pos()
    {
        let new_pan = ((pointer.x - track_left) / track_w).clamp(0.0, 1.0);
        app.project.tracks[ch].default_panning = new_pan;
    }
    if response.double_clicked() {
        app.project.tracks[ch].default_panning = 0.5;
    }
    if response.hovered() {
        ui.ctx().set_cursor_icon(egui::CursorIcon::ResizeHorizontal);
    }
}

fn toggle_solo(muted: &mut Vec<bool>, ch: usize, channels: usize) {
    if muted.len() < channels {
        muted.resize(channels, false);
    }

    let is_soloed =
        !muted[ch] && (0..channels).all(|c| c == ch || muted.get(c).copied().unwrap_or(false));

    if is_soloed {
        for m in muted.iter_mut() {
            *m = false;
        }
    } else {
        for (c, m) in muted.iter_mut().enumerate() {
            *m = c != ch;
        }
    }
}
