#include <WiFi.h>
#include <WebServer.h>
#include "network_config.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

WebServer server(80); // Server on port 80

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP()); // This line prints the IP address

  server.on("/", handleRoot); // Define endpoint
  server.begin();
}

void handleRoot() {
  String html = "<html><body><h1>Data from ESP32</h1>";
  html += "<p>Sample Data: " + String(testData()) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void loop() {
  server.handleClient();
}

int testData() {
  return 8; // Example: read analog value
}
