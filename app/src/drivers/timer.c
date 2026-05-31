#include "timer.h"

void timer_enable_update_interrupt(TIM_TypeDef* timer)
{
    timer->DIER |= 1 << 0;
}
void timer_disable_update_interrupt(TIM_TypeDef* timer)
{
    timer->DIER |= 0 << 0;
}
void timer_enable_counter(TIM_TypeDef* timer)
{
    timer->CR1 |= 1 << 0;
}
void timer_disable_counter(TIM_TypeDef* timer)
{
    timer->CR1 |= 0 << 0;
}
void timer_set_prescalar(TIM_TypeDef* timer, uint16_t prescalar)
{
    timer->PSC = prescalar;
}
void timer_set_auto_reload(TIM_TypeDef* timer, uint32_t value)
{
    timer->ARR = value;
}
void timer_generate_update(TIM_TypeDef* timer, uint32_t value)
{
    timer->EGR = 1 << 0;
}
void timer_clear_update_interrupt_flag(TIM_TypeDef* timer)
{
    timer->SR |= 0;
}