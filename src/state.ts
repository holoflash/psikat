import { Signal, signal } from "./utils/signal";

type STATE = { playing: Signal<boolean>; arranger: Signal<boolean>; octave: Signal<number> };

const DEFAULT_STATE: STATE = { playing: signal(false), arranger: signal(false), octave: signal(0) };
export const STATE: STATE = DEFAULT_STATE;
