OPENOCD_CFG := -f interface/stlink.cfg -f target/stm32f1x.cfg

ifeq ($(OS),Windows_NT)
    GDB := arm-none-eabi-gdb
else
    GDB := gdb-multiarch
endif

all: bootloader app

bootloader:
	$(MAKE) -C bootloader

app:
	$(MAKE) -C app

flash:
	$(MAKE) -C bootloader flash
	$(MAKE) -C app flash

clean: 
	$(MAKE) -C bootloader clean
	$(MAKE) -C app clean

openocd:
	openocd $(OPENOCD_CFG)

debug_app:
	$(GDB) app/app.elf -x debug.gdb

.PHONY: all clean openocd debug bootloader app
