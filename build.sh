#!/bin/bash
# Build and upload script for Pi-hole ESP32 Client

set -e

echo "=================================="
echo "Pi-hole ESP32 Client - Build Tool"
echo "=================================="
echo ""

# Check if PlatformIO is installed
if ! command -v pio &> /dev/null; then
    echo "ERROR: PlatformIO is not installed!"
    echo ""
    echo "Install it with:"
    echo "  pip install platformio"
    echo ""
    echo "Or install the VS Code extension:"
    echo "  https://platformio.org/install/ide?install=vscode"
    exit 1
fi

# Check if config.h exists
if [ ! -f "include/config.h" ]; then
    echo "ERROR: Configuration file not found!"
    echo ""
    echo "Please create include/config.h from the template:"
    echo "  cp include/config.example.h include/config.h"
    echo ""
    echo "Then edit it with your WiFi and Pi-hole settings."
    exit 1
fi

# Show available boards
echo "Available boards:"
echo "  1. esp32dev     - Standard ESP32"
echo "  2. esp32-c3     - ESP32-C3"
echo "  3. esp32-s3     - ESP32-S3"
echo ""

# Default to esp32dev
BOARD="${1:-esp32dev}"

echo "Building for: $BOARD"
echo ""

# Build the project
echo "Building project..."
pio run -e "$BOARD"

echo ""
echo "Build successful!"
echo ""
echo "To upload to your ESP32:"
echo "  ./build.sh $BOARD && pio run -e $BOARD --target upload"
echo ""
echo "To monitor serial output:"
echo "  pio device monitor"
echo ""
