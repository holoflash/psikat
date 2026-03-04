use eframe::egui::{self, Stroke};

use crate::app::App;

use super::{COLOR_LAYOUT_BG_DARK, commands_ref, instrument, settings_panel};

pub fn draw_sidebar(ctx: &egui::Context, app: &mut App) {
    if !app.show_sidebar {
        return;
    }
    egui::SidePanel::right("sidebar")
        .resizable(false)
        .exact_width(560.0)
        .frame(
            egui::Frame::new()
                .fill(COLOR_LAYOUT_BG_DARK)
                .inner_margin(egui::Margin::ZERO)
                .stroke(Stroke::NONE),
        )
        .show(ctx, |ui| {
            let half = ui.available_width() / 2.0;
            egui::SidePanel::left("sidebar_left")
                .resizable(false)
                .exact_width(half)
                .frame(
                    egui::Frame::new()
                        .fill(COLOR_LAYOUT_BG_DARK)
                        .inner_margin(egui::Margin::ZERO)
                        .stroke(Stroke::NONE),
                )
                .show_inside(ui, |ui| {
                    egui::ScrollArea::vertical()
                        .id_salt("sidebar_left_scroll")
                        .auto_shrink([false; 2])
                        .show(ui, |ui| {
                            ui.spacing_mut().item_spacing.y = 0.0;
                            instrument::draw_instrument(ui, app);
                            instrument::draw_instrument_list(ui, app);
                        });
                });
            egui::ScrollArea::vertical()
                .id_salt("sidebar_right_scroll")
                .auto_shrink([false; 2])
                .show(ui, |ui| {
                    ui.spacing_mut().item_spacing.y = 0.0;
                    settings_panel::draw_settings(ui, app);
                    commands_ref::draw_commands_ref(ui);
                });
        });
}
