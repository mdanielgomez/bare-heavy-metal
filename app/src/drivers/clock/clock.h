#pragma once

#include "stdint.h"

void clock_init_hsi_8mhz(void);

void clock_init_72mhz(void);

uint32_t clock_get_sysclk_hz(void);
uint32_t clock_get_hclk_hz(void);
uint32_t clock_get_pclk1_hz(void);
uint32_t clock_get_pclk2_hz(void);