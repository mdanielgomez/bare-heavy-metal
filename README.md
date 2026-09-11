# bare-heavy-metal

This repository documents my exploration of embedded firmware development from the ground up. The goal is to develop a strong understanding of how microcontrollers work at a low level by implementing functionality without relying on vendor HAL libraries.

The project focuses on core embedded concepts such as linker scripts, startup code, memory layout, register-level peripheral control, interrupt handling, and debugging with tools like OpenOCD and GDB. Each component is implemented incrementally to better understand the underlying architecture and firmware execution model.

## Driver documentation

Detailed documentation is kept beside each driver so that its explanation stays
close to the implementation:

- [UART driver](app/src/drivers/uart/README.md)
- [DMA driver](app/src/drivers/dma/README.md)
- [Timer driver](app/src/drivers/timer/README.md)

## Board and processor

This project targets the **NUCLEO-F103RB** development board, which uses an
**STM32F103RBT6** microcontroller from STMicroelectronics. The STM32F103 is a
32-bit microcontroller based on an **Arm Cortex-M3** processor core. This project
uses 128 KB of flash memory and 20 KB of SRAM, as reflected in the linker scripts.

The Cortex-M3 implements the Armv7-M architecture and is designed for embedded
and real-time applications. It executes the Thumb and Thumb-2 instruction sets
and includes core features such as the Nested Vectored Interrupt Controller
(NVIC), SysTick timer, and hardware exception handling. The project is compiled
for this core using the `-mcpu=cortex-m3` and `-mthumb` compiler options. On the
STM32F103, the core can run at up to 72 MHz.

The board's integrated ST-LINK interface is used to program and debug the
microcontroller through Serial Wire Debug (SWD). It also supplies the 8 MHz
clock used as the external high-speed clock input for the clock configuration
described below.

## Clock setup

The system clock is configured in `app/src/drivers/clock/clock.c`. The board
supplies an 8 MHz external high-speed clock (HSE), which is selected as the PLL
input. The PLL multiplier is set to x9, producing a 72 MHz PLL clock:

```text
8 MHz HSE x 9 = 72 MHz PLL clock
```

After the PLL is enabled and ready, it is selected as the SYSCLK source. SYSCLK
therefore runs at 72 MHz.

The clock is then distributed through the AHB and APB prescalers:

| Clock | Source | Prescaler | Result |
| --- | --- | ---: | ---: |
| SYSCLK | PLL | - | 72 MHz |
| HCLK (AHB) | SYSCLK | /1 | 72 MHz |
| PCLK1 (APB1) | HCLK | /2 | 36 MHz |
| PCLK2 (APB2) | HCLK | /1 | 72 MHz |

The AHB prescaler is left at `/1`, so HCLK remains equal to SYSCLK. The APB1
prescaler is set to `/2` to keep the low-speed peripheral bus at 36 MHz. The APB2
prescaler is left at `/1`, so the high-speed peripheral bus runs at the full
72 MHz HCLK rate.

Because the core runs at 72 MHz, flash latency is configured for two wait states
before switching SYSCLK to the PLL. The CPU can execute instructions faster than
the embedded flash can supply them at this clock rate. A wait state gives the flash
additional clock cycles to complete each read; without enough wait states, the CPU
could receive invalid instructions or data and the firmware may behave
unpredictably. For an STM32F103 operating in its normal voltage range, 72 MHz
requires two flash wait states. The prefetch buffer is also enabled so upcoming
instructions can be fetched in advance, reducing the performance cost of those
wait states. Both settings are applied while the system is still running from the
slower clock, ensuring flash is ready before SYSCLK is increased to 72 MHz.
