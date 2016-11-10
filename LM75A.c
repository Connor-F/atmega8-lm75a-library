#include "LM75A.h"
#include "i2c.h"

void initLM75A()
{
	initI2C(32); // twbr as 32 gives 100kbit i2c comms with 8MHz cpu
}

/*
   allows the lm75a temperature register to be read
   Returns: unsigned 16bit int containing the temperature. The top 8 bits represent the whole number part of the temperature, bits 9, 10 and 11 represent the fractional part of the temperature (0.5, 0.25 and 0.125 degrees) and the remaining bits are always 0
*/
uint16_t getTemperature()
{
	i2cStart();
	i2cSend(LM75A_ADDRESS_WRITE);
	i2cSend(LM75A_REGISTER_TEMPERATURE); // set register pointer to temperature register

	i2cStart(); // restart, now reading
	i2cSend(LM75A_ADDRESS_READ);

	uint8_t upperByte = i2cRead(ACK);
	uint8_t lowerByte = i2cRead(NACK);

	i2cStop();

	return (upperByte << 8) | lowerByte;
}
