declare global {
  interface Window {
    psikat_state: {
      arranger: boolean;
      playing: boolean;
    };
  }
}

export { type global };
