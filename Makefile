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


all: $(TARGET).elf $(TARGET).bin $(TARGET).hex

bootloader:
	$(MAKE) -C bootloader

# Compile to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link .o to .elf
$(TARGET).elf: $(OBJS) $(LDSCRIPT)
	$(CC) $(CFLAGS) -T$(LDSCRIPT) -Wl,-Map=$(TARGET).map,--cref $(OBJS) -o $@

# Convert elf to bin	
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@
clean: 
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).map $(TARGET).hex

openocd:
	openocd $(OPENOCD_CFG)

debug:
	gdb-multiarch $(ELF) -x debug.gdb

.PHONY: all clean openocd debug bootloader
