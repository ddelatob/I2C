#ifndef RCCDRIVER_H
#define RCCDRIVER_H

void enableAPB1I2CClk(uint8_t I2CNum, uint8_t enableBit);
void setMSIRGSEL(uint8_t bitState);
void setMSIRANGE(uint8_t setting);
uint8_t getSysClkNanoSec(void);
uint8_t getMSIMHz(void);
uint8_t getI2CLKSpeed(void);
#endif