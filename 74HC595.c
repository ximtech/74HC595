#include "74HC595.h"

ShiftRegister initShiftRegister(SPI_TypeDef *SPIx,
                                GPIO_TypeDef *chipSelectPort,
                                uint32_t chipSelectPin,
                                uint16_t registerCount,
                                GPIO_TypeDef *resetPort,
                                uint32_t resetPin) {
    ShiftRegister shiftRegister = {0};
    shiftRegister.spi = initSPI(SPIx, chipSelectPort, chipSelectPin);
    shiftRegister.resetPort = resetPort;
    shiftRegister.resetPin = resetPin;
    shiftRegister.count = registerCount;
    resetShiftRegister(&shiftRegister);
    latchShiftRegister(&shiftRegister);
    return shiftRegister;
}

void sendU8ToShiftRegister(ShiftRegister *shiftRegister, uint8_t byte) {
    transmit8BitsSPI(&shiftRegister->spi, byte);
}

void sendU16ToShiftRegister(ShiftRegister *shiftRegister, uint16_t halfWord) {
    if (LL_SPI_GetDataWidth(shiftRegister->spi.SPIx) == LL_SPI_DATAWIDTH_16BIT) {
        transmit16BitsSPI(&shiftRegister->spi, halfWord);
    } else {
        sendU8ToShiftRegister(shiftRegister, halfWord >> 8);
        sendU8ToShiftRegister(shiftRegister, halfWord);
    }
}

void sendBytesToShiftRegister(ShiftRegister *shiftRegister, uint8_t *bytes) {
    for (uint16_t i = shiftRegister->count; i > 0; i--) {
        sendU8ToShiftRegister(shiftRegister, bytes[i - 1]);
    }
    latchShiftRegister(shiftRegister);
}

void latchShiftRegister(ShiftRegister *shiftRegister) {
    chipSelectReset(&shiftRegister->spi);    // set CS to high level, then data flushes to output
    chipSelectSet(&shiftRegister->spi);    // set to low
}

void resetShiftRegister(ShiftRegister *shiftRegister) {
    if (shiftRegister->resetPort != NULL && shiftRegister->resetPin != 0) {
        LL_GPIO_ResetOutputPin(shiftRegister->resetPort, shiftRegister->resetPin);
        LL_GPIO_SetOutputPin(shiftRegister->resetPort, shiftRegister->resetPin);    // set to high(shift register is ready to receive data)
    }
}