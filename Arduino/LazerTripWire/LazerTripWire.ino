#include <SoftwareSerial.h>

int laser_sensor = 3;
int led1 = 2;

void setup() {
  pinMode(led1, OUTPUT);

}

void loop() {

  Serial.begin(9600);
  int lazer = digitalRead(laser_sensor);
  Serial.write(lazer);
  
  if(lazer == HIGH)
  {
    Serial.println("High");
    digitalWrite(led1, HIGH); 
  }  

  else
  {
    Serial.println("Low");
    digitalWrite(led1, LOW);
  }
  

}
