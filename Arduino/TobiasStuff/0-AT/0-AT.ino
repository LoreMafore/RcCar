//5V-VCC, GND-GND, SET-GND, TX-D2, RX-D3
#include <SoftwareSerial.h>

#define RX 2
#define TX 3
SoftwareSerial mySerial(RX,TX);

void setup() {
	Serial.begin(9600);
	mySerial.begin(9600);
}

void loop() {
	while (mySerial.available())
	{
		Serial.write(mySerial.read());
	}
	while (Serial.available())
	{
		mySerial.write(Serial.read());
	}
}
