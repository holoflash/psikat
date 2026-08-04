import { create_dom_element } from "../../utils/create_dom_element";

class PatternComponent extends HTMLElement {
  static get observedAttributes() {
    return ["steps", "voices", "fx-tracks"];
  }
  connectedCallback() {
    this.render();
  }
  // first arg "name" omitted
  attributeChangedCallback(_: string, oldValue: string, newValue: string) {
    if (newValue !== oldValue) {
      this.render();
    }
  }

  get steps() {
    return this.getAttribute("steps");
  }

  set steps(value) {
    this.setAttribute("steps", value ?? "0");
  }

  render() {
    const stepsCount = parseInt(this.getAttribute("steps") ?? "0");
    const voiceCount = parseInt(this.getAttribute("voices") ?? "0");
    this.replaceChildren();
    for (let j = 0; j < voiceCount; j++) {
      const wrapper = create_dom_element("div");
      for (let i = 0; i < stepsCount; i++) {
        wrapper.append(create_dom_element("div", { textContent: "C-4" }));
      }
      this.append(wrapper);
    }
  }
}

export function RegisterPatternComponent() {
  customElements.define("x-pattern", PatternComponent);
}
