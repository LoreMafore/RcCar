#include <esp_now.h>
#include <WiFi.h>

#define u8 uint8_t
#define f32 float

//pins
#define INT1 22
#define INT2 23
#define INT3 34
#define INT4 35

f32 x = 0.0f;
f32 y = 0.0f;

uint8_t carAddress[] = {0xCC, 0xDB, 0xA7, 0x9A, 0xD8, 0x34};

typedef struct message
{
  char a[32];
  f32 x;
  f32 y;
  f32 value;

}message;

message Data;

void OnDataRecv(const esp_now_recv_info *info, const u8 *incomingData, int len)
{
  memcpy(&Data, incomingData, sizeof(Data));
  Serial.println("Data recieved: ");
  Serial.println(len);
  Serial.println("Character Value: ");
  Serial.println(Data.a);
  Serial.println("Y: ");
  Serial.println(Data.y);
  Serial.println("X: ");
  Serial.println(Data.x);
  Serial.println("Value: ");
  Serial.println(Data.value);

}

void setup()
{
  Serial.begin(115200);

  pinMode(INT1, OUTPUT);
  pinMode(INT2, OUTPUT);

  WiFi.mode(WIFI_STA);

  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error Inializing");
    return;
  }
  
  //registers the function for whenever the data is being recieved
  esp_now_register_recv_cb(OnDataRecv);
  
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, carAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

}

void loop()
{

  if(Data.value == 2)
  {

    digitalWrite(INT1, HIGH);
    digitalWrite(INT2, LOW);
    digitalWrite(INT3, HIGH);
    digitalWrite(INT4, LOW);


  }

  else if(Data.value == 0)
  {
    digitalWrite(INT1, LOW);
    digitalWrite(INT2, LOW);
    digitalWrite(INT3, LOW;
    digitalWrite(INT4, LOW);

  }

  else if(Data.value == 1)
  {

    digitalWrite(INT1, LOW);
    digitalWrite(INT2, HIGH);
    digitalWrite(INT3, LOW;
    digitalWrite(INT4, HIGH);

  }

}
