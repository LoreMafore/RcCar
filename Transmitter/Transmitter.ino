#include <SoftwareSerial.h>

SoftwareSerial HC12(2,3); //HC-12 TX-Pins, HC-12 RX Pins

void setup()
{
  Serial.begin(9600);
  HC12.begin(9600);
}

void loop() 
{ 
  HC12.println("Hello World");
  delay(2000);

}
