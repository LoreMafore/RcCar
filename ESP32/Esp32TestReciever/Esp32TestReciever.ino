#include <esp_now.h>
#include <WiFi.h>

#define u8 uint8_t

int intSentData = 0;
float floatSentData = 0.0f;
bool boolSentData = true;

typedef struct message
{
  char a[32];
  int b;
  float c;
  bool d;
}message;

message Data;

void OnDataRecv(const esp_now_recv_info *info, const u8 *incomingData, int len)
{
  memcpy(&Data, incomingData, sizeof(Data));
  Serial.println("Data recieved: ");
  Serial.println(len);
  Serial.println("Character Value: ");
  Serial.println(Data.a);
  Serial.println("Interger Value: ");
  Serial.println(Data.b);
  Serial.println("Float Value: ");
  Serial.println(Data.c);
  Serial.println("Boolean Value: ");
  Serial.println(Data.d);

}

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error Inializing");
    return;
  }
  
  //registers the function for whenever the data is being recieved
  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {
  // put your main code here, to run repeatedly:

}
