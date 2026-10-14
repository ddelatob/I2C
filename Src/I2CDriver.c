#include <stdint.h>
#include "stm32l432xx.h"
#include "I2CDriver.h"
/**
 * @brief Toggles I2C1 peripheral enable bit.
 * 
 * Clears then toggles I2C1 peripheral's CR1 register at bit 0.
 * 
 * @param[in] PEbit is 1 to enable, 0 to disable.
 * 
 * @pre Analog and/or noise filters must be configured.
 */
void toggleI2C1PeripheralEnable(uint8_t PEbit) {
    I2C1->CR1 &= ~(0x1UL << 0U);
    I2C1->CR1 |= (PEbit << 0U);
}
/**
 * @brief configures digital noise filter on SDA and SCL input.
 * 
 * Filters spikes with a length of up to minKerCkPeriods * kernel clock period length.
 * 
 * @param minKerCKPeriods is minimum number of periods that SCL and SDA's corresponding I2C bus lines
 * must remain stable to have their level taken. 
 */
void configureDigitalNoiseFilter(uint8_t minKerCkPeriods) {
    I2C1->CR1 &= ~(0xFUL << 8U);
    I2C1->CR1 |= (minKerCkPeriods << 8U);
}
/**
 * @brief configures the analog noise filter on SDA and SCL input.
 * 
 * Filters spikes that are less than 50ns.
 * 
 * @param ANFOFFBit is 1 to turn off analog filter and 0 to turn it on.
 */
void configureAnalogNoiseFilter(uint8_t ANFOFFBit)
{
    uint32_t mask = 0x1UL << 12U;
    I2C1->CR1 = (RCC->AHB1ENR & ~mask) | (ANFOFFBit << 12U);
}



uint32_t getTFilterNanoSec()
{

    uint8_t digitalFilterPeriods = I2C1->CR1 & (0xFUL << 8U);

    uint8_t digitalFilterTime = digitalFilterPeriods * 0;

    uint32_t analogFilterSelection = (I2C1->CR1 & (0x1UL << 12U));

    uint8_t analogFilterTime = (50UL & ~analogFilterSelection) | (50UL & analogFilterSelection);
    return analogFilterTime + digitalFilterTime;
}




uint8_t getTI2CClkNanoSec()
{
    if(/*using sysclk*/1) {

    } else {
        uint8_t clkSelction;
    }
}


