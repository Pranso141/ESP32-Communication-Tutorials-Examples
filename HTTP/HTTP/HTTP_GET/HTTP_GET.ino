#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverName = "http://ip-api.com/json";

void setup() {
  Serial.begin(115200);
  delay(2000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.setUserAgent("ESP32-HTTPClient");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode); // Expect 200 OK

      String payload = http.getString();
      Serial.println("\n--- Server Response ---");
      Serial.println(payload);
    } else {
      Serial.print("Request failed, error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}

void loop() {
  // Empty for single run trial
}

