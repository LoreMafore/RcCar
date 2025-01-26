#include <esp_now.h>
#include <WiFi.h>

#define u8 uint8_t

int intSentData = 0;
float floatSentData = 0.0f;
bool boolSentData = true;

//uint8_t controllerAddress[] = {0x88, 0x13, 0xBF, 0xC8, 0x36, 0x68};
uint8_t carAddress[] =        {0xCC, 0xDB, 0xA7, 0x9A, 0xD8, 0x34};

typedef struct message
{
  char a[32];
  int b;
  float c;
  bool d;
}message;

message Data;

//Peer information which uses a struct from the esp_now library
esp_now_peer_info_t peerInfo;

void OnDataSent(const u8 *mac_addr, esp_now_send_status_t status)
{
  Serial.printf("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
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

  //registers the function for whenever the data is being sent
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, carAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

  WiFi.begin();
  //esp_now_init()
}

void loop()
{
  intSentData = random(1,20);
  floatSentData = 1.5* intSentData;
  boolSentData = !boolSentData;

  strcpy(Data.a, "Hello Car.");
  Data.b = intSentData;
  Data.c = floatSentData;
  Data.d = boolSentData;

  esp_err_t result = esp_now_send(carAddress, (u8 *) &Data, sizeof(Data));

  if(result == ESP_OK)
  {
    Serial.println("Sending Confirmed");
  }

  else
  {
    Serial.println("Sending Error");
  }
  delay(2000);
}















