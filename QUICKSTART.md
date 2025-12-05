# Quick Start Guide - Pi-hole ESP32 Client

Get your ESP32 monitoring Pi-hole statistics in 5 minutes!

## What You Need

- ESP32 development board (any variant)
- USB cable
- Computer with internet connection
- A running Pi-hole server on your network

## Step-by-Step Setup

### 1. Install PlatformIO

**Option A: VS Code (Recommended)**
1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Open VS Code
3. Go to Extensions (Ctrl+Shift+X)
4. Search for "PlatformIO IDE"
5. Click Install

**Option B: Command Line**
```bash
pip install platformio
```

### 2. Get the Code

```bash
git clone https://github.com/Gurawa/pi-hole-esp32.git
cd pi-hole-esp32
```

### 3. Configure Your Settings

```bash
# Copy the example configuration
cp include/config.example.h include/config.h

# Edit the configuration file
nano include/config.h
# or use your favorite editor
```

Update these values in `include/config.h`:
```cpp
#define WIFI_SSID "YourWiFiName"         // Your WiFi network name
#define WIFI_PASSWORD "YourWiFiPassword" // Your WiFi password
#define PIHOLE_SERVER "192.168.1.100"    // Your Pi-hole IP address
```

**How to find your Pi-hole IP:**
- Log into your Pi-hole admin panel
- Look at the browser address bar
- Use the IP address without `http://` or `/admin`

### 4. Upload to ESP32

**Option A: Using PlatformIO CLI**
```bash
# Connect your ESP32 via USB
# Then run:
pio run --target upload

# To see the output:
pio device monitor
```

**Option B: Using VS Code**
1. Open the project folder in VS Code
2. Click the PlatformIO icon in the sidebar
3. Under "Project Tasks" expand your board (e.g., esp32dev)
4. Click "Upload"
5. After upload completes, click "Monitor" to see output

### 5. View the Statistics

Open the Serial Monitor (115200 baud) to see Pi-hole statistics:

```
==================================
Pi-hole ESP32 Client
==================================

Connecting to WiFi...
WiFi connected!
IP address: 192.168.1.150

Fetching initial Pi-hole statistics...

==== Pi-hole Statistics ====
Status: enabled
Domains Blocked: 128543
DNS Queries Today: 1234
Ads Blocked Today: 345
Ads Percentage: 27.95%
...
============================
```

## Troubleshooting

### "WiFi not connected"
- Double-check your SSID and password
- Make sure you're using 2.4GHz WiFi (most ESP32 don't support 5GHz)
- Move closer to your router

### "HTTP request failed"
- Verify the Pi-hole IP address
- Make sure Pi-hole is running: `pihole status`
- Check they're on the same network
- Try accessing in browser: `http://YOUR_PI_IP/admin/api.php?summary`

### "Could not open port"
- Close any other programs using the serial port
- Try a different USB cable
- Press the reset button on ESP32
- Try a different USB port

### Compilation Errors
- Make sure `config.h` exists in the `include/` directory
- Verify all libraries are installed
- Try: `pio lib install` to ensure dependencies are installed

## What's Next?

Now that you have the basic client running, you can:

1. **Add a display**: Show stats on an OLED or TFT screen
2. **Create alerts**: Get notified when Pi-hole is blocking lots of ads
3. **Build a dashboard**: Use the ESP32's web server capabilities
4. **Integrate with home automation**: Send data via MQTT

Check the [ESP32_README.md](ESP32_README.md) for more advanced features!

## Need Help?

- Check the [ESP32_README.md](ESP32_README.md) for detailed documentation
- Review the [examples/](examples/) directory for inspiration
- Open an issue on GitHub if you're stuck

Happy monitoring! 🎉
