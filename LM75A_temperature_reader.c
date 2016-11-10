#include "USART.h"
#include "LM75A.h"

#include <avr/power.h> // for 8MHz cpu
#include <util/delay.h>

int main()
{
	clock_prescale_set(clock_div_1); // 8MHz, changing this 
	// requires the TWBR variable to be changed when initialising i2c
	// according to the i2c speed formula on page 213 of the atmega8 datasheet
	initUSART();
	initLM75A(); // sets up i2c internally, with TWBR of 32

	while(1)
	{
		uint16_t temperature = getTemperature();

		usartTransmitByte((uint8_t) (temperature >> 8)); // high byte
		usartTransmitByte((uint8_t) temperature); // low byte

		_delay_ms(100); // lm75a updates every 100ms
	}

	return 0;
}
