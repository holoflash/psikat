import { Signal, signal } from "./utils/signal";

type AppState = {
  playing: Signal<boolean>;
  arranger: Signal<boolean>;
  octave: Signal<number>;
  command_palette_open: Signal<boolean>;
};

const DEFAULT_STATE: AppState = {
  playing: signal(false),
  arranger: signal(false),
  octave: signal(0),
  command_palette_open: signal(false),
};
export const AppState: AppState = DEFAULT_STATE;
