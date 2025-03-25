#include <esp_now.h>
#include <WiFi.h>

#define u8 uint8_t
#define f32 float

//pins
#define PINX 33
#define PINY 32
#define PINB 26

f32 x = 0.0f;
f32 y = 0.0f;
f32 sendingValue = 0;
int buttonStuff = 0;
int buttonStatus = 0;


//uint8_t controllerAddress[] = {0x88, 0x13, 0xBF, 0xC8, 0x36, 0x68};
//uint8_t carAddress[] =        {0xCC, 0xDB, 0xA7, 0x9A, 0xD8, 0x34}; //2
uint8_t carAddress[] =        {0xCC, 0xDB, 0xA7, 0x9A, 0xAA, 0xD8}; //3

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
  pinMode(PINB, INPUT_PULLUP);

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
  buttonStuff = digitalRead(PINB);

  if(buttonStuff == 0)
  {

    if(buttonStatus == 0)
    {
      buttonStatus = 1;
      Data.button = buttonStatus;
    }

    else if(buttonStatus == 1)
    {
      buttonStatus = 0;
      Data.button = buttonStatus;
    }

  }
  buttonStuff = digitalRead(PINB);

  Serial.println(buttonStuff);

  if(y >= 0 && y <= 1365)
  {
    Data.y = y;
    strcpy(Data.a, "Back.");
    Data.valueY = 1;
  }

  else if(y >= 1366 && y <= 2730)
  {
    Data.y = y;
    strcpy(Data.a, "Stop.");
    Data.valueY = 0;
  }

  else if(y >= 2731 and y <= 4096)
  {
    Data.y = y;
    strcpy(Data.a, "Forward.");
    Data.valueY = 2;
  }

  if(x >= 0 && x <= 1365)
  {
    Data.x = x;
    strcpy(Data.a, "Left.");
    Data.valueX = 1;
  }

  else if(x >= 1366 && x <= 2730)
  {
    Data.x = x;
    strcpy(Data.a, "Stop.");
    Data.valueX = 0;
  }

  else if(x >= 2731 and x <= 4096)
  {
    Data.x = x;
    strcpy(Data.a, "Right.");
    Data.valueX = 2;
  }

  esp_err_t result = esp_now_send(carAddress, (u8 *) &Data, sizeof(Data));

  if(result == ESP_OK)
  {
    Serial.println("Sending Confirmed");
    Serial.println("Y: ");
    Serial.println(y);
    Serial.println("X: ");
    Serial.println(x);
    Serial.println("Button: ");
    Serial.print(buttonStatus);
  }

  else
  {
    Serial.println("Sending Error");
    Serial.println("Y: ");
    Serial.println(y);
    Serial.println("X: ");
    Serial.println(x);
    Serial.println("Button: ");
 
    
  }
  delay(1000);
}


