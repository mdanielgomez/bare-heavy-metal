#pragma once

#include "stm32f103.h"
#include "stdint.h"

#define DMA_CCR_MINC_POS 7
#define DMA_CCR_PINC_POS 6
#define DMA_CCR_CIRC_POS 5

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

typedef struct
{
    DMA_TypeDef* dma;
    uint32_t*    peripheral_address;
    uint32_t*    buffer;
    uint32_t     buffer_size;
    uint8_t      channel;
    dma_minc_t   memory_inc_mode;
    dma_pinc_t   peripheral_inc_mode;
    dma_circ_t   circular_inc_mode;
} dma_channel_config_t;

void dma_channel_enable(DMA_TypeDef* dma, dma_channel_num_t channel);
void dma_channel_disable(DMA_TypeDef* dma, dma_channel_num_t channel);
void dma_enable_circular_mode(DMA_TypeDef* dma, dma_channel_num_t channel);
void dma_disable_circular_mode(DMA_TypeDef* dma, dma_channel_num_t channel);
void dma_enable_memory_increment_mode(DMA_TypeDef* dma, dma_channel_num_t channel);
void dma_disable_memory_increment_mode(DMA_TypeDef* dma, dma_channel_num_t channel);
void dma_set_peripheral_address(DMA_TypeDef* dma, dma_channel_num_t channel,
                                uint32_t peripheral_address);
void dma_set_memory_address(DMA_TypeDef* dma, dma_channel_num_t channel, uint32_t memory_address);
void dma_set_number_of_data(DMA_TypeDef* dma, dma_channel_num_t channel, uint16_t number_of_data);

dma_config_channel_buffer(DMA_TypeDef* dma, uint32_t* peripheral_address, uint32_t* buffer,
                          uint32_t buffer_size, uint8_t channel);
// dma_config(dma_config_t config)