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
#define LINT1 26
#define LINT2 25


f32 x = 0.0f;
f32 y = 0.0f;

u8 y_speed = 255;
u8 x_speed = 125;


//uint8_t carAddress[] = {0xCC, 0xDB, 0xA7, 0x9A, 0xD8, 0x34}; //2
//uint8_t controllerAddress[] = {0xCC, 0xDB, 0xA7, 0x9A, 0xAA, 0xD8}; //3
uint8_t carAddress[] = {0x88, 0x13, 0xBF, 0xC8, 0x33, 0x40}; //944331

typedef struct message
{
  char a[32];
  char b[32];
  f32 x;
  f32 y;
  f32 valueY;
  f32 valueX;
  bool switchY;
  bool switchX;
}message;

message Data;

void OnDataRecv(const esp_now_recv_info *info, const u8 *incomingData, int len)
{
  memcpy(&Data, incomingData, sizeof(Data));
  Serial.println("Data recieved: ");
  Serial.print("Length: ");
  Serial.println(len);
  Serial.print("Character Value: ");
  Serial.println(Data.a);
  Serial.print("Y: ");
  Serial.println(Data.y);
  Serial.print("X: ");
  Serial.println(Data.x);
  Serial.print("ValueY: ");
  Serial.println(Data.valueY);
  Serial.print("ValueX: ");
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

  analogWrite(RINT1, 0);
  analogWrite(RINT2, 0);
  analogWrite(RINT3, 0);
  analogWrite(RINT4, 0);
  analogWrite(LINT1, 0);
  analogWrite(LINT2, 0);
  analogWrite(LINT3, 0);
  analogWrite(LINT4, 0);

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

  WiFi.begin();

}

void loop()
{


  // if(esp_now_init() == ESP_OK)
  // {
  //   Serial.println("Sending Confirmed");
  //   Serial.println("Y: ");
  //   Serial.println(y);
  //   Serial.println("X: ");
  //   Serial.println(x);
  //   Serial.println("Button: ");
  //   Serial.print(button);
  // }

  // else
  // {
  //   Serial.println("Sending Error");
  //   Serial.println("Y: ");
  //   Serial.println(y);
  //   Serial.println("X: ");
  //   Serial.println(x);
  //   Serial.println("Button: ");
 
    
  // }
      if(Data.switchY == true)
      {
        y_speed = 255;
      }
      else
      {
        y_speed = 125;
      }

      if(Data.switchX == true)
      {
        x_speed = 125;
      }
      else
      {
        x_speed = 60;
      }

      if(Data.valueY == 2 && Data.valueX ==0)
      {
        analogWrite(RINT1, 0);
        analogWrite(RINT2, y_speed);

        analogWrite(RINT4, 0);
        analogWrite(RINT3, y_speed);

        analogWrite(LINT2, 0);
        analogWrite(LINT1, y_speed);

        analogWrite(LINT3, 0);
        analogWrite(LINT4, y_speed);

      }

      else if(Data.valueY == 0 && Data.valueX ==0)
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

      else if(Data.valueY == 1 && Data.valueX ==0)
      {

        analogWrite(RINT2, 0);
        analogWrite(RINT1, y_speed);

        analogWrite(RINT3, 0);
        analogWrite(RINT4, y_speed);

        analogWrite(LINT1, 0);
        analogWrite(LINT2, y_speed);

        analogWrite(LINT4, 0);
        analogWrite(LINT3, y_speed);


      }

      if(Data.valueY == 0 && Data.valueX == 2)
      {
        analogWrite(LINT1, 0);
        analogWrite(LINT2, x_speed);

        analogWrite(LINT4, 0);
        analogWrite(LINT3, x_speed);

        analogWrite(RINT1, 0);
        analogWrite(RINT2, x_speed);

        analogWrite(RINT4, 0);
        analogWrite(RINT3, x_speed);
      }

      else if(Data.valueY == 0 && Data.valueX == 1)
      {
        analogWrite(LINT2, 0);
        analogWrite(LINT1, x_speed);

        analogWrite(LINT3, 0);
        analogWrite(LINT4, x_speed);

        analogWrite(RINT2, 0);
        analogWrite(RINT1, x_speed);

        analogWrite(RINT3, 0);
        analogWrite(RINT4, x_speed);
      }

      delay(10);

}
