#ifndef __dma_H
#define __dma_H

#include "stm32f4xx_hal.h"

void dma_init(void);
void DMA1_Stream6_IRQHandler(void);

#endif
