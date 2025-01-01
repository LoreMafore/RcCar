#include <SoftwareSerial.h>
#include <string.h>



SoftwareSerial HC12(7,8); // HC-12 TX-Pins, HC-12 RX Pins

int led1 = 2;

// Motor 1 Pins
int ena = 3;
int in1 = 5;
int in2 = 6;

//Motor 2 Pins
int enb = 11;
int in3 = 9;
int in4 = 10;

void setup()
{
    Serial.begin(9600);
    HC12.begin(9600);
    pinMode(led1, OUTPUT);
    pinMode(ena, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enb, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
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
              //Serial.println("Forward");
              //Serial.write(c);
              //Serial.write("\n");
              digitalWrite(led1, HIGH);
              digitalWrite(in1, HIGH);
              digitalWrite(in2, LOW);
              analogWrite(ena, 75);
              digitalWrite(in3, HIGH);
              digitalWrite(in4, LOW);
              analogWrite(enb, 70);
            
            }

            else if(c == 0x30)
            {
              // Stop
              //Serial.println("Stop");
              //Serial.write(c);
              //Serial.write("\n");
              digitalWrite(led1, LOW);
              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              analogWrite(ena, 0);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
              analogWrite(enb, 0);
            }
            else if(c == 0x32)
            {
              // CounterClockwise Max Spd
              //Serial.println("Backwards");
              //Serial.write(c);
              //Serial.write("\n");
              digitalWrite(led1, HIGH);
              digitalWrite(in1, LOW);
              digitalWrite(in2, HIGH);
              analogWrite(ena, 75);
              digitalWrite(in3, LOW);
              digitalWrite(in4, HIGH);
              analogWrite(enb, 70);
            }
            else
            {
              //Serial.write(c);
              //Serial.print("Not it");
            }
        }
    }
}
