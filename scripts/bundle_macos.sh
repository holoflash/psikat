#!/bin/bash
set -euo pipefail

APP_NAME="Psikat"
BUNDLE_ID="com.holoflash.psikat"
VERSION=$(grep '^version' Cargo.toml | head -1 | sed 's/.*"\(.*\)".*/\1/')

echo "Building ${APP_NAME} v${VERSION} release..."
cargo build --release

APP_DIR="target/${APP_NAME}.app"
CONTENTS="${APP_DIR}/Contents"
MACOS="${CONTENTS}/MacOS"
RESOURCES="${CONTENTS}/Resources"

rm -rf "${APP_DIR}"
mkdir -p "${MACOS}" "${RESOURCES}"

cp "target/release/psikat" "${MACOS}/${APP_NAME}"

cat > "${CONTENTS}/Info.plist" << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleName</key>
    <string>${APP_NAME}</string>
    <key>CFBundleDisplayName</key>
    <string>${APP_NAME}</string>
    <key>CFBundleIdentifier</key>
    <string>${BUNDLE_ID}</string>
    <key>CFBundleVersion</key>
    <string>${VERSION}</string>
    <key>CFBundleShortVersionString</key>
    <string>${VERSION}</string>
    <key>CFBundleExecutable</key>
    <string>${APP_NAME}</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleIconFile</key>
    <string>AppIcon</string>
    <key>NSHighResolutionCapable</key>
    <true/>
    <key>LSMinimumSystemVersion</key>
    <string>12.0</string>
    <key>NSSupportsAutomaticGraphicsSwitching</key>
    <true/>
</dict>
</plist>
EOF

ICONSET="target/AppIcon.iconset"
mkdir -p "${ICONSET}"
python3 -c "
from PIL import Image
img = Image.open('assets/icon.png')
for s in [16, 32, 64, 128, 256, 512]:
    img.resize((s, s), Image.NEAREST).save(f'${ICONSET}/icon_{s}x{s}.png')
for s, label in [(32,16), (64,32), (256,128), (512,256), (1024,512)]:
    img.resize((s, s), Image.NEAREST).save(f'${ICONSET}/icon_{label}x{label}@2x.png')
"
iconutil -c icns "${ICONSET}" -o "${RESOURCES}/AppIcon.icns"
rm -rf "${ICONSET}"

echo ""
echo "✓ Built ${APP_DIR}"
