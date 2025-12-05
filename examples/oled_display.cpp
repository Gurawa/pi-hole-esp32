/**
 * Pi-hole ESP32 Client with OLED Display
 * 
 * This example shows Pi-hole statistics on a 128x64 OLED display using SSD1306 driver.
 * 
 * Hardware Requirements:
 * - ESP32 board
 * - SSD1306 OLED display (128x64)
 * - I2C connection (default pins: SDA=21, SCL=22 on ESP32)
 * 
 * Wiring:
 * - OLED VCC -> 3.3V
 * - OLED GND -> GND
 * - OLED SCL -> GPIO 22 (default I2C clock)
 * - OLED SDA -> GPIO 21 (default I2C data)
 * 
 * PlatformIO Dependencies (add to platformio.ini):
 * lib_deps = 
 *     bblanchon/ArduinoJson@^6.21.3
 *     adafruit/Adafruit SSD1306@^2.5.7
 *     adafruit/Adafruit GFX Library@^1.11.9
 * 
 * Instructions:
 * 1. Add the above libraries to your platformio.ini
 * 2. Wire up the OLED display as shown above
 * 3. Copy this file to src/main.cpp
 * 4. Configure config.h with your settings
 * 5. Upload to your ESP32
 */

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Include configuration file
#include "config.h"

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin (-1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // Common I2C address for SSD1306

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pi-hole statistics structure
struct PiHoleStats {
    long domains_being_blocked;
    long dns_queries_today;
    long ads_blocked_today;
    float ads_percentage_today;
    String status;
};

PiHoleStats currentStats;
unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 30000; // Update every 30 seconds

// Function declarations
String formatNumber(long num);

/**
 * Initialize OLED display
 */
void initDisplay() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Pi-hole ESP32"));
    display.println(F("Initializing..."));
    display.display();
}

/**
 * Display status message
 */
void displayMessage(const char* line1, const char* line2 = "", const char* line3 = "") {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(line1);
    if (strlen(line2) > 0) display.println(line2);
    if (strlen(line3) > 0) display.println(line3);
    display.display();
}

/**
 * Connect to WiFi network
 */
void connectWiFi() {
    Serial.println("Connecting to WiFi...");
    displayMessage("Connecting to", WIFI_SSID, "Please wait...");
    
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        
        displayMessage("WiFi Connected!", WiFi.localIP().toString().c_str());
        delay(2000);
    } else {
        Serial.println("\nFailed to connect to WiFi");
        displayMessage("WiFi Failed", "Check settings", "Retrying...");
        delay(3000);
    }
}

/**
 * Fetch statistics from Pi-hole API
 */
bool fetchPiHoleStats() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected");
        return false;
    }
    
    HTTPClient http;
    String url = String("http://") + PIHOLE_SERVER + "/admin/api.php?summary";
    
    #ifdef PIHOLE_API_KEY
    if (strlen(PIHOLE_API_KEY) > 0) {
        url += String("&auth=") + PIHOLE_API_KEY;
    }
    #endif
    
    Serial.print("Fetching from: ");
    Serial.println(url);
    
    http.begin(url);
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, payload);
        
        if (error) {
            Serial.print("JSON parsing failed: ");
            Serial.println(error.c_str());
            http.end();
            return false;
        }
        
        currentStats.domains_being_blocked = doc["domains_being_blocked"] | 0;
        currentStats.dns_queries_today = doc["dns_queries_today"] | 0;
        currentStats.ads_blocked_today = doc["ads_blocked_today"] | 0;
        currentStats.ads_percentage_today = doc["ads_percentage_today"] | 0.0;
        currentStats.status = doc["status"] | "unknown";
        
        http.end();
        return true;
    } else {
        Serial.print("HTTP request failed, error: ");
        Serial.println(httpCode);
        http.end();
        return false;
    }
}

/**
 * Display Pi-hole statistics on OLED
 */
void displayStats() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    // Title
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("Pi-hole: ");
    display.println(currentStats.status);
    
    // Draw separator line
    display.drawLine(0, 10, SCREEN_WIDTH, 10, SSD1306_WHITE);
    
    // Statistics
    display.setCursor(0, 14);
    display.print("Blocked: ");
    display.println(formatNumber(currentStats.domains_being_blocked));
    
    display.setCursor(0, 24);
    display.print("Queries: ");
    display.println(formatNumber(currentStats.dns_queries_today));
    
    display.setCursor(0, 34);
    display.print("Ads: ");
    display.println(formatNumber(currentStats.ads_blocked_today));
    
    // Large percentage at bottom
    display.setTextSize(2);
    display.setCursor(0, 46);
    display.print(currentStats.ads_percentage_today, 1);
    display.print("%");
    
    display.display();
    
    // Also print to serial
    Serial.println("\n==== Pi-hole Statistics ====");
    Serial.print("Status: ");
    Serial.println(currentStats.status);
    Serial.print("Domains Blocked: ");
    Serial.println(currentStats.domains_being_blocked);
    Serial.print("DNS Queries Today: ");
    Serial.println(currentStats.dns_queries_today);
    Serial.print("Ads Blocked Today: ");
    Serial.println(currentStats.ads_blocked_today);
    Serial.print("Ads Percentage: ");
    Serial.print(currentStats.ads_percentage_today);
    Serial.println("%");
    Serial.println("============================\n");
}

/**
 * Format large numbers with K/M suffix
 */
String formatNumber(long num) {
    if (num >= 1000000) {
        return String(num / 1000000.0, 1) + "M";
    } else if (num >= 1000) {
        return String(num / 1000.0, 1) + "K";
    }
    return String(num);
}

/**
 * Setup function - runs once at startup
 */
void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n\n==================================");
    Serial.println("Pi-hole ESP32 Client with OLED");
    Serial.println("==================================\n");
    
    // Initialize OLED display
    initDisplay();
    delay(2000);
    
    // Connect to WiFi
    connectWiFi();
    
    // Fetch initial statistics
    if (WiFi.status() == WL_CONNECTED) {
        displayMessage("Fetching stats", "from Pi-hole...");
        Serial.println("Fetching initial Pi-hole statistics...");
        
        if (fetchPiHoleStats()) {
            displayStats();
        } else {
            displayMessage("Error fetching", "Pi-hole stats", "Check config");
        }
    }
}

/**
 * Main loop - runs continuously
 */
void loop() {
    // Check WiFi connection
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi disconnected, reconnecting...");
        displayMessage("WiFi Lost", "Reconnecting...");
        connectWiFi();
    }
    
    // Update statistics periodically
    unsigned long currentMillis = millis();
    if (currentMillis - lastUpdate >= UPDATE_INTERVAL) {
        lastUpdate = currentMillis;
        
        Serial.println("Updating Pi-hole statistics...");
        if (fetchPiHoleStats()) {
            displayStats();
        } else {
            displayMessage("Update Failed", "Retrying soon...");
        }
    }
    
    delay(1000);
}
