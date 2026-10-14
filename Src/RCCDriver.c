#include "RCCDriver.h"
#include <stdint.h>
#include "stm32l432xx.h"
#include "pins.h"

/**
 * @brief enables or disables I2C peripheral 
 * clocks.
 * 
 * @param I2CNum the number of the I2C
 * peripheral.
 * @param enableBit 1 - enable, 0 - disable.
 */
void enableAPB1I2CClk(uint8_t I2CNum, uint8_t enableBit) {
    uint8_t offset = 20U;
    RCC->APB1ENR1 &= ~(0x3UL << (offset + I2CNum));
    RCC->APB1ENR1 |= (enableBit << (offset + I2CNum));
}
/**
 * @brief enables or disables GPIO AHB2 
 * peripheral clocks.
 * 
 * @param GPIOPort the capitalized port
 * letter.
 * @param enableBit 1 - enable, 0 - disable.
 */
void enableAHB2GPIOCLK(unsigned char GPIOPort, uint8_t enableBit)
{
    uint8_t shift = (GPIOPort <= 'E') ? GPIOPort - 65U : 7U;
    uint32_t mask = (0x1UL << shift);
    RCC->AHB2ENR = (RCC->AHB2ENR & ~mask);
}
/**
 * @brief Allows setting of clock range with MSIRANGE[3:0] in RCC_CSR register or RCC_CR register.
 *
 * Write 0 has no effect, MSIRGSEL at 0 after standby or reset.
 *
 * @param bitState 0 MSI range provided by RCC_CSR register, 1 MSI range provided by RCC_CR register.
 *
 */
void setMSIRGSEL(uint8_t bitState)
{
    RCC->CR |= (0x1UL << 3U);
}
/**
 * @brief Sets MSIRANGE dynamically (NOT MSISRANGE)
 * 
 * @pre To modifyy MSIRANGE, MSI must be off (MSION=0) or MSI must be ready
 *  (MSIRDY=1). MSIRANGE must not be modified when MSI is on and NOT ready
 *  (MISON=1) and (MSIRDY=0).
 */
void setMSIRANGE(uint8_t setting)
{
    if (!(RCC->CR & (0x1UL << 1U)) && (RCC->CR & (0x1UL << 0U))) {return;}
    
    uint8_t setting = 0;
    if (RCC->CR & (0x1UL << 3U))
    {
        RCC->CR = (RCC->CR & ~(0xFUL << 4U) | (setting << 4U));
    }
}

uint8_t MHzToNanoSec(uint8_t MHz) {

}

uint8_t getSysClkNanoSec(void) 
{
    // Need to complete other clocks.
    uint8_t SW = RCC->CFGR & (0x3UL << 0U);
    uint8_t clkSpdMHz = 0U;
    switch (SW)
    {
    case 0x0UL:
        //HSI16
        clkSpdMHz = 0;
        break;
    case 0x1UL:
        clkSpdMHz = getMSIMHz();
        break;
    case 0x2UL:
        //HSE
        clkSpdMHz = 0;
        break;
    case 0x3UL:
        clkSpdMHz = 0;
        break;
    }
    return clkSpdMHz;
}

//fix
uint8_t getMSIMHz(void)
{
    uint8_t range = RCC->CR & (0xFUL << 4U);
    switch (range)
    {
    case 0x0UL:
        return 1U;
    case 0x1UL:
        return 1U;
    case 0x2UL:
        return 1U;
    case 0x3UL:
        return 1U;
    case 0x4UL:
        return 1U;
    case 0x5UL:
        return 2U;
    case 0x6UL:
        return 4U;
    case 0x7UL:
        return 8U;
    case 0x8UL:
        return 16U;
    case 0x9UL:
        return 24U;
    case 0xAUL:
        return 32U;
    case 0xBUL:
        return 48U;
    }
}

uint8_t getI2CLKSpeed(void)
{
    uint8_t selection = RCC->CCIPR & (0x3UL);
    switch (selection)
    {
    case 0x0UL:
        //PCLK calculation
        break;
    case 0x1UL:
        return getSysClkNanoSec();
        break;
    case 0x2UL:
        //HSI16
        break;
    }
    return 0;
}
/**
 * @brief selects PCLK, SYSCLK, or HSI16 as the I2C1 clock source
 * 
 * @param selection 0 - PCLK, 1 - SYSCLK, 2 - HSI16
 */
void setI2C1ClockSource(uint8_t selection) {
    RCC->CCIPR = ((RCC->CCIPR & ~(0x3UL << 12U)) | (selection << 12U));
}
