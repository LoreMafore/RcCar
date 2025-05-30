#include <esp_now.h>
#include <WiFi.h>

#define u8 uint8_t
#define f32 float

//Front wheels
#define LINT3 18
#define LINT4 19
#define RINT1 17
#define RINT2 16

//Back wheels
#define RINT3 12
#define RINT4 13

#define LINT1 19
#define LINT2 18


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


  pinMode(RINT1, OUTPUT);
  pinMode(RINT2, OUTPUT);
  pinMode(RINT3, OUTPUT);
  pinMode(RINT4, OUTPUT);

  pinMode(LINT1, OUTPUT);
  pinMode(LINT2, OUTPUT);
  pinMode(LINT3, OUTPUT);
  pinMode(LINT4, OUTPUT);

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
        analogWrite(RINT2, 0);
        analogWrite(RINT1, 125);
        analogWrite(RINT4, 0);
        analogWrite(RINT3, 225);
      }

      else if(Data.valueY == 0)
      {
        analogWrite(RINT1, 0);
        analogWrite(RINT2, 0);
        analogWrite(RINT3, 0);
        analogWrite(RINT4, 0);

      }

      else if(Data.valueY == 1)
      {

        analogWrite(RINT1, 0);
        analogWrite(RINT2, 125);
        analogWrite(RINT3, 0);
        analogWrite(RINT4, 125);

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
        analogWrite(RINT2, 0);
        analogWrite(RINT1, 125);

        analogWrite(RINT4, 0);
        analogWrite(RINT3, 125);

        analogWrite(LINT2, 0);
        analogWrite(LINT1, 130);

        analogWrite(LINT4, 0);
        analogWrite(LINT3, 130);

      }

      else if(Data.valueY == 0)
      {
        analogWrite(RINT1, 0);
        analogWrite(RINT2, 0);

        analogWrite(RINT3, 0);
        analogWrite(RINT4, 0);

        analogWrite(LINT1, 0);
        analogWrite(LINT2, 0);

        analogWrite(LINT3, 0);
        analogWrite(LINT4, 0);

      }

      else if(Data.valueY == 1)
      {

        analogWrite(RINT1, 0);
        analogWrite(RINT2, 125);

        analogWrite(RINT3, 0);
        analogWrite(RINT4, 125);

        analogWrite(LINT1, 0);
        analogWrite(LINT2, 125);

        analogWrite(LINT3, 0);
        analogWrite(LINT4, 125);


      }

      if(Data.valueX == 2 && Data.valueY == 0)
      {
        analogWrite(RINT4, 0);
        analogWrite(RINT3, 125);

        analogWrite(LINT4, 0);
        analogWrite(LINT3, 125);

        analogWrite(RINT1, 0);
        analogWrite(RINT2, 125);

        analogWrite(LINT1, 0);
        analogWrite(LINT2, 125);
      }

      else if(Data.valueX == 0)
      {
        analogWrite(RINT1, 0);
        analogWrite(RINT2, 0);

        analogWrite(RINT3, 0);
        analogWrite(RINT4, 0);

        analogWrite(LINT1, 0);
        analogWrite(LINT2, 0);

        analogWrite(LINT3, 0);
        analogWrite(LINT4, 0);

      }

      else if(Data.valueX == 1)
      {
        analogWrite(RINT2, 0);
        analogWrite(RINT1, 125);

        analogWrite(LINT1, 0);
        analogWrite(LINT2, 125);

        analogWrite(RINT3, 0);
        analogWrite(RINT4, 125);

        analogWrite(LINT3, 0);
        analogWrite(LINT4, 125);
       

      }
   }

}
