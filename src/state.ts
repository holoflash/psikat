import { Signal, signal } from "./utils/signal";

type STATE = { playing: Signal; arranger: Signal; octave: Signal };

const DEFAULT_STATE: STATE = { playing: signal(false), arranger: signal(false), octave: signal(0) };
export const STATE: STATE = DEFAULT_STATE;
