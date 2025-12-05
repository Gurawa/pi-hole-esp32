# Frequently Asked Questions (FAQ)

## General Questions

### Q: What is this project?
**A:** This is an ESP32 client for Pi-hole that allows you to monitor your Pi-hole statistics on ESP32 microcontrollers. You can display real-time ad-blocking statistics on OLED/TFT screens or integrate with IoT projects.

### Q: Do I need to install Pi-hole on the ESP32?
**A:** No! The ESP32 is a *client* that connects to an existing Pi-hole server running on another device (Raspberry Pi, Linux server, etc.). The ESP32 fetches and displays statistics only.

### Q: Can the ESP32 replace my Pi-hole server?
**A:** No. The ESP32 doesn't have the resources to run a full DNS server. It's designed to monitor an existing Pi-hole installation, not replace it.

### Q: Which ESP32 boards are supported?
**A:** We support:
- ESP32 (standard)
- ESP32-C3
- ESP32-S3
- Most ESP32 development boards with WiFi capability

## Setup Questions

### Q: How do I find my Pi-hole IP address?
**A:** Several ways:
1. Look at your router's DHCP client list
2. Run `hostname -I` on your Pi-hole device
3. Check the Pi-hole admin panel URL in your browser
4. Use `pihole -a hostrecord` command

### Q: Do I need an API key?
**A:** No, basic statistics don't require authentication. However, if your Pi-hole requires authentication or you want access to additional features, you'll need an API key from: Settings → API → Show API token

### Q: My ESP32 won't connect to WiFi. What should I do?
**A:** Check these common issues:
1. Verify SSID and password are correct (case-sensitive!)
2. Ensure you're using a 2.4GHz network (most ESP32 don't support 5GHz)
3. Check for special characters in your WiFi password
4. Move ESP32 closer to the router
5. Try a different power source

### Q: Where do I put my WiFi credentials?
**A:** 
1. Copy `include/config.example.h` to `include/config.h`
2. Edit `include/config.h`
3. Update `WIFI_SSID` and `WIFI_PASSWORD`
4. Save and upload to ESP32

## Hardware Questions

### Q: What hardware do I need?
**A:** Minimum setup:
- ESP32 development board (any variant)
- USB cable for programming
- Existing Pi-hole server on your network

Optional:
- OLED or TFT display for visual output
- Enclosure/case
- Power supply

### Q: Can I use an ESP8266 instead of ESP32?
**A:** This project is designed for ESP32. ESP8266 has less memory and different libraries. You'd need to modify the code significantly.

### Q: What OLED displays are compatible?
**A:** The example code uses SSD1306 OLED displays (128x64 pixels, I2C). These are very common and inexpensive (~$5). Most 128x64 I2C OLED displays will work.

### Q: How do I wire the OLED display?
**A:** See [HARDWARE.md](HARDWARE.md) for detailed wiring diagrams. Basic connection:
- VCC → 3.3V
- GND → GND
- SDA → GPIO 21
- SCL → GPIO 22

## Software Questions

### Q: What's PlatformIO?
**A:** PlatformIO is a cross-platform IDE for embedded development. It's like Arduino IDE but more powerful. Available as VS Code extension or command-line tool.

### Q: Can I use Arduino IDE instead of PlatformIO?
**A:** Yes, but PlatformIO is recommended. For Arduino IDE:
1. Install ESP32 board support
2. Install required libraries (ArduinoJson, NTPClient)
3. Copy src/main.cpp to a new sketch
4. Configure and upload

### Q: How do I install PlatformIO?
**A:** Two methods:
1. **VS Code (easiest):** Install VS Code → Install PlatformIO IDE extension
2. **Command line:** `pip install platformio`

### Q: What libraries are required?
**A:** 
- ArduinoJson (v6.21.3+) - for parsing Pi-hole API responses
- NTPClient (v3.2.1+) - for time synchronization (optional)
- For OLED: Adafruit SSD1306 + Adafruit GFX Library

### Q: How do I upload the code?
**A:** 
- **PlatformIO CLI:** `pio run --target upload`
- **VS Code:** Click "Upload" in PlatformIO sidebar
- Connect ESP32 via USB and ensure correct port is selected

## Usage Questions

### Q: How often does it update?
**A:** By default, every 30 seconds. You can change this by modifying `UPDATE_INTERVAL` in the code.

### Q: Can I monitor multiple Pi-hole servers?
**A:** Not in the current version, but this would be a great enhancement! You'd need to modify the code to store multiple server configs and cycle through them.

### Q: How do I see the output?
**A:** Two ways:
1. **Serial Monitor:** Connect via USB and open serial monitor at 115200 baud
2. **OLED Display:** Use the OLED example to see stats on a physical display

### Q: Can I control Pi-hole from the ESP32?
**A:** The basic client is read-only (monitoring). To add control features, you'd need to implement API calls for enable/disable and use buttons or a web interface.

## Troubleshooting

### Q: I get "HTTP request failed, error: -1"
**A:** This usually means:
1. Pi-hole server is unreachable
2. Wrong IP address
3. Pi-hole is not running
4. Network connectivity issue

Try: `curl http://YOUR_PIHOLE_IP/admin/api.php?summary` from another computer to verify Pi-hole is accessible.

### Q: My display shows nothing
**A:** Check:
1. I2C address (try 0x3C or 0x3D)
2. Wiring connections
3. Display power (3.3V or 5V depending on display)
4. Run an I2C scanner sketch to detect the display

### Q: "JSON parsing failed"
**A:** The Pi-hole API response might be:
1. Not in JSON format (check API endpoint)
2. Too large for the buffer (increase DynamicJsonDocument size)
3. Malformed due to network issues

### Q: ESP32 keeps rebooting
**A:** Common causes:
1. Insufficient power (try different USB cable/power supply)
2. Memory overflow
3. Watchdog timer timeout
4. Try reducing update frequency

### Q: Compilation errors
**A:** 
1. Ensure `config.h` exists in `include/` directory
2. Check all libraries are installed
3. Update to latest PlatformIO platform
4. Clear build cache: `pio run --target clean`

## Advanced Questions

### Q: Can I add a web server?
**A:** Yes! ESP32 supports web servers. You could create a local web interface to view stats. This would be a great addition!

### Q: How do I add MQTT support?
**A:** Install an MQTT library (like PubSubClient), connect to your MQTT broker, and publish stats as topics. Great for home automation!

### Q: Can I use deep sleep for battery operation?
**A:** Yes! ESP32 supports deep sleep. You'd need to:
1. Wake up periodically
2. Connect to WiFi
3. Fetch stats
4. Update display (if using e-paper)
5. Go back to sleep

### Q: How do I enable OTA updates?
**A:** Add the ArduinoOTA library and implement OTA handling in your code. This allows wireless firmware updates without USB cable.

### Q: Can I log data to SD card?
**A:** Yes! Add an SD card module and use the SD library to log statistics over time. Great for creating historical charts!

## Contributing

### Q: How can I contribute?
**A:** 
1. Test on different ESP32 boards
2. Create new examples (TFT display, MQTT, web server)
3. Improve documentation
4. Report bugs
5. Submit pull requests

### Q: I found a bug. What should I do?
**A:** 
1. Check if it's already reported in GitHub Issues
2. If not, create a new issue with:
   - ESP32 board model
   - PlatformIO version
   - Error messages/logs
   - Steps to reproduce

### Q: Can I submit my own example?
**A:** Absolutely! We'd love to see:
- Different display types
- Integration examples (MQTT, Home Assistant, etc.)
- Creative use cases
- Alternative configurations

## Getting Help

### Q: Where can I get help?
**A:** 
1. Check this FAQ first
2. Read the documentation (ESP32_README.md, QUICKSTART.md)
3. Search existing GitHub Issues
4. Create a new GitHub Issue with details
5. For Pi-hole specific questions: https://discourse.pi-hole.net/

### Q: Is there a community?
**A:** The main Pi-hole community is at https://discourse.pi-hole.net/. Feel free to share your ESP32 Pi-hole projects there!

## Support the Project

### Q: How can I support this project?
**A:** 
- ⭐ Star the repository on GitHub
- Share your builds and setups
- Contribute code or documentation
- Report bugs and suggest features
- Support the main Pi-hole project: https://pi-hole.net/donate

---

**Didn't find your question?** Open an issue on GitHub and we'll help you out!
