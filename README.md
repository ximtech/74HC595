# 74HC595

**STM32** LL(Low-Layer) shift register library. 
A shift register allows to expand the number of I/O pins you can use from any microcontroller.

### Features

- No limit in register count
- Easy bit manipulation
- Small code footprint

<img src="https://github.com/ximtech/74HC595/blob/main/example/view.PNG" alt="image" width="300"/>

### Add as CPM project dependency

How to add CPM to the project, check the [link](https://github.com/cpm-cmake/CPM.cmake)

```cmake
CPMAddPackage(
        NAME 74HC595
        GITHUB_REPOSITORY ximtech/74HC595
        GIT_TAG origin/main)
```

### Project configuration

1. Start project with STM32CubeMX:
    * [SPI configuration](https://github.com/ximtech/74HC595/blob/main/example/config.PNG)
2. Select: Project Manager -> Advanced Settings -> SPI -> LL
3. Generate Code
4. Add sources to project:
```cmake
add_subdirectory(${STM32_CORE_SOURCE_DIR}/SPI/Polling)  # add SPI to project

include_directories(${74HC595_DIRECTORY})   # source directories
file(GLOB_RECURSE SOURCES ${74HC595_SOURCES})    # source files
```

3. Then Build -> Clean -> Rebuild Project

### Wiring

- <img src="https://github.com/ximtech/74HC595/blob/main/example/wiring_1.PNG" alt="image" width="300"/>
- <img src="https://github.com/ximtech/74HC595/blob/main/example/wiring_2.PNG" alt="image" width="300"/>
- <img src="https://github.com/ximtech/74HC595/blob/main/example/wiring_3.PNG" alt="image" width="300"/>

### Usage
```c
#include "74HC595.h"

#define SHIFT_REGISTER_COUNT 2
#define DELAY 50

int main() {
    
    ShiftRegister shiftRegister = initShiftRegister(SPI1, CHIP_SELECT_GPIO_Port, CHIP_SELECT_Pin, SHIFT_REGISTER_COUNT, REG_RESET_GPIO_Port, REG_RESET_Pin);
    uint16_t binaryCounter = 0;
    
    while (1) {
        sendU16ToShiftRegister(&shiftRegister, binaryCounter);
        latchShiftRegister(&shiftRegister);
        binaryCounter++;
        delay_ms(DELAY);
    }
}
```
