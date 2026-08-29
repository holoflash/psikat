type CssVar =
  | "--BG_1"
  | "--BG_2"
  | "--BG_3"
  | "--BG_4"
  | "--BG_5"
  | "--BG_6"
  | "--ACCENT"
  | "--TEXT"
  | "--TEXT_DIM"
  | "--PADDING_MD";

export function get_css_var(variable: CssVar) {
  return getComputedStyle(document.body).getPropertyValue(variable);
}
