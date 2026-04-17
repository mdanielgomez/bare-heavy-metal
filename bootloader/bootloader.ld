ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 16K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

PROVIDE(_sidata = LOADADDR(.data));
PROVIDE(_sdata  = ADDR(.data));
PROVIDE(_edata  = ADDR(.data) + SIZEOF(.data));
PROVIDE(_sbss   = ADDR(.bss));
PROVIDE(_ebss   = ADDR(.bss) + SIZEOF(.bss));

SECTIONS
{
    .isr_vector : { KEEP(*(.isr_vector))} > FLASH

    .text : {
        . = ALIGN(4);
        *(.text*) *(.rodata*)
    } > FLASH

    .data : {
        . = ALIGN(4);
        *(.data*)
        . = ALIGN(4);
    } > RAM AT > FLASH

    .bss : {
        . = ALIGN(4);
        *(.bss*) *(COMMON)
        . = ALIGN(4);
    } > RAM
}
