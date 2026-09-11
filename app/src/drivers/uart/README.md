# UART driver

The UART driver configures the STM32F103 USART peripherals and uses DMA for
asynchronous reception and transmission. The application currently uses
USART2 with the following configuration:

| Setting | Value |
| --- | --- |
| Peripheral | USART2 |
| Peripheral clock | PCLK1 at 36 MHz |
| Baud rate | 9,600 bits per second |
| Word length | 8 bits |
| Parity | None |
| Stop bits | 1 |
| Mode | Transmit and receive |
| TX pin | PA2, alternate-function push-pull output |
| RX pin | PA3, floating input |

## Baud-rate setup

USART2 is connected to APB1, so its baud-rate calculation uses the 36 MHz PCLK1
frequency returned by `clock_get_pclk1_hz()`. The value written to the USART baud
rate register is calculated as:

```text
BRR = PCLK1 / baud rate
BRR = 36,000,000 / 9,600
BRR = 3,750
```

Integer rounding is included in the calculation so that the closest supported
baud rate is selected.

## Receiving data

USART2 reception uses DMA1 Channel 6 in circular mode. Each received byte is
copied from the USART data register into a 128-byte receive buffer without the
CPU moving the byte itself. Circular mode causes DMA to return to the beginning
of the buffer after reaching its end.

`uart_process_receive()` compares the software read position with the current
DMA write position. It passes each unread byte to a callback and advances the
software position. In the current application, the callback queues the byte for
transmission, creating a UART echo.

## Transmitting data

USART2 transmission uses DMA1 Channel 7 and a 128-byte ring buffer.
`uart_write_byte()` places a byte in the buffer and starts a DMA transfer when
one is not already active. The DMA transfer-complete interrupt advances the
buffer's read position and starts the next contiguous section when more data is
waiting.

This design allows the application to continue running while UART data is being
received or transmitted.
