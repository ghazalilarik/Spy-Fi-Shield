#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>

// Wi-Fi Configuration
const char* primarySSID = "Your_WiFi_SSID";        // Replace with your Wi-Fi network SSID
const char* primaryPassword = "Your_WiFi_Password"; // Replace with your Wi-Fi network password

// Web Server Setup
ESP8266WebServer server(80);

// Device Fingerprinting
const String knownDevices[] = {"AA:BB:CC:DD:EE:FF", "11:22:33:44:55:66"}; // Replace with known MAC addresses
volatile int unauthorizedDevices = 0;

// Attack Detection
volatile int deauthPackets = 0;
const int alertThreshold = 5; // Threshold for triggering alerts
int ledPin = D4;              // LED for alert notifications

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(primarySSID, primaryPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to primary network!");

  // Set up Web Server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started!");

  // Enable Promiscuous Mode for Packet Detection
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
  wifi_set_promiscuous_rx_cb(promiscuousCallback);
}

void promiscuousCallback(uint8_t* buf, uint16_t len) {
  // Detect deauth attack packets
  if (buf[0] == 0xC0) {
    deauthPackets++;
  }

  // Check for unauthorized devices by MAC address
  String mac = String(buf[10], HEX) + ":" + String(buf[11], HEX) + ":" + String(buf[12], HEX) +
               ":" + String(buf[13], HEX) + ":" + String(buf[14], HEX) + ":" + String(buf[15], HEX);

  bool isKnownDevice = false;
  for (String device : knownDevices) {
    if (mac.equalsIgnoreCase(device)) {
      isKnownDevice = true;
      break;
    }
  }

  if (!isKnownDevice) {
    unauthorizedDevices++;
    Serial.println("Unauthorized device detected: " + mac);
  }
}

void handleRoot() {
  String html = "<html><head><title>Wi-Fi Security Monitor</title></head><body>";
  html += "<h1>Wi-Fi Intrusion & Attack Logger</h1>";
  html += "<p>Deauthentication Packets Detected: " + String(deauthPackets) + "</p>";
  html += "<p>Unauthorized Devices Detected: " + String(unauthorizedDevices) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void sendAlert() {
  Serial.println("Alert: Potential Attack or Unauthorized Access Detected!");
  // Flash LED and reset counters for alerts
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}

void loop() {
  server.handleClient();

  // Check for deauth packets and unauthorized devices
  if (deauthPackets >= alertThreshold || unauthorizedDevices > 0) {
    sendAlert();
    deauthPackets = 0;
    unauthorizedDevices = 0;
  }

  delay(1000); // Check every second
}
