#include <WiFi.h>
#include <WebSocketsServer.h>
// Define network credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
// Initialize WebSocket server on port 81 (standard port is 80 for HTTP, 81 for WS)
WebSocketsServer webSocket = WebSocketsServer(81);
// Variables for sending dummy data
unsigned long lastSendTime = 0;
int counter = 0;

// Callback function to handle WebSocket events
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
switch(type) {
case WStype_DISCONNECTED:
Serial.printf("[%u] Disconnected!\n", num);
break;
case WStype_CONNECTED: {
IPAddress ip = webSocket.remoteIP(num);
Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3],
payload);
// Send a welcome message to the newly connected client
webSocket.sendTXT(num, "Welcome to the ESP32 WebSocket Server!");
break;
}
case WStype_TEXT:
Serial.printf("[%u] Received text: %s\n", num, payload);
// Echo the message back to the specific client
String echoMsg = "ESP32 Echo: " + String((char*)payload);
webSocket.sendTXT(num, echoMsg);
break;
}
}
void setup() {
Serial.begin(115200);
// Connect to Wi-Fi
WiFi.begin(ssid, password);
Serial.print("Connecting to Wi-Fi");
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("\nConnected to Wi-Fi");
Serial.print("ESP32 IP Address: ");
Serial.println(WiFi.localIP());
// Start the WebSocket server and attach the event handler
webSocket.begin();
webSocket.onEvent(webSocketEvent);
Serial.println("WebSocket server started.");
}

void loop() {
// Keep the WebSocket server running and listening for clients
webSocket.loop();
// Send a message to all connected clients every 5 seconds
if (millis() - lastSendTime > 5000) {
lastSendTime = millis();
String broadcastMsg = "Server update #" + String(counter++);
webSocket.broadcastTXT(broadcastMsg);
Serial.println("Broadcasted: " + broadcastMsg);
}
}