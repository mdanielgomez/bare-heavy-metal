CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -ffreestanding -nostdlib -ISTM32CubeF1/Drivers/CMSIS/Include -ISTM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Include
LDSCRIPT = linker/stm32f103rb.ld

all: blink.elf

blink.elf: src/startup/startup_stm32f103rb.c src/main.c $(LDSCRIPT)
	$(CC) $(CFLAGS) -T$(LDSCRIPT) src/startup/startup_stm32f103rb.c	src/main.c -o $@


clean: rm -f blink.elf

.PHONY: all clean