#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h> // Required to set the Wi-Fi channel in Core 2.x

#define LED_PIN 2

// Replace this with the receiver's actual MAC address
uint8_t receiver[] = {
  0x14, 0x08, 0x08,
  0xA4, 0x61, 0xA0
};

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);
  
  // Correct way to set the Wi-Fi channel in Core 2.x
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW INIT FAILED");
    return;
  }

  esp_now_peer_info_t peerInfo = {};

  memcpy(peerInfo.peer_addr, receiver, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("PEER ADD FAILED");
    return;
  }

  Serial.println("Unicast Sender Ready");
}

void loop() {
  const char *message = "Hello from ESP32-A";

  esp_err_t result = esp_now_send(
    receiver,
    (uint8_t *)message,
    strlen(message)
  );

  if (result == ESP_OK) {
    Serial.println("Message sent");

    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("Send failed");
  }

  delay(2000);
}