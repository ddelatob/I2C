#include <stdint.h>
#include "stm32l432xx.h"
/**
 * @brief Toggles I2C1 peripheral enable bit.
 * 
 * Clears then toggles I2C1 peripheral's CR1 register at bit 0.
 * 
 * @param[in] PEbit is 1 to enable, 0 to disable.
 * 
 * @pre Analog and/or noise filters must be configured.
 */
void ToggleI2C1PeripheralEnable(uint8_t PEbit) {
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
 * 
 * @pre 
 */
void ConfigureDigitalNoiseFilter(uint8_t minKerCkPeriods) {
    I2C1->CR1 &= ~(0xFUL << 8U);
    I2C1->CR1 |= (minKerCkPeriods << 8U);
}