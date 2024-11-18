void setup()
{
  //This starts the serial communication and set the rate of sending
  //information to 9600 bits per sec
  Serial.begin(9600);
}

void loop() 
{
  //This send the a message using serial. 
  Serial.print("Hello World");
  //Does not send another one for two seconds
  delay(2000);

}
