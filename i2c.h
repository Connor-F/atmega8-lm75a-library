#ifndef GUARD_I2C_H
#define GUARD_I2C_H

#include <stdint.h>

#define ACK 1 // i2c ack
#define NACK 0

/* Sets pullups and initializes bus speed to 100kHz (at FCPU=8MHz) */
void initI2C(uint8_t);

/* Waits until the hardware sets the TWINT flag */
void i2cWaitForComplete();

/* Sends a start condition (sets TWSTA) */
void i2cStart();

/* Sends a stop condition (sets TWSTO) */
void i2cStop();

/* Loads data, sends it out, waiting for completion */
void i2cSend(uint8_t);

/* Read in from slave and send ACK/NACK depending on parameter */
uint8_t i2cRead(uint8_t);

#endif
