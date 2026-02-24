use crate::pattern::Note;
use crate::scale::{Scale, map_key_index_to_midi};
use crossterm::event::KeyCode;

/// Map a keyboard key to a `Note` using the current scale.
///
/// Keys are assigned a linear index (0, 1, 2, …) which is then
/// translated through the scale to the correct MIDI pitch.
pub fn key_to_note(key: KeyCode, octave: u8, scale: &Scale, transpose: i8) -> Option<Note> {
    let key_index = match key {
        KeyCode::Char('z') => Some((0, 0)),
        KeyCode::Char('x') => Some((0, 1)),
        KeyCode::Char('c') => Some((0, 2)),
        KeyCode::Char('v') => Some((0, 3)),
        KeyCode::Char('b') => Some((0, 4)),
        KeyCode::Char('n') => Some((0, 5)),
        KeyCode::Char('m') => Some((0, 6)),
        KeyCode::Char('a') => Some((0, 7)),
        KeyCode::Char('s') => Some((0, 8)),
        KeyCode::Char('d') => Some((0, 9)),
        KeyCode::Char('f') => Some((0, 10)),
        KeyCode::Char('g') => Some((0, 11)),

        KeyCode::Char('h') => Some((0, 12)),
        KeyCode::Char('j') => Some((0, 13)),
        KeyCode::Char('k') => Some((0, 14)),
        KeyCode::Char('l') => Some((0, 15)),
        KeyCode::Char('q') => Some((0, 16)),
        KeyCode::Char('w') => Some((0, 17)),
        KeyCode::Char('e') => Some((0, 18)),
        KeyCode::Char('r') => Some((0, 19)),
        KeyCode::Char('t') => Some((0, 20)),
        KeyCode::Char('y') => Some((0, 21)),
        KeyCode::Char('u') => Some((0, 22)),
        KeyCode::Char('i') => Some((0, 23)),
        KeyCode::Char('o') => Some((0, 24)),
        KeyCode::Char('p') => Some((0, 25)),

        _ => None,
    };

    key_index.map(|(_oct_offset, idx)| {
        let midi = map_key_index_to_midi(idx, octave, scale, transpose);
        Note::new(midi)
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::scale::CHROMATIC;

    #[test]
    fn chromatic_c4() {
        let note = key_to_note(KeyCode::Char('z'), 4, &CHROMATIC, 0).unwrap();
        assert_eq!(note.pitch, 60);
        assert_eq!(note.name(), "C-4");
    }

    #[test]
    fn chromatic_a4() {
        let note = key_to_note(KeyCode::Char('d'), 4, &CHROMATIC, 0).unwrap();
        assert_eq!(note.pitch, 69);
    }

    #[test]
    fn chromatic_upper_octave() {
        let note = key_to_note(KeyCode::Char('h'), 4, &CHROMATIC, 0).unwrap();
        assert_eq!(note.pitch, 72);
    }

    #[test]
    fn unknown_key() {
        assert!(key_to_note(KeyCode::Char('0'), 4, &CHROMATIC, 0).is_none());
    }
}
