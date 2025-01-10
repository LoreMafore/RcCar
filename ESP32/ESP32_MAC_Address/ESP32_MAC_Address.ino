#include <WiFi.h>
#include "esp_wifi.h"


void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  Serial.begin(115200);
  delay(1000);
  Serial.print("This ESP32's new Mac Address is:  ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // Your main code
}

