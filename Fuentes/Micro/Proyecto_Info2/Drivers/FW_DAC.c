/*
 * dac.c
 *
 *  Created on: 06/11/2013
 *      Author: el churrito
 */


#include "KitInfo2.h"
#include "FW_DAC.h"

/**
 * \file FW_DAC.c
 * \brief Driver del DAC
 */

/*********************************************************************//**
 * @brief	Inicializa el DAC
 ***********************************************************************/
void InitDAC()
{


   //1.- Selecciono el clock del DAC como 25MHz:
   	PCLKSEL0 &= ~(0x03<<22);
   	//2.- Configuro los pines del DAC
   	//DAC : P0[26]->PINSEL1: 20:21
   	PINSEL1 |= PINSEL_FUNC2 << 20;
   	//3.- Configuro el DAC:
	DACCNTVAL = 0xC35; //CNTVAL = 3125 => 25MHz/3125 = 8kHz
   	DACCTRL = 0x6; 	//DBLBUF_ENA = 1, CNT_ENA = 1



}


