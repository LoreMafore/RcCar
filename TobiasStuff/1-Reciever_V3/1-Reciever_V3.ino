//Reciever
//RX-TX, TX-RX, Middle pin is RX, power and ground, PWM pin LIGHT to 150 ohm resistor to led to ground, 9V VIN.

#define LENGTH 2
#define LIGHT 5

void setup()
{
	pinMode(LIGHT, OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	while(Serial.available() > 0)
	{
		static byte arr[LENGTH];
		static unsigned int index = 0;
		byte new_byte = Serial.read();
		if( (new_byte != 0b00001010) && (index < LENGTH - 1) )
		{
			arr[index] = new_byte;
			index++;
		}else{
			byte input = arr[0];
			if(input == 0b01001111)
				digitalWrite(LIGHT, LOW);
			else if(input == 0b01010000)
				analogWrite(LIGHT, 80);
			index = 0;
		}
	}
}
