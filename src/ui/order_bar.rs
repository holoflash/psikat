use eframe::egui::{self, RichText, Sense};

use crate::app::{App, Mode};
use crate::ui::{
    COLOR_LAYOUT_BG_DARK, COLOR_LAYOUT_BORDER, COLOR_PATTERN_CURSOR_BG, COLOR_PATTERN_CURSOR_TEXT,
    COLOR_TEXT, COLOR_TEXT_DIM,
};

const FONT: egui::FontId = egui::FontId::monospace(11.0);
const CELL_W: f32 = 22.0;
const CELL_H: f32 = 18.0;

pub fn draw_order_bar(ctx: &egui::Context, app: &mut App) {
    egui::TopBottomPanel::top("order_bar").show(ctx, |ui| {
        ui.set_min_height(24.0);
        let painter = ui.painter();
        painter.rect_filled(ui.max_rect(), 0.0, COLOR_LAYOUT_BG_DARK);

        ui.horizontal_centered(|ui| {
            ui.spacing_mut().item_spacing.x = 3.0;

            ui.label(RichText::new("ORD").font(FONT).color(COLOR_TEXT_DIM));
            ui.add_space(4.0);

            for (i, &pat_idx) in app.project.order.iter().enumerate() {
                let is_current = i == app.project.current_order_idx;
                let is_playing = app.playback.playing && i == app.playback_order_display;

                let (bg, fg) = if is_current && app.mode == Mode::Edit {
                    (COLOR_PATTERN_CURSOR_BG, COLOR_PATTERN_CURSOR_TEXT)
                } else if is_playing {
                    (
                        egui::Color32::from_rgb(90, 75, 40),
                        egui::Color32::from_rgb(255, 245, 220),
                    )
                } else if is_current {
                    (egui::Color32::from_rgb(40, 36, 56), COLOR_TEXT)
                } else {
                    (COLOR_LAYOUT_BG_DARK, COLOR_TEXT_DIM)
                };

                let (rect, response) =
                    ui.allocate_exact_size(egui::vec2(CELL_W, CELL_H), Sense::click());

                let rounding = 3.0;
                ui.painter().rect_filled(rect, rounding, bg);

                if is_current {
                    ui.painter().rect_stroke(
                        rect,
                        rounding,
                        egui::Stroke::new(1.0, COLOR_LAYOUT_BORDER),
                        egui::StrokeKind::Inside,
                    );
                }

                let text = format!("{:02X}", pat_idx);
                ui.painter()
                    .text(rect.center(), egui::Align2::CENTER_CENTER, text, FONT, fg);

                if response.clicked() {
                    app.project.current_order_idx = i;
                    app.cursor.row = 0;
                }
            }

            ui.add_space(6.0);

            let btn = |ui: &mut egui::Ui, label: &str| -> bool {
                ui.add(
                    egui::Button::new(RichText::new(label).font(FONT).color(COLOR_TEXT))
                        .min_size(egui::vec2(24.0, CELL_H))
                        .fill(egui::Color32::from_rgb(32, 28, 48))
                        .stroke(egui::Stroke::new(1.0, COLOR_LAYOUT_BORDER)),
                )
                .clicked()
            };

            if btn(ui, "+") {
                let current_pat = app.project.order[app.project.current_order_idx];
                let insert_pos = app.project.current_order_idx + 1;
                app.project.order.insert(insert_pos, current_pat);
                app.project.current_order_idx = insert_pos;
                app.cursor.row = 0;
            }

            if app.project.order.len() > 1 && btn(ui, "−") {
                app.project.order.remove(app.project.current_order_idx);
                if app.project.current_order_idx >= app.project.order.len() {
                    app.project.current_order_idx = app.project.order.len() - 1;
                }
                app.cursor.row = 0;
            }

            if btn(ui, "NEW") {
                let channels = app.project.current_pattern().channels;
                let rows = app.project.current_pattern().rows;
                let new_idx = app.project.patterns.len();
                app.project
                    .patterns
                    .push(crate::project::Pattern::new(channels, rows));
                let insert_pos = app.project.current_order_idx + 1;
                app.project.order.insert(insert_pos, new_idx);
                app.project.current_order_idx = insert_pos;
                app.cursor.row = 0;
            }
        });
    });
}
