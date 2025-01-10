#include <esp_now.h>
#include <WiFi.h>


int controllerAddress{0x88, 0x13, 0xBF, 0xC8, 0x36, 0x68}
int carAddress       {0xCC, 0xdB, 0xA7, 0x9A, 0xD8, 0x34}


void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  esp_now_init()
}

void loop() {
  // put your main code here, to run repeatedly:

}
