#!/bin/bash
set -euo pipefail

echo "Building Psikat release..."
cargo build --release

echo ""
echo "✓ Built target/release/psikat"
echo ""
echo "To install:"
echo "  sudo cp target/release/psikat /usr/local/bin/"
echo "  cp assets/psikat.desktop ~/.local/share/applications/"
echo "  cp assets/icon.png ~/.local/share/icons/psikat.png"
