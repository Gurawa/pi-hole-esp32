#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "DNSServer.h"
#include "BlocklistManager.h"

class PiHoleWebServer {
public:
    PiHoleWebServer(DNSServer* dns, BlocklistManager* blocklist);
    bool begin(uint16_t port);
    void handleClient();
    
private:
    AsyncWebServer* server;
    DNSServer* dnsServer;
    BlocklistManager* blocklistManager;
    
    // Web page handlers
    void handleRoot(AsyncWebServerRequest* request);
    void handleStats(AsyncWebServerRequest* request);
    void handleBlocklist(AsyncWebServerRequest* request);
    void handleAddDomain(AsyncWebServerRequest* request);
    void handleRemoveDomain(AsyncWebServerRequest* request);
    void handleResetStats(AsyncWebServerRequest* request);
    
    // Helper methods
    String getStatsJSON();
    String getBlocklistJSON();
    String getHTMLHeader();
    String getHTMLFooter();
    bool authenticate(AsyncWebServerRequest* request);
};

#endif // WEB_SERVER_H
