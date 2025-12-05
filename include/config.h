/**
 * Default configuration file for Pi-hole ESP32 Client
 * 
 * This is a placeholder configuration file that allows the project
 * to compile. For actual use, copy config.example.h to config.h
 * and update with your actual settings.
 */

#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#ifndef WIFI_SSID
#define WIFI_SSID "your_wifi_ssid"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "your_wifi_password"
#endif

// Pi-hole Server Configuration
#ifndef PIHOLE_SERVER
#define PIHOLE_SERVER "192.168.1.100"
#endif

// Pi-hole API Key (optional)
#ifndef PIHOLE_API_KEY
#define PIHOLE_API_KEY ""
#endif

#endif // CONFIG_H
