# Pi-hole ESP32 - Quick Start Guide

## What You Need
- ESP32 board (any variant with 4MB+ flash)
- USB cable
- WiFi network (2.4GHz)
- Computer with PlatformIO installed

## 5-Minute Setup

### Step 1: Configure WiFi
Edit `include/config.h`:
```cpp
#define WIFI_SSID "YourNetworkName"
#define WIFI_PASSWORD "YourPassword"
```

### Step 2: Upload to ESP32
```bash
pio run --target upload
pio device monitor
```

### Step 3: Note the IP Address
Watch the serial monitor for:
```
WiFi connected!
IP Address: 192.168.1.100  <-- This is your DNS server IP
```

### Step 4: Configure Your Device
On your phone/computer:
1. Go to WiFi settings
2. Change DNS to the ESP32's IP (e.g., 192.168.1.100)
3. Save and reconnect

### Step 5: Test It!
1. Open browser to `http://192.168.1.100/`
2. Add a test domain like "doubleclick.net"
3. Try visiting that site - it should be blocked!

## Troubleshooting

**Can't connect to WiFi?**
- Check SSID/password spelling
- Verify 2.4GHz network (ESP32 doesn't support 5GHz)

**DNS not working?**
- Verify you entered the correct IP as DNS
- Try pinging the ESP32: `ping 192.168.1.100`

**Web interface not loading?**
- Make sure you're using `http://` not `https://`
- Try the IP address directly

## Next Steps
- Add more domains to your blocklist
- Configure your router to use ESP32 as network-wide DNS
- Check statistics on the web dashboard

For full documentation, see ESP32_README.md
