#include <WiFi.h>          // Built-in ESP32 Wi-Fi library
#include <PubSubClient.h>  // MQTT library for sending/receiving messages

// 1. Network Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// 2. Public MQTT Broker Address
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

// Triggered automatically whenever a message arrives from the broker
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // Configure MQTT Server (Port 1883 is standard unencrypted MQTT)
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Generate a unique client ID for this session
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected!");
      // Subscribe to receive incoming messages on this topic
      client.subscribe("esp32/trial/in");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Keeps the MQTT connection alive and checks for incoming data

  // Publish a status message every 5 seconds (5000ms)
  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    client.publish("esp32/trial/out", "Hello from ESP32!");
  }
}
