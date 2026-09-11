# Timer driver

The application uses the STM32F103 general-purpose TIM2 peripheral to generate
periodic update interrupts. Each interrupt toggles PA5, which drives the user LED
on the NUCLEO-F103RB.

## Timer clock

TIM2 is connected to APB1. PCLK1 runs at 36 MHz because the APB1 prescaler is
set to `/2`. On the STM32F103, an APB timer receives twice the peripheral clock
when its APB prescaler is greater than one. TIM2 therefore receives a 72 MHz
timer clock:

```text
PCLK1       = 36 MHz
APB1 divisor = 2
TIM2 clock  = 2 x PCLK1 = 72 MHz
```

## Update-event timing

The prescaler register (`PSC`) divides the timer input clock by `PSC + 1`. The
auto-reload register (`ARR`) determines how many divided timer ticks occur before
an update event:

```text
update frequency = timer clock / ((PSC + 1) x (ARR + 1))
```

The current application writes `PSC = 7,999` and `ARR = 499`. With the 72 MHz
TIM2 clock, this produces 18 update events per second:

```text
72,000,000 / (8,000 x 500) = 18 Hz
```

Because PA5 is toggled once per event, a complete on/off LED cycle takes two
events and occurs at 9 Hz. The comment in `main.c` that bases this calculation on
an 8 MHz timer clock does not match the current 72 MHz clock configuration.

For a 1 ms timer tick and a complete 1 Hz LED blink cycle, the timer could instead
use `PSC = 71,999` and `ARR = 499`. That would toggle the LED every 500 ms.

## Interrupt flow

The application enables the TIM2 update interrupt in the timer and enables the
TIM2 interrupt line in the Nested Vectored Interrupt Controller (NVIC). When TIM2
reaches its auto-reload value, it sets the update interrupt flag and enters
`TIM2_IRQHandler()`. The handler clears the flag and toggles PA5 before returning
to the interrupted code.
