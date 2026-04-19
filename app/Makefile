CC := arm-none-eabi-gcc
CFLAGS := -mcpu=cortex-m3 -mthumb -O0 -ffreestanding -nostdlib -g
CFLAGS += -I../common/inc
TARGET := app
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

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).map

