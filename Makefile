OPENOCD_CFG := -f interface/stlink.cfg -f target/stm32f1x.cfg

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

debug:
	gdb-multiarch $(ELF) -x debug.gdb

.PHONY: all clean openocd debug bootloader app
