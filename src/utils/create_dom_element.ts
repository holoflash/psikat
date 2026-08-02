export function create_dom_element<T extends keyof HTMLElementTagNameMap>(
  tag_name: T,
  params?: Partial<HTMLElementTagNameMap[T]>,
) {
  const element = document.createElement(tag_name);
  if (params) {
    return Object.assign(element, { ...params });
  } else {
    return element;
  }
}
