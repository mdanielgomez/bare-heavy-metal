#pragma once

#include "stm32f103.h"
#include <stdint.h>

void timer_enable_update_interrupt(TIM_TypeDef* timer);
void timer_disable_update_interrupt(TIM_TypeDef* timer);
void timer_enable_counter(TIM_TypeDef* timer);
void timer_disable_counter(TIM_TypeDef* timer);
void timer_set_prescalar(TIM_TypeDef* timer, uint32_t prescalar);
void timer_set_auto_reload(TIM_TypeDef* timer, uint32_t value);
void timer_generate_update(TIM_TypeDef* timer);
void timer_clear_update_interrupt_flag(TIM_TypeDef* timer);
