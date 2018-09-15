/*
 * FW_DMA.c
 *
 *  Created on: 21/01/2014
 *      Author: elchurrito
 */

/**
 * \file FW_DMA.c
 * \brief Drivers del DMA
 */

#include "FW_DMA.h"
#include "AppFunctions.h"

volatile uint8_t G_dma_transfer_done=0; //!< Flag que avisa que se termino una transferencia por DMA


/*********************************************************************//**
 * @brief	Inicializa el DMA
 ***********************************************************************/

void InitDMA ( void )
{


	PCONP |= 1<<29;	//Energizo el periferico

	DMACSync = 0xFFFF;//Deshabilito la lógica de sincronismo

	DMACIntTCClear = 0x01;	//Deshabilito interrupciones pendientes

	DMACConfig = 0x00000001;	//Habilito el DMA, con logica little endian

	ISER0 |= (1<<26); //Habilito interrupciones del DMA en NVIC
}

/*********************************************************************//**
 * @brief		Inicializa el canal 0 del DMA con "buffer" como direccion de origen
 * @param		buffer puntero que contiene la direccion de memoria del buffer
 ***********************************************************************/
void DMAChannelInit(unsigned int* buffer)
{
	//Canal 0 del DMA

		//Borro datos anteriores
		DMACC0Control = 0;

		DMACC0Config= 0;

		DMACIntTCClear = 0x01;

		//Source: buffer
		DMACC0SrcAddr = (uint32_t)buffer;
		//Dest:DAC (registro del DAC)
		DMACC0DestAddr = (uint32_t)( ( uint32_t  * ) 0x4008C000UL ); // DACR
		/*
		Control:
		Tamanio de la transferencia: 1024
		Cantidad de transferencias por burst en SRC: 1 (0x00)
		Cantidad de transferencias por burst en DST: 1 (0x00)
		Source width (tamanio de los datos en origen): 32 bits (0x02)
		Dest width (tamanio de los datos en destino) : 32 bits (0x02)
		Source increment (se debe incrementar la direccion de source: SI (1)
		Dest increment (se debe incrementar la direccion de destino: NO (0)
		Activacion de la interrupcion al finalizar la transferencia: SI (1)
		*/
		DMACC0Control = 1024 | (0<<12) | (0<<15) | (2<<18) | (2<<21) | (1<<26) | (0<<27) | (1<<31);


		DACCTRL |= 1<<3; //Habilito el pedido de transferencia desde el DAC

		/*Configuro y disparo el canal 0 de DMA:
		Habilito el canal (1)
		Source: Memory (nada)
		Dest: DAC (7)
		Tipo de transferencia (memory to peripheral): (1)
		Interrupcion por finalizacion habilitada: SI (1)
		*/
		DMACC0Config = 0x01 | (0x00<<1) | (7<<6) | (1<<11) | (1<<15);
}

/*********************************************************************//**
 * @brief		Deshabilita el canal 0 del DMA
 ***********************************************************************/
void StopDMA()
{
		DMACC0Config =0;

		DMACC0Control=0;

		DMACIntTCClear = 0x01;

		G_dma_transfer_done=0;
}

/*********************************************************************//**
 * @brief		Funcion de interrupcion del DMA
 ***********************************************************************/
void DMA_IRQHandler ( void )
{
		DMACIntTCClear = 0x01;

		G_dma_transfer_done=1;

}
