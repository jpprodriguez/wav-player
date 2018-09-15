/*
 * PR_Display7Seg.c
 *
 *  Created on: 12/11/2013
 *      Author: elchurrito
 */

/**
 * \file PR_Display7Seg.c
 * \brief Primitivas del display de 7 segmentos
 */

#include "FW_Display7Seg.h"
#include "PR_Display7Seg.h"

/*********************************************************************//**
 * @brief		Muestra un valor en los primeros o en los ultimos dos digitos del display
 * @param		valor valor numerico a mostrar en el display
 * @param		dsp	si dsp=MINUTOS el valor se muestra en los primeros dos digitos y si dsp=SEGUNDOS se muestra el valor en los ultimos dos digitos
 ***********************************************************************/
void Display (uint16_t valor, uint8_t dsp)
{
	int i;

	uint8_t aux[2];

	for(i=1;i>=0;i--)
	{
		aux[i] = valor % 10 ;

		valor /= 10;
	}

	switch(dsp)
	{
		case MINUTOS:

			Digitos[0] = aux[0];

			Digitos[1] = aux[1];

			break;

		case SEGUNDOS:

			Digitos[2] = aux[0];

			Digitos[3] = aux[1];

			break;

	}
}

/*********************************************************************//**
 * @brief		Muestra en el display el tiempo en el formato MMSS
 * @param		time_in_segs tiempo en segundos
 ***********************************************************************/
void DisplayTime(uint32_t time_in_segs)
{
	uint16_t min,segs;

	/*Paso de segundos a minutos y segundos*/

	min = time_in_segs / 60; //minutos

	segs= time_in_segs % 60; //segundos

	Display(min,MINUTOS);

	Display(segs,SEGUNDOS);

}

/*********************************************************************//**
 * @brief		Resetea el Display a 0000
 ***********************************************************************/
void ResetDisplay(void)
{
	int i;

	for(i=0;i<DIGITOS;i++)
		Digitos[i]=0;

}

