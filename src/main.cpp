/**
 * Pi-hole ESP32 Client
 * 
 * This ESP32 client connects to a Pi-hole server and fetches statistics
 * via the Pi-hole API. It can be used to display Pi-hole stats on an
 * OLED/TFT display or for monitoring purposes.
 * 
 * Features:
 * - WiFi connectivity
 * - Pi-hole API integration
 * - Statistics fetching (queries blocked, total queries, etc.)
 * - JSON parsing of API responses
 * 
 * Configuration:
 * - Copy config.example.h to config.h
 * - Update WiFi credentials and Pi-hole server details
 */

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Include configuration file
#include "config.h"

// Pi-hole statistics structure
struct PiHoleStats {
    long domains_being_blocked;
    long dns_queries_today;
    long ads_blocked_today;
    float ads_percentage_today;
    long unique_domains;
    long queries_forwarded;
    long queries_cached;
    long unique_clients;
    String status;
};

PiHoleStats currentStats;
unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 30000; // Update every 30 seconds

/**
 * Connect to WiFi network
 */
void connectWiFi() {
    Serial.println("Connecting to WiFi...");
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
    } else {
        Serial.println("\nFailed to connect to WiFi");
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
    
    // Add API key if configured
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
        
        // Parse JSON response
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, payload);
        
        if (error) {
            Serial.print("JSON parsing failed: ");
            Serial.println(error.c_str());
            http.end();
            return false;
        }
        
        // Extract statistics
        currentStats.domains_being_blocked = doc["domains_being_blocked"] | 0;
        currentStats.dns_queries_today = doc["dns_queries_today"] | 0;
        currentStats.ads_blocked_today = doc["ads_blocked_today"] | 0;
        currentStats.ads_percentage_today = doc["ads_percentage_today"] | 0.0;
        currentStats.unique_domains = doc["unique_domains"] | 0;
        currentStats.queries_forwarded = doc["queries_forwarded"] | 0;
        currentStats.queries_cached = doc["queries_cached"] | 0;
        currentStats.unique_clients = doc["unique_clients"] | 0;
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
 * Display current statistics on Serial Monitor
 */
void displayStats() {
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
    Serial.print("Unique Domains: ");
    Serial.println(currentStats.unique_domains);
    Serial.print("Queries Forwarded: ");
    Serial.println(currentStats.queries_forwarded);
    Serial.print("Queries Cached: ");
    Serial.println(currentStats.queries_cached);
    Serial.print("Unique Clients: ");
    Serial.println(currentStats.unique_clients);
    Serial.println("============================\n");
}

/**
 * Setup function - runs once at startup
 */
void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n\n==================================");
    Serial.println("Pi-hole ESP32 Client");
    Serial.println("==================================\n");
    
    // Connect to WiFi
    connectWiFi();
    
    // Fetch initial statistics
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Fetching initial Pi-hole statistics...");
        if (fetchPiHoleStats()) {
            displayStats();
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
        connectWiFi();
    }
    
    // Update statistics periodically
    unsigned long currentMillis = millis();
    if (currentMillis - lastUpdate >= UPDATE_INTERVAL) {
        lastUpdate = currentMillis;
        
        Serial.println("Updating Pi-hole statistics...");
        if (fetchPiHoleStats()) {
            displayStats();
        }
    }
    
    delay(1000); // Small delay to prevent excessive CPU usage
}
