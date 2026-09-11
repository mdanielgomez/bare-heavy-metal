#pragma once

#include "stm32f103.h"
#include "stdint.h"

#define DMA_CCR_MINC_POS 7
#define DMA_CCR_PINC_POS 6
#define DMA_CCR_CIRC_POS 5
#define DMA_CCR_DIR_POS 4
#define DMA_CCR_TCIE_POS 1

typedef enum
{
    DMA_MINC_DISABLED,
    DMA_MINC_ENABLED
} dma_minc_t;

typedef enum
{
    DMA_PINC_DISABLED,
    DMA_PINC_ENABLED
} dma_pinc_t;

typedef enum
{
    DMA_CIRC_DISABLE,
    DMA_CIRC_ENABLED
} dma_circ_t;

typedef enum
{
    DMA_DIRECTION_PERIPHERAL_TO_MEMORY,
    DMA_DIRECTION_MEMORY_TO_PERIPHERAL
} dma_direction_t;

typedef struct
{
    DMA_TypeDef*    dma;
    uintptr_t       peripheral_address;
    uintptr_t       buffer;
    uint16_t        buffer_size;
    uint8_t         channel;
    dma_minc_t      memory_inc_mode;
    dma_pinc_t      peripheral_inc_mode;
    dma_circ_t      circular_inc_mode;
    dma_direction_t direction;
    uint8_t         transfer_complete_interrupt;
} dma_channel_config_t;

void     dma_config_channel(const dma_channel_config_t* config);
void     dma_channel_enable(DMA_TypeDef* dma, uint8_t channel);
void     dma_channel_disable(DMA_TypeDef* dma, uint8_t channel);
uint16_t dma_channel_get_remaining(DMA_TypeDef* dma, uint8_t channel);
uint8_t  dma_channel_transfer_complete(DMA_TypeDef* dma, uint8_t channel);
void     dma_channel_clear_flags(DMA_TypeDef* dma, uint8_t channel);
