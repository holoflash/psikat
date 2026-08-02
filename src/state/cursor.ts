import { signal, type Signal } from "../utils/signal";

type CursorState = {
  position_x: Signal<number>;
  position_y: Signal<number>;
};

const INIT_CURSOR_STATE: CursorState = {
  position_x: signal(0),
  position_y: signal(1),
};

export const CursorState: CursorState = INIT_CURSOR_STATE;
