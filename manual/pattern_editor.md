# Pattern Editor

## Poly Mode

Poly mode lets you enter chords across multiple voices in a single step.

- Toggle poly mode with the **POLY** button in the UI.
- Number of voices is toggled in the track editor.
- While poly mode is **off**, a note key writes one note to the cursor's exact voice and advances the row by the current step size.
- While poly mode is **on**:
  - Each note key pressed within a short window (~3 frames) is collected into a chord buffer instead of written immediately.
  - When the window expires the whole chord is committed at the current row, starting at the **cursor's current voice** and spreading upward, clamped to the channel's maximum voices.
  - A single note pressed in poly mode writes to the cursor's current voice (same position you'd expect in **mono** mode).
  - After committing, the cursor advances by the current step size.
