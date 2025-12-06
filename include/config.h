#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

// DNS Server Configuration
#define DNS_PORT 53
#define UPSTREAM_DNS_IP "8.8.8.8"  // Google DNS as default upstream
#define UPSTREAM_DNS_PORT 53

// Web Server Configuration
#define WEB_SERVER_PORT 80
#define WEB_PASSWORD "admin"  // Default password for web interface

// DNS Cache Configuration
#define DNS_CACHE_SIZE 50
#define DNS_CACHE_TTL 300  // 5 minutes in seconds

// Blocklist Configuration
#define MAX_BLOCKLIST_ENTRIES 1000
#define BLOCKLIST_FILE "/blocklist.txt"

// Statistics Configuration
#define STATS_RESET_HOUR 0  // Reset stats at midnight

// Hostname Configuration
#define DEVICE_HOSTNAME "pihole-esp32"

// Debug Configuration
#define DEBUG_ENABLED true

#endif // CONFIG_H
