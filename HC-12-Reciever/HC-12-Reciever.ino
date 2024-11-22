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
    pinMode(ena, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
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
              
              // Clockwise Max Spd
              digitalWrite(in1, HIGH);
              digitalWrite(in2, LOW);
              analogWrite(ena, 50);
              delay(2000);
            
              // Stop
              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              analogWrite(ena, 0);
              delay(2000);
            
              // CounterClockwise Max Spd
              digitalWrite(in1, LOW);
              digitalWrite(in2, HIGH);
              analogWrite(ena, 100);
              delay(2000);
            }
            else
            {
              Serial.write(c);
              Serial.write("Not it");
            }
        }
    }
}
