#include <WiFi.h>
// Replace with your 2.4 GHz Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
// Initialize TCP Server on Port 8080
WiFiServer server(8080);
void setup() {
Serial.begin(115200);
// Connect to local Wi-Fi network
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("\nWiFi connected.");
Serial.print("ESP32 IP Address: ");
Serial.println(WiFi.localIP());
// Start listening for TCP clients
server.begin();
}
void loop() {
WiFiClient client = server.available(); // Check for incoming connection
if (client) {
Serial.println("New client connected!");
while (client.connected()) {
if (client.available()) {

String incomingData = client.readStringUntil('\n');
Serial.print("Received: ");
Serial.println(incomingData);
// Echo data back over TCP
client.println("ESP32 Echo: " + incomingData);
}
}
client.stop();
Serial.println("Client disconnected.");
}
}