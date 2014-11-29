BASENAME := Template
BIN := $(BASENAME).elf
MAP := $(BASENAME).map
LINKER_SCRIPT := stm32f4_flash.ld

CC := arm-none-eabi-gcc
LD := arm-none-eabi-gcc

CFLAGS := -c -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu90 -DUSE_STM32F4_DISCOVERY -DHSE_VALUE=8000000 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER \
    -O0 -ffunction-sections -fdata-sections -g -Wall \
    -I./src \
    -I./Utilities/STM32F4-Discovery \
    -I./Libraries/STM32F4xx_StdPeriph_Driver/inc \
    -I./Libraries/Device/STM32F4xx/Include \
    -I./Libraries/CMSIS/Include

LDFLAGS := \
    -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T$(LINKER_SCRIPT) -Wl,--start-group -lc_s -lm -Wl,--end-group -static -Wl,-cref,-u,Reset_Handler -Wl,-Map=$(MAP) -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x1000

SRCDIRS := \
    src \
    ./Utilities/STM32F4-Discovery \
    ./Libraries/STM32F4xx_StdPeriph_Driver/src
SRC := $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))
OBJ := $(patsubst %.c,%.o,$(SRC))
STARTUP := ./src/startup_stm32f40xx.s

all: $(BIN)

$(BIN): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) $(STARTUP) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm $(OBJ) $(BIN) $(MAP)
