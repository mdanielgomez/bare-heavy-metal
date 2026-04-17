ELF := blink.elf
OPENOCD_CFG := -f interface/stlink.cfg -f target/stm32f1x.cfg

CC := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -ffreestanding -nostdlib -g
LDSCRIPT = linker/stm32f103rb.ld
TARGET := blink

SRCS := \
	$(wildcard src/startup/*.c) \
	$(wildcard src/*.c) 	

OBJS := $(SRCS:.c=.o)


all: bootloader

bootloader:
	$(MAKE) -C bootloader

# Link .o to .elf
$(TARGET).elf: $(OBJS) $(LDSCRIPT)
	$(CC) $(CFLAGS) -T$(LDSCRIPT) -Wl,-Map=$(TARGET).map,--cref $(OBJS) -o $@

clean: 
	$(MAKE) -C bootloader clean

openocd:
	openocd $(OPENOCD_CFG)

debug:
	gdb-multiarch $(ELF) -x debug.gdb

.PHONY: all clean openocd debug bootloader
