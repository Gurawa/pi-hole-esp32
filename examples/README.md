# Pi-hole ESP32 Examples

This directory contains example sketches and extensions for the Pi-hole ESP32 client.

## Available Examples

### 1. OLED Display Example
Display Pi-hole statistics on an SSD1306 OLED display.

**File:** `oled_display.cpp`

**Features:**
- Real-time statistics display on 128x64 OLED
- WiFi status indication
- Formatted numbers with K/M suffixes
- Auto-refresh every 30 seconds

**Required Hardware:**
- SSD1306 OLED display (128x64, I2C)
- 4 jumper wires for connection

**Additional Libraries:**
```ini
lib_deps = 
    bblanchon/ArduinoJson@^6.21.3
    adafruit/Adafruit SSD1306@^2.5.7
    adafruit/Adafruit GFX Library@^1.11.9
```

See [HARDWARE.md](../HARDWARE.md) for wiring instructions.

### 2. TFT Display Example (Coming Soon)
Show statistics on a color TFT screen.

### 3. Web Server Example (Coming Soon)
Run a local web server on the ESP32 to view statistics.

### 4. MQTT Publisher Example (Coming Soon)
Publish Pi-hole statistics to an MQTT broker for home automation integration.

## How to Use Examples

1. Copy the desired example to your `src/main.cpp`
2. Install any additional required libraries
3. Configure and upload to your ESP32

## Contributing Examples

We welcome contributions! If you've created an interesting extension or example, please submit a pull request.
