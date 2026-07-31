import { defineConfig } from "vite-plus";

export default defineConfig({
  staged: {
    "*": "vp check --fix",
  },
  fmt: { ignorePatterns: ["./data"] },
  lint: {
    jsPlugins: [{ name: "vite-plus", specifier: "vite-plus/oxlint-plugin" }],
    plugins: ["eslint", "import", "oxc", "typescript", "unicorn"],
    categories: { correctness: "error", perf: "error", suspicious: "error" },
    rules: { "vite-plus/prefer-vite-plus-imports": "error", "no-underscore-dangle": "off" },
    options: { typeAware: true, typeCheck: true },
  },
});
