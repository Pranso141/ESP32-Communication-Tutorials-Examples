#include <WiFi.h>
#include <WiFiUdp.h>
// ====================================================
// REPLACE WITH YOUR ACTUAL WI-FI NETWORK CREDENTIALS
// ====================================================
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
WiFiUDP udp;
const unsigned int localPort = 4210; // Port to listen for UDP packets
char packetBuffer[255];
void setup() {
Serial.begin(115200);
// Connect to Wi-Fi
Serial.print("Connecting to Wi-Fi");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("\nWiFi Connected!");
Serial.print("ESP32 IP Address: ");
Serial.println(WiFi.localIP());
// Start listening on the assigned UDP port
udp.begin(localPort);
Serial.printf("Listening for UDP packets on port %d\n", localPort);
}
void loop() {
// Check if a packet has arrived

int packetSize = udp.parsePacket();
if (packetSize) {
Serial.printf("\nReceived %d bytes from %s:%d\n",
packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());
// Read the packet payload into the buffer
int len = udp.read(packetBuffer, 255);
if (len > 0) {
packetBuffer[len] = 0; // Null-terminate to convert raw bytes into string
}
Serial.printf("Payload: %s\n", packetBuffer);
// Send an echo response back to the sender
udp.beginPacket(udp.remoteIP(), udp.remotePort());
udp.print("ESP32 Echo: ");
udp.print(packetBuffer);
udp.endPacket();
}
}