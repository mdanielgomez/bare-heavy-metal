#include "dma.h"

static DMA_Channel_TypeDef* dma_get_channel(DMA_TypeDef* dma, uint8_t channel)
{
    return (DMA_Channel_TypeDef*)((uintptr_t)dma + 0x08 + ((channel - 1) * 0x14));
}

void dma_config_channel(const dma_channel_config_t* config)
{
    DMA_Channel_TypeDef* dma_channel = dma_get_channel(config->dma, config->channel);
    dma_channel->CCR   = 0;
    dma_channel->CPAR  = config->peripheral_address;
    dma_channel->CMAR  = config->buffer;
    dma_channel->CNDTR = config->buffer_size;
    dma_channel->CCR |= (config->memory_inc_mode << DMA_CCR_MINC_POS);
    dma_channel->CCR |= (config->peripheral_inc_mode << DMA_CCR_PINC_POS);
    dma_channel->CCR |= (config->circular_inc_mode << DMA_CCR_CIRC_POS);
    dma_channel->CCR |= (config->direction << DMA_CCR_DIR_POS);
    dma_channel->CCR |= (config->transfer_complete_interrupt << DMA_CCR_TCIE_POS);
}
