#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h> // Required to set the Wi-Fi channel in Core 2.x

#define LED_PIN 2

volatile bool newDataReceived = false;
char receiveBuffer[250]; 
volatile int receiveLength = 0;

// Correct signature for ESP32 Core 2.x
void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {
  int copyLen = (len < 249) ? len : 249; 
  memcpy(receiveBuffer, data, copyLen);
  receiveBuffer[copyLen] = '\0'; 
  receiveLength = copyLen;
  
  newDataReceived = true; 
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);
  
  // Correct way to set the Wi-Fi channel in Core 2.x
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_register_recv_cb(onReceive);

  Serial.println("ESP-NOW Receiver Ready");
}

void loop() {
  if (newDataReceived) {
    newDataReceived = false; 

    Serial.print("Received: ");
    Serial.println(receiveBuffer);

    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
  }
}