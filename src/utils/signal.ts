// https://plainvanillaweb.com/blog/articles/2024-08-30-poor-mans-signals/
export class Signal<T> extends EventTarget {
  #value: T;
  get value() {
    return this.#value;
  }
  set value(value) {
    if (this.equals(value)) return;
    this.#value = value;
    this.dispatchEvent(new CustomEvent("change"));
  }

  constructor(value: T) {
    super();
    this.#value = value;
  }

  equals(value: T) {
    return this.#value === value;
  }

  effect(fn: any) {
    fn();
    this.addEventListener("change", fn);
    return () => this.removeEventListener("change", fn);
  }

  valueOf() {
    return this.#value;
  }
  toString() {
    return String(this.#value);
  }
}

export const signal = (_: any) => new Signal(_);
