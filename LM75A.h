#ifndef GUARD_LM75A_H
#define GUARD_LM75A_H

#include <stdint.h>

#define LM75A_ADDRESS_READ 0b10010001
#define LM75A_ADDRESS_WRITE 0b10010000
#define LM75A_REGISTER_TEMPERATURE 0

/* starts i2c */
void initLM75A(); 
/* gets the full temperature register info and returns it to master */
uint16_t getTemperature();

#endif
