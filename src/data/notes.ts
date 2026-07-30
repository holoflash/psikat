export const notes = [
  "C-4",
  "C#4",
  "D-4",
  "D#4",
  "E-4",
  "F-4",
  "F#4",
  "G-4",
  "G#4",
  "A-4",
  "A#4",
  "B-4",
  "C-5",
  "···",
];

export function getRandomNote() {
  return notes[Math.floor(Math.random() * notes.length)];
}
