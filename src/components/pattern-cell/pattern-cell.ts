class PatternCellComponent extends HTMLElement {
  static get observedAttributes() {
    return ["cell_value"];
  }
  connectedCallback() {
    this.render();
    // this.addEventListener("click", this);
  }
  //   handleEvent(event) {
  //     console.log(event);
  //   }

  attributeChangedCallback(_: string, oldValue: string, newValue: string) {
    if (newValue !== oldValue) {
      this.render();
    }
  }

  get cell_value() {
    return this.getAttribute("cell_value");
  }

  set cell_value(value) {
    this.setAttribute("cell_value", value ?? "0");
  }

  render() {
    this.textContent = this.cell_value;
    console.log(this.cell_value);
  }
}

export function RegisterPatternCellComponent() {
  customElements.define("x-pattern-cell", PatternCellComponent);
}
