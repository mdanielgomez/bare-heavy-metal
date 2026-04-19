CC := arm-none-eabi-gcc
CFLAGS := -mcpu=cortex-m3 -mthumb -O0 -ffreestanding -nostdlib -g
CFLAGS += -I../common/inc
TARGET := app
OPENOCD_CFG := -f interface/stlink.cfg -f target/stm32f1x.cfg
SRCS := \
	$(wildcard src/*.c)

OBJS := $(SRCS:.c=.o)

all: $(TARGET).elf

# Compile to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link .o to .elf
$(TARGET).elf :$(OBJS) $(LDSCRIPT)
	$(CC) $(CFLAGS) -T$(TARGET).ld -Wl,-Map=$(TARGET).map,--cref $(OBJS) -o $@

flash: $(TARGET).elf
	openocd $(OPENOCD_CFG) \
		-c "init" \
		-c "reset halt" \
		-c "program $(TARGET).elf verify" \
		-c "reset run" \
		-c "exit"

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).map

