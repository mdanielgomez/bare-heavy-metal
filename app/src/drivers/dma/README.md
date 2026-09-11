# DMA driver

Direct Memory Access (DMA) moves data between a peripheral and memory without
requiring the CPU to copy each value. This project uses DMA1 to support the UART
driver.

| UART operation | DMA1 channel | Mode |
| --- | ---: | --- |
| USART2 receive | 6 | Peripheral-to-memory, circular |
| USART2 transmit | 7 | Memory-to-peripheral, normal |

For UART transfers, the peripheral address remains fixed at the USART data
register while the memory address advances through a buffer. Receive DMA uses
circular mode so incoming data can continuously wrap through its buffer.
Transmit DMA uses normal mode and raises a transfer-complete interrupt after
sending the requested section of the transmit buffer.

Before a channel is configured, the driver disables it and clears its previous
settings. It then programs the peripheral address, memory address, transfer
count, address increment modes, transfer direction, circular mode, and optional
transfer-complete interrupt. A DMA channel must be disabled before these settings
or its transfer count are changed.

The UART driver owns the higher-level buffering policy; the DMA driver only
provides register-level channel configuration, status, and enable/disable
operations.
