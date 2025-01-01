#include <SoftwareSerial.h>

int y_pin = A1;
int y_val = 0;
char message = 0;

SoftwareSerial HC12(2,3); //HC-12 TX-Pins, HC-12 RX Pins

void setup()
{
  Serial.begin(9600);
  HC12.begin(9600);
  pinMode(y_pin, INPUT);
}

void loop() 
{ 
  y_val = analogRead(y_pin);

  if (y_val >= 0 and y_val <= 341)
  {
      HC12.println("1");
      Serial.print("1");
  }

  else if (y_val >= 342 and y_val <= 682)
  {
    HC12.println("0");
    Serial.print("0");
  }

  else if (y_val >= 683 and y_val <= 1023)
  {
    HC12.println("2");
    Serial.print("2");
  }

}
