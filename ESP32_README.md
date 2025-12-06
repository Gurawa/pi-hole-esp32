# Pi-hole ESP32

A lightweight DNS-based ad blocker running on ESP32, inspired by the original Pi-hole project.

## Overview

This is a refactored version of Pi-hole designed to run on ESP32 microcontrollers. It provides network-wide ad blocking by acting as a DNS server that filters requests against a customizable blocklist.

## Features

- ✅ **DNS Server**: Lightweight DNS server running on ESP32
- ✅ **Ad Blocking**: Block ads and tracking domains network-wide
- ✅ **Web Interface**: Simple web dashboard for management and statistics
- ✅ **Customizable Blocklists**: Add/remove domains via web interface
- ✅ **Real-time Statistics**: Monitor queries, blocks, and performance
- ✅ **Low Resource Usage**: Optimized for ESP32's limited resources
- ✅ **Easy Configuration**: Simple WiFi and DNS settings

## Hardware Requirements

- **ESP32 Development Board** (ESP32-WROOM-32, ESP32-DevKitC, or similar)
- **Minimum 4MB Flash** (for filesystem and firmware)
- **Stable Power Supply** (USB or 5V power adapter)
- **WiFi Network** (2.4GHz)

### Recommended Boards
- ESP32-DevKitC
- ESP32-WROOM-32
- NodeMCU-32S
- Any ESP32 board with at least 4MB flash

## Software Requirements

- [PlatformIO](https://platformio.org/) (recommended) or Arduino IDE
- USB drivers for your ESP32 board (usually CH340 or CP2102)

## Installation

### Using PlatformIO (Recommended)

1. **Install PlatformIO**
   - [Download VS Code](https://code.visualstudio.com/)
   - Install the PlatformIO IDE extension

2. **Clone the Repository**
   ```bash
   git clone https://github.com/Gurawa/pi-hole-esp32.git
   cd pi-hole-esp32
   ```

3. **Configure WiFi Credentials**
   Copy the template configuration file and edit it:
   ```bash
   cp include/config.h.template include/config.h
   ```
   Then edit `include/config.h` and set your WiFi credentials:
   ```cpp
   #define WIFI_SSID "YourWiFiSSID"
   #define WIFI_PASSWORD "YourWiFiPassword"
   ```
   **Note**: `config.h` is in `.gitignore` to prevent accidentally committing credentials.

4. **Configure DNS Settings** (Optional)
   In `include/config.h`, you can also configure:
   - Upstream DNS server (default: 8.8.8.8)
   - Web server port (default: 80)
   - Maximum blocklist entries
   - Device hostname

5. **Upload Filesystem** (Optional)
   To use the sample blocklist:
   ```bash
   pio run --target uploadfs
   ```

6. **Build and Upload**
   ```bash
   pio run --target upload
   ```

7. **Monitor Serial Output**
   ```bash
   pio device monitor
   ```

### Using Arduino IDE

1. **Install Arduino IDE** and ESP32 board support
   - Follow [ESP32 Arduino Core installation guide](https://github.com/espressif/arduino-esp32)

2. **Install Required Libraries**
   - ArduinoJson (v7.2.0 or later)
   - ESPAsyncWebServer
   - AsyncTCP

3. **Open the Project**
   - Open `src/main.cpp` in Arduino IDE

4. **Configure Settings**
   - Edit `include/config.h` as described above

5. **Select Board and Port**
   - Tools → Board → ESP32 Dev Module
   - Tools → Port → Select your ESP32's port

6. **Upload**
   - Click Upload button

## Configuration

### WiFi Settings
Create `include/config.h` from the template first:
```bash
cp include/config.h.template include/config.h
```

Then edit `include/config.h`:
```cpp
#define WIFI_SSID "YourWiFiSSID"      // Your WiFi network name
#define WIFI_PASSWORD "YourWiFiPassword"  // Your WiFi password
```
**Important**: Never commit your actual `config.h` with credentials to Git!

### DNS Settings
```cpp
#define DNS_PORT 53                    // DNS server port (default: 53)
#define UPSTREAM_DNS_IP "8.8.8.8"     // Upstream DNS server
#define UPSTREAM_DNS_PORT 53           // Upstream DNS port
```

### Web Interface Settings
```cpp
#define WEB_SERVER_PORT 80             // Web interface port
#define WEB_PASSWORD "admin"           // Web interface password (future use)
```

### Blocklist Settings
```cpp
#define MAX_BLOCKLIST_ENTRIES 1000     // Maximum domains in blocklist
#define BLOCKLIST_FILE "/blocklist.txt" // Blocklist file path
```

## Usage

### 1. Initial Setup

After uploading the firmware:
1. Open Serial Monitor (115200 baud)
2. Wait for the device to connect to WiFi
3. Note the IP address displayed (e.g., `192.168.1.100`)

### 2. Configure Network Devices

You have three options to use Pi-hole ESP32:

#### Option A: Configure Router DNS (Recommended)
- Log into your router's admin panel
- Find DNS settings (usually under DHCP or WAN settings)
- Set Primary DNS to your ESP32's IP address
- Save settings and reboot devices

#### Option B: Configure Individual Devices
On each device you want to protect:
- Go to Network Settings
- Set DNS server to ESP32's IP address
- Example on Windows: Network Settings → Change adapter options → Properties → IPv4 → DNS

#### Option C: Use DHCP Server (Advanced)
- Some routers allow setting DHCP options
- Configure DHCP to advertise ESP32's IP as DNS server

### 3. Access Web Interface

1. Open a web browser
2. Navigate to: `http://<ESP32_IP_ADDRESS>/`
3. You'll see the Pi-hole ESP32 dashboard with:
   - Real-time statistics
   - Blocklist management
   - Add/remove domains

### 4. Manage Blocklist

#### Via Web Interface:
- **Add Domain**: Type domain name and click "Add Domain"
- **Remove Domain**: Click "Remove" button next to domain
- **View Statistics**: Automatically updates every 5 seconds

#### Via Serial Monitor:
- Monitor real-time DNS queries
- View statistics printed every 60 seconds
- Debug blocked and forwarded queries

## Blocklist Management

### Default Blocklist
The sample blocklist (`data/blocklist.txt`) includes common ad and tracking domains:
- doubleclick.net
- googlesyndication.com
- googleadservices.com
- And more...

### Adding Custom Domains
1. Via web interface: Enter domain and click "Add Domain"
2. Via file system: Edit `/blocklist.txt` on the ESP32 filesystem

### Blocklist Format
- One domain per line
- Lines starting with `#` are comments
- Empty lines are ignored
- Domains are case-insensitive
- Subdomain blocking: `example.com` blocks `www.example.com`, `ads.example.com`, etc.

### Examples
```
# Block entire domain and all subdomains
doubleclick.net

# Block specific subdomain only
ads.example.com

# Comments are ignored
# example.org
```

## Web Interface

### Dashboard Features
- **Statistics Cards**: Display total queries, blocked queries, block rate, and blocklist size
- **Real-time Updates**: Stats refresh every 5 seconds
- **Domain Management**: Add/remove domains on the fly
- **Responsive Design**: Works on desktop and mobile devices

### API Endpoints
- `GET /`: Main dashboard
- `GET /api/stats`: Get current statistics (JSON)
- `GET /api/blocklist`: Get all blocked domains (JSON)
- `POST /api/add?domain=<domain>`: Add domain to blocklist
- `POST /api/remove?domain=<domain>`: Remove domain from blocklist
- `POST /api/reset`: Reset statistics

## Troubleshooting

### WiFi Connection Issues
- **Symptom**: "Failed to connect to WiFi"
- **Solution**: 
  - Verify SSID and password in `config.h`
  - Ensure ESP32 is within WiFi range
  - Check that WiFi is 2.4GHz (ESP32 doesn't support 5GHz)
  - Restart ESP32 after changing config

### DNS Not Working
- **Symptom**: Devices can't resolve domains
- **Solution**:
  - Verify ESP32 IP address is correct
  - Check that port 53 is not blocked by firewall
  - Ensure upstream DNS server is reachable
  - Try pinging ESP32 from client device

### Web Interface Not Loading
- **Symptom**: Can't access web dashboard
- **Solution**:
  - Verify ESP32 is connected to WiFi
  - Check correct IP address in browser
  - Try `http://<IP>/` (include http://)
  - Clear browser cache

### Blocklist Not Working
- **Symptom**: Ads still appearing
- **Solution**:
  - Verify domains are added to blocklist
  - Check domain spelling (no typos)
  - Some ads use multiple domains
  - Clear browser cache and DNS cache on client

### Out of Memory
- **Symptom**: ESP32 crashes or reboots
- **Solution**:
  - Reduce `MAX_BLOCKLIST_ENTRIES` in config.h
  - Remove unused domains from blocklist
  - Monitor free heap in serial output
  - Use ESP32 with more RAM (WROVER variant)

### Serial Output
Enable debugging by checking serial monitor (115200 baud):
```
=== Pi-hole ESP32 ===
Connecting to WiFi: YourNetwork
WiFi connected!
IP Address: 192.168.1.100
DNS server started successfully
Web server started successfully
System Ready!
```

## Performance Considerations

### Memory Usage
- **Blocklist**: Each domain uses ~20-30 bytes of RAM
- **DNS Cache**: ~50 entries cached
- **Recommended**: Keep blocklist under 1000 entries for stability

### Query Performance
- **Local blocks**: ~1-2ms response time
- **Forwarded queries**: ~10-50ms (depends on upstream DNS)
- **Throughput**: Can handle ~50-100 queries/second

### Network Impact
- **Bandwidth**: Minimal (only DNS packets, ~50 bytes per query)
- **Latency**: Usually faster than ISP DNS due to local blocking

## Advanced Configuration

### Custom Upstream DNS
Popular options:
- Google DNS: `8.8.8.8` or `8.8.4.4`
- Cloudflare: `1.1.1.1` or `1.0.0.1`
- Quad9: `9.9.9.9`
- OpenDNS: `208.67.222.222`

### Static IP Configuration
To assign a static IP to ESP32, add to `setup()` in `main.cpp`:
```cpp
IPAddress local_IP(192, 168, 1, 100);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WiFi.config(local_IP, gateway, subnet);
```

### Multiple Blocklists
To use multiple blocklist files, modify `BlocklistManager.cpp`:
```cpp
blocklistManager.loadBlocklist("/blocklist1.txt");
blocklistManager.loadBlocklist("/blocklist2.txt");
```

## Differences from Original Pi-hole

### What's Included ✅
- DNS server with ad blocking
- Web interface for management
- Customizable blocklists
- Real-time statistics
- Subdomain blocking

### What's Not Included ❌
- DHCP server (use your router's DHCP)
- FTL database (simplified in-memory stats)
- Gravity list updates (manual blocklist management)
- Query log history (memory limitations)
- User authentication (simplified for ESP32)
- Regex blocking patterns
- Multiple clients tracking
- Long-term statistics storage

### Why These Limitations?
ESP32 has limited resources compared to Raspberry Pi:
- **RAM**: 320KB vs 1-8GB
- **Storage**: 4MB flash vs 8-64GB SD card
- **Processing**: Single/dual core @ 240MHz vs quad-core @ 1.5GHz

The ESP32 version focuses on core DNS blocking functionality while maintaining stability on constrained hardware.

## Development

### Project Structure
```
pi-hole-esp32/
├── platformio.ini          # PlatformIO configuration
├── include/
│   ├── config.h           # Configuration settings
│   ├── DNSServer.h        # DNS server header
│   ├── BlocklistManager.h # Blocklist management header
│   └── WebServer.h        # Web server header
├── src/
│   ├── main.cpp           # Main application
│   ├── DNSServer.cpp      # DNS server implementation
│   ├── BlocklistManager.cpp # Blocklist management
│   └── WebServer.cpp      # Web server implementation
├── data/
│   └── blocklist.txt      # Sample blocklist
└── ESP32_README.md        # This file
```

### Building from Source
```bash
# Install dependencies
pio lib install

# Build only
pio run

# Build and upload
pio run --target upload

# Upload filesystem
pio run --target uploadfs

# Monitor serial output
pio device monitor
```

### Contributing
Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly on real hardware
5. Submit a pull request

## License

This project inherits the license from the original Pi-hole project (EUPL-1.2).

## Credits

- Original Pi-hole project: https://pi-hole.net/
- ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
- ESPAsyncWebServer: https://github.com/me-no-dev/ESPAsyncWebServer

## Support

For issues and questions:
- GitHub Issues: https://github.com/Gurawa/pi-hole-esp32/issues
- Original Pi-hole: https://discourse.pi-hole.net/

## Disclaimer

This ESP32 implementation is a lightweight alternative to the full Pi-hole system. It provides basic ad-blocking functionality but does not include all features of the original Pi-hole. For full Pi-hole functionality, use the official Pi-hole on a Raspberry Pi or Linux system.
