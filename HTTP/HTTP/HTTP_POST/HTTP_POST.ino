#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverName = "http://jsonplaceholder.typicode.com/posts";

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

    // Specify content type header for JSON
    http.addHeader("Content-Type", "application/json");

    // Construct packet payload with your custom message
    String jsonPayload = "{\"message\":\"hello esp 32\"}";

    Serial.println("\n[1] --- Sending Data ---");
    Serial.println(jsonPayload);

    // Send the POST request
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      Serial.print("\nHTTP Response Code: ");
      Serial.println(httpResponseCode); // Expect 201 Created

      String response = http.getString();
      Serial.println("\n[2] --- Data Received Back from Server ---");
      Serial.println(response);
    } else {
      Serial.print("POST failed, error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}

void loop() {
  // Empty
}
