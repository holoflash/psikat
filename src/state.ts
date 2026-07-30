import { Signal, signal } from "./utils/signal";

type AppState = { playing: Signal<boolean>; arranger: Signal<boolean>; octave: Signal<number> };

const DEFAULT_STATE: AppState = {
  playing: signal(false),
  arranger: signal(false),
  octave: signal(0),
};
export const AppState: AppState = DEFAULT_STATE;
