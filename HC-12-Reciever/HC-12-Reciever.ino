#include <SoftwareSerial.h>
#include <string.h>



SoftwareSerial HC12(7,8); // HC-12 TX-Pins, HC-12 RX Pins

int led1 = 2;
// Motor 1 Pins
int ena = 3;
int in1 = 5;
int in2 = 6;

void setup()
{
    Serial.begin(9600);
    HC12.begin(9600);
    pinMode(led1, OUTPUT);
}

void loop() 
{
    // Check if HC-12 has received data
    if (HC12.available()) 
    {
        // Read and display data on Serial Monitor
        while (HC12.available()) 
        {
            char c = HC12.read();

            if(c == 0x31)
            {
              Serial.write(c);
              Serial.write("\n");
              digitalWrite(led1, HIGH);
              delay(500);
              digitalWrite(led1, LOW);
            }
            else
            {
              Serial.write(c);
              Serial.write("Not it");
            }
        }
    }
}
