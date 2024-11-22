#include <SoftwareSerial.h>
#include <string.h>



SoftwareSerial HC12(2,3); // HC-12 TX-Pins, HC-12 RX Pins

int led1 = 6;
int result;
char stringMatch[12] = "Hello World";

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

            result = strcmp(c, stringMatch);

            if(result == 0)
            {
              Serial.write(c);
            }
            else
            {
              Serial.write(result);
            }
        }

        // Blink LED when data is received
        digitalWrite(led1, HIGH);
        delay(500);
        digitalWrite(led1, LOW);
    }
}
