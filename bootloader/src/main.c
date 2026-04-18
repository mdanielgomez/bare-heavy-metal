#include <stdint.h>
#include "arm.h"

typedef void (*pFunction)(void);
#define APP_BASE 0x08004000u

static inline void set_msp(uint32_t app_sp)
{
    asm volatile("msr msp, %0" ::"r"(app_sp) :);
}

void jump_to_app(void)
{
    uint32_t app_sp    = *(volatile uint32_t*)APP_BASE;
    uint32_t app_reset = *(volatile uint32_t*)(APP_BASE + 4);

    pFunction app_entry = (pFunction)app_reset;

    VTOR = APP_BASE;

    set_msp(app_sp);
    app_entry();
}

int main()
{
    jump_to_app();
    return 0;
}