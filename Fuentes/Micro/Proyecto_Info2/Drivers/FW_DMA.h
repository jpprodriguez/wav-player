/*
 * FW_DMA.h
 *
 *  Created on: 21/01/2014
 *      Author: elchurrito
 */

/**
 * \file FW_DMA.h
 * \brief Header del driver del DMA
 */
#ifndef FW_DMA_H_
#define FW_DMA_H_

#include "regs.h"

extern volatile uint8_t G_dma_transfer_done;

void InitDMA ( void );

void DMAChannelInit(unsigned int* buffer);

void StopDMA();

#endif /* FW_DMA_H_ */
