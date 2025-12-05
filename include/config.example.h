/**
 * Configuration file for Pi-hole ESP32 Client
 * 
 * INSTRUCTIONS:
 * 1. Copy this file to config.h
 * 2. Update the values below with your settings
 * 3. Keep config.h private (it's in .gitignore)
 */

#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// Pi-hole Server Configuration
// Use IP address or hostname (without http://)
// Example: "192.168.1.100" or "pi.hole"
#define PIHOLE_SERVER "192.168.1.100"

// Pi-hole API Key (optional)
// Leave empty "" if your Pi-hole doesn't require authentication
// for basic statistics. Get your API key from Pi-hole admin panel:
// Settings -> API -> Show API token
#define PIHOLE_API_KEY ""

// Update interval in milliseconds (default: 30000 = 30 seconds)
// #define UPDATE_INTERVAL 30000

#endif // CONFIG_H
