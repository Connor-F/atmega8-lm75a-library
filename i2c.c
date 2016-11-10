#include "i2c.h"

#include <avr/io.h>

/*
   sets up i2c communications by setting the bit rate and
   enabling i2c
   Param: twbr -> the bit rate to use according to the formula in the 328 datasheet
		page 213
*/
void initI2C(uint8_t twbr) 
{
	TWBR = twbr;                               /* set bit rate, see p. 242 */
									 /* 8MHz / (16+2*TWBR*1) ~= 100kHz ( with twbr as 32 )*/
	TWCR |= 1 << TWEN;                                       /* enable */
}

/*
   waits until the TWINT bit is set in the TWCR which indicates
   the i2c transmission has completed
*/
void i2cWaitForComplete() 
{
	loop_until_bit_is_set(TWCR, TWINT);
}

/*
   sends the i2c start condition
*/
void i2cStart() 
{
	TWCR = (1 << TWINT | 1 << TWEN | 1 << TWSTA);
	i2cWaitForComplete();
}

/*
   sends the i2c stop condition
*/
void i2cStop() 
{
	TWCR = (1 << TWINT | 1 << TWEN | 1 << TWSTO);
}

/*
   reads the value from the selected slave and returns it (1 byte)
   Param: ack -> whether to send an ACK or NACK to the slave after reading
   the byte
   Returns: the byte read, or -1 if neither an ACK or NACK was used as the param
*/
uint8_t i2cRead(uint8_t ack) 
{
	if(ack == ACK)
	{
		TWCR = (1 << TWINT | 1 << TWEN | 1 << TWEA); // enable ack
		i2cWaitForComplete();
		return TWDR;
	}
	else if(ack == NACK)
	{
		TWCR = (1 << TWINT | 1 << TWEN);
		i2cWaitForComplete();
		return TWDR;
	}

	return -1;
}

/*
   sends a byte to the slave and waits for it to transmit
   Param: data -> the byte to send
   Returns: nothing
*/
void i2cSend(uint8_t data) 
{
	TWDR = data;
	TWCR = (1 << TWINT | 1 << TWEN);                  /* init and enable */
	i2cWaitForComplete();
}
