#include <esp_now.h>
#include <WiFi.h>

#define u8 uint8_t
#define f32 float

//pins
#define PINX 33
#define PINY 32

f32 x = 0.0f;
f32 y = 0.0f;
f32 sendingValue = 0;

//uint8_t controllerAddress[] = {0x88, 0x13, 0xBF, 0xC8, 0x36, 0x68};
uint8_t carAddress[] =        {0xCC, 0xDB, 0xA7, 0x9A, 0xD8, 0x34};

typedef struct message
{
  char a[32];
  f32 x;
  f32 y;
  f32 value;
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

  pinMode(PINX, INPUT); 
  pinMode(PINY, INPUT); 

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
  y = analogRead(PINY);
  x = analogRead(PINX);

  if(y >= 0 && y <= 1365)
  {
    Data.y = y;
    strcpy(Data.a, "Back.");
    Data.x = x;
    Data.value = 1;
  }

  else if(y >= 1366 && y <= 2730)
  {
    Data.y = y;
    strcpy(Data.a, "Stop.");
    Data.x = x;
    Data.value = 0;
  }

  else if(y >= 2731 and y <= 4096)
  {
    Data.y = y;
    strcpy(Data.a, "Forward.");
    Data.x = x;
    Data.value = 2;
  }

  esp_err_t result = esp_now_send(carAddress, (u8 *) &Data, sizeof(Data));

  if(result == ESP_OK)
  {
    Serial.println("Sending Confirmed");
    Serial.println("Y: ");
    Serial.print(y);
    Serial.println("X: ");
    Serial.print(x);
  }

  else
  {
    Serial.println("Sending Error");
     Serial.println("Y: ");
    Serial.print(y);
    Serial.println("X: ");
    Serial.print(x);
    
  }
  delay(2000);
}


