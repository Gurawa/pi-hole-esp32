# Pi-hole ESP32 Client

An ESP32-based client for monitoring Pi-hole statistics. This project allows you to connect an ESP32 microcontroller to your Pi-hole server and fetch real-time statistics via the Pi-hole API.

## Features

- ✅ WiFi connectivity for ESP32
- ✅ Pi-hole API integration
- ✅ Real-time statistics monitoring
- ✅ Support for multiple ESP32 variants (ESP32, ESP32-C3, ESP32-S3)
- ✅ JSON parsing of API responses
- ✅ Automatic reconnection on WiFi dropout
- ✅ Serial monitor output for debugging
- ✅ Easy configuration

## Statistics Available

The client fetches the following statistics from your Pi-hole:

- Domains being blocked
- DNS queries today
- Ads blocked today
- Ads percentage today
- Unique domains
- Queries forwarded
- Queries cached
- Unique clients
- Pi-hole status

## Requirements

### Hardware

- ESP32 development board (any variant: ESP32, ESP32-C3, ESP32-S3)
- USB cable for programming
- WiFi network
- Running Pi-hole server on your network

### Software

- [PlatformIO](https://platformio.org/) (recommended) or Arduino IDE
- Pi-hole server (v5.0 or later)

## Installation

### Using PlatformIO (Recommended)

1. **Install PlatformIO**
   - [VS Code extension](https://platformio.org/install/ide?install=vscode)
   - Or [PlatformIO CLI](https://docs.platformio.org/en/latest/core/installation.html)

2. **Clone or download this repository**
   ```bash
   git clone https://github.com/Gurawa/pi-hole-esp32.git
   cd pi-hole-esp32
   ```

3. **Configure your settings**
   ```bash
   cp include/config.example.h include/config.h
   ```
   
   Edit `include/config.h` and update:
   - `WIFI_SSID`: Your WiFi network name
   - `WIFI_PASSWORD`: Your WiFi password
   - `PIHOLE_SERVER`: Your Pi-hole server IP address or hostname
   - `PIHOLE_API_KEY`: (Optional) Your Pi-hole API key

4. **Build and upload**
   ```bash
   pio run --target upload
   ```

5. **Monitor serial output**
   ```bash
   pio device monitor
   ```

### Using Arduino IDE

1. **Install ESP32 board support**
   - Follow the [official guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)

2. **Install required libraries**
   - ArduinoJson (v6.21.3 or later)
   - NTPClient (v3.2.1 or later)

3. **Open the project**
   - Copy `src/main.cpp` content to a new Arduino sketch
   - Configure settings in `include/config.h`

4. **Select your board**
   - Tools -> Board -> ESP32 Arduino -> Your ESP32 board

5. **Upload the sketch**

## Configuration

### WiFi Settings

```cpp
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
```

### Pi-hole Server

You can use either an IP address or hostname:

```cpp
#define PIHOLE_SERVER "192.168.1.100"  // IP address
// or
#define PIHOLE_SERVER "pi.hole"         // Hostname
```

### API Authentication (Optional)

For enhanced security or accessing restricted endpoints, you can configure an API key:

1. Log in to your Pi-hole admin panel
2. Go to Settings -> API
3. Click "Show API token"
4. Copy the token to your config:

```cpp
#define PIHOLE_API_KEY "your_api_token_here"
```

**Note:** Basic statistics don't require authentication by default.

## Usage

Once uploaded and running, the ESP32 will:

1. Connect to your WiFi network
2. Fetch Pi-hole statistics every 30 seconds
3. Display statistics on the serial monitor
4. Automatically reconnect if WiFi connection is lost

### Serial Monitor Output Example

```
==================================
Pi-hole ESP32 Client
==================================

Connecting to WiFi...
WiFi connected!
IP address: 192.168.1.150

Fetching initial Pi-hole statistics...
Fetching from: http://192.168.1.100/admin/api.php?summary

==== Pi-hole Statistics ====
Status: enabled
Domains Blocked: 128543
DNS Queries Today: 1234
Ads Blocked Today: 345
Ads Percentage: 27.95%
Unique Domains: 89
Queries Forwarded: 789
Queries Cached: 445
Unique Clients: 5
============================
```

## Extending the Project

This basic client can be extended with:

- **OLED/TFT Display**: Show statistics on a physical display
- **Web Server**: Create a local web interface
- **LED Indicators**: Visual status indicators
- **Button Controls**: Enable/disable Pi-hole remotely
- **MQTT Integration**: Publish stats to home automation systems
- **Multiple Pi-hole Support**: Monitor multiple Pi-hole instances

## Supported ESP32 Boards

The project includes configurations for:

- **ESP32 Dev Module** (`esp32dev`)
- **ESP32-C3** (`esp32-c3-devkitm-1`)
- **ESP32-S3** (`esp32-s3-devkitc-1`)

To build for a specific board:
```bash
pio run -e esp32dev        # Standard ESP32
pio run -e esp32-c3        # ESP32-C3
pio run -e esp32-s3        # ESP32-S3
```

## Troubleshooting

### WiFi Connection Issues

- Verify SSID and password are correct
- Ensure ESP32 is within WiFi range
- Check if your network uses 2.4GHz (ESP32 doesn't support 5GHz on most models)

### Can't Connect to Pi-hole

- Verify Pi-hole server IP address
- Ensure ESP32 and Pi-hole are on the same network
- Check Pi-hole is running: `pihole status`
- Test API manually: `curl http://YOUR_PIHOLE_IP/admin/api.php?summary`

### Compilation Errors

- Ensure all libraries are installed
- Check you have the latest ESP32 platform
- Verify `config.h` exists in the `include` directory

## API Reference

This client uses the Pi-hole API v5+ endpoints:

- **Summary Statistics**: `/admin/api.php?summary`
- **Full API docs**: http://your-pihole-ip/admin/api.php

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues.

## License

This project inherits the license from the original Pi-hole project (EUPL-1.2).

## Related Projects

- [Pi-hole](https://github.com/pi-hole/pi-hole) - The main Pi-hole project
- [Pi-hole Admin](https://github.com/pi-hole/AdminLTE) - Pi-hole web interface

## Support

For Pi-hole specific questions, visit the [Pi-hole Discourse](https://discourse.pi-hole.net/).

For ESP32 client issues, please open an issue on this repository.
