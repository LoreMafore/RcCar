// Transmitter
//RX-TX, TX-RX, Middle pin is RX, power and ground, pin BTN to button module to 5V, 10k ohm resistor from button/BTN node to GND, 9V VIN.

#define BTN 2

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	if(digitalRead(BTN) == HIGH)
		Serial.write(0b01010000);
	else if(digitalRead(BTN) == LOW)
		Serial.write(0b01001111);
	Serial.println();
	delay(10);
}

