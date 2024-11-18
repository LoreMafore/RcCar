//initializing the variables to the pins on the ardunio
int lazer_sensor = 2;
int buzzer = 8;

void setup()
{
  //Making the buzzer variable an Output
  pinMode(buzzer, OUTPUT);
}

void loop() 
{
  //Assigning the sensor to be assigned to a variable so that 
  //we can easilible read what the sensor is doing
  int lazer = digitalRead(lazer_sensor);

  //if the laser is hits the sensor it actiavtes the buzzer 
  // We can swap the buzzer out for a meriad of things
  // We can also change it so if the sensor is not recieving 
  //the lazer the dynamic structure moves
  if(lazer == HIGH)
  {
    tone(buzzer, 2000);  
  }

  //else the buzzer does not do anything
  else
  {
    noTone(buzzer);
  }
  //this pauses for .2 seconds
  delay(200);

}
