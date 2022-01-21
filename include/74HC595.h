#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "main.h"
#include "SPI_Polling.h"

/*
 * Pinout:            Pin no.
 SPI: MOSI    -> DS    (14)
 SPI: SCK     -> SH_CP (11)
 SPI: CS      -> ST_CP (12)
 Pin: RESET   -> MR    (10)
 */

typedef struct ShiftRegister {
    SPI_Polling spi;
    GPIO_TypeDef *resetPort;
    uint32_t resetPin;
    uint16_t count;
} ShiftRegister;


ShiftRegister initShiftRegister(SPI_TypeDef *SPIx,
                                GPIO_TypeDef *chipSelectPort,
                                uint32_t chipSelectPin,
                                uint16_t registerCount,
                                GPIO_TypeDef *resetPort,
                                uint32_t resetPin);   // set reset pin and port to 0 if not used

void sendU8ToShiftRegister(ShiftRegister *shiftRegister, uint8_t byte);
void sendU16ToShiftRegister(ShiftRegister *shiftRegister, uint16_t halfWord);

void sendBytesToShiftRegister(ShiftRegister *shiftRegister, uint8_t *bytes);
void latchShiftRegister(ShiftRegister *shiftRegister);
void resetShiftRegister(ShiftRegister *shiftRegister);