@echo off
echo Building Psikat release...
cargo build --release

echo.
echo Done! Binary at target\release\psikat.exe
