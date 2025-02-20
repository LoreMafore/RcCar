#include <esp_now.h>
#include <WiFi.h>

#define u8 uint8_t
#define f32 float

//pins
#define BINT1 25
#define BINT2 26
#define BINT3 12
#define BINT4 13

#define FINT1 19
#define FINT2 18
#define FINT3 17
#define FINT4 16

#define SINT1 32
#define SINT2 33

f32 x = 0.0f;
f32 y = 0.0f;

uint8_t carAddress[] = {0xCC, 0xDB, 0xA7, 0x9A, 0xD8, 0x34};

typedef struct message
{
  char a[32];
  char b[32];
  f32 x;
  f32 y;
  f32 valueY;
  f32 valueX;
  int button;

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
  Serial.println(Data.valueY);
  Serial.println("Value: ");
  Serial.println(Data.valueX);

}

void setup()
{
  Serial.begin(115200);

  pinMode(BINT1, OUTPUT);
  pinMode(BINT2, OUTPUT);
  pinMode(BINT3, OUTPUT);
  pinMode(BINT4, OUTPUT);

  pinMode(FINT1, OUTPUT);
  pinMode(FINT2, OUTPUT);
  pinMode(FINT3, OUTPUT);
  pinMode(FINT4, OUTPUT);

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

  if(Data.button == 0)
  {
      if(Data.valueY == 2)
      {
        analogWrite(BINT2, 0);
        analogWrite(BINT1, 125);
        analogWrite(BINT4, 0);
        analogWrite(BINT3, 225);
      }

      else if(Data.valueY == 0)
      {
        analogWrite(BINT1, 0);
        analogWrite(BINT2, 0);
        analogWrite(BINT3, 0);
        analogWrite(BINT4, 0);

      }

      else if(Data.valueY == 1)
      {

        analogWrite(BINT1, 0);
        analogWrite(BINT2, 125);
        analogWrite(BINT3, 0);
        analogWrite(BINT4, 125);

      }

       if(Data.valueX == 2)
      {
        analogWrite(SINT2, 0);
        analogWrite(SINT1, 125);

      }

      else if(Data.valueX == 0)
      {
        analogWrite(SINT1, 0);
        analogWrite(SINT2, 0);

      }

      else if(Data.valueX == 1)
      {

        analogWrite(SINT1, 0);
        analogWrite(SINT2, 125);

      }
  }

   if(Data.button == 1)
   {
      if(Data.valueY == 2)
      {
        analogWrite(BINT2, 0);
        analogWrite(BINT1, 125);

        analogWrite(BINT4, 0);
        analogWrite(BINT3, 125);

        analogWrite(FINT2, 0);
        analogWrite(FINT1, 130);

        analogWrite(FINT4, 0);
        analogWrite(FINT3, 130);

      }

      else if(Data.valueY == 0)
      {
        analogWrite(BINT1, 0);
        analogWrite(BINT2, 0);

        analogWrite(BINT3, 0);
        analogWrite(BINT4, 0);

        analogWrite(FINT1, 0);
        analogWrite(FINT2, 0);

        analogWrite(FINT3, 0);
        analogWrite(FINT4, 0);

      }

      else if(Data.valueY == 1)
      {

        analogWrite(BINT1, 0);
        analogWrite(BINT2, 125);

        analogWrite(BINT3, 0);
        analogWrite(BINT4, 125);

        analogWrite(FINT1, 0);
        analogWrite(FINT2, 125);

        analogWrite(FINT3, 0);
        analogWrite(FINT4, 125);


      }

      if(Data.valueX == 2 && Data.valueY == 0)
      {
        analogWrite(BINT4, 0);
        analogWrite(BINT3, 125);

        analogWrite(FINT4, 0);
        analogWrite(FINT3, 125);

        analogWrite(BINT1, 0);
        analogWrite(BINT2, 125);

        analogWrite(FINT1, 0);
        analogWrite(FINT2, 125);
      }

      else if(Data.valueX == 0)
      {
        analogWrite(BINT1, 0);
        analogWrite(BINT2, 0);

        analogWrite(BINT3, 0);
        analogWrite(BINT4, 0);

        analogWrite(FINT1, 0);
        analogWrite(FINT2, 0);

        analogWrite(FINT3, 0);
        analogWrite(FINT4, 0);

      }

      else if(Data.valueX == 1)
      {
        analogWrite(BINT2, 0);
        analogWrite(BINT1, 125);

        analogWrite(FINT1, 0);
        analogWrite(FINT2, 125);

        analogWrite(BINT3, 0);
        analogWrite(BINT4, 125);

        analogWrite(FINT3, 0);
        analogWrite(FINT4, 125);
       

      }
   }

}
