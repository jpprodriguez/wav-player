/*
 * FW_Timer1.c
 *
 *  Created on: 27/12/2013
 *      Author: elchurrito
 */

/**
 * \file FW_Timer1.c
 * \brief Drivers del Timer 1
 */

#include "regs.h"
#include "UtilesInfo2.h"
#include "FW_DAC.h"
#include "FW_Timer1.h"
#include "AppFunctions.h"
#include "PR_Display7Seg.h"




volatile uint32_t G_tiempo_actual=0;

extern FIL G_fp;

char string_G_tiempo_actual[40];

/*********************************************************************//**
 * @brief		Inicializa el Timer1
 ***********************************************************************/

void InitTimer1(void)
{
	PCONP |= 1 << 2;

	PCLKSEL0 |= 1 << 4;


	T1MR0 = 40000000;				// Configuro el tiempo del match 0 en 400mseg


	T1MCR = 0x3;					// Match 0 resetea e interrumpe

	T1PR = 0;						// Prescaler en 0

	T1TCR = 0;						// Funcionamiento como timer


	T1TCR = 0x02;					// Apago y reseteo el timer


	ISER0 |= 1<<2; 					// Habilito interrupcion del Timer0 en el NVIC.
}

/*********************************************************************//**
 * @brief		Resetea y luego inicia el Timer1
 ***********************************************************************/
void StartTimer1()
{
	T1TCR = 0x02;

	T1TCR = 0x01;
}

/*********************************************************************//**
 * @brief		Resetea y apaga el Timer1 y resetea el display
 ***********************************************************************/
void StopTimer1()
{
	T1TCR = 0x02;

	DisplayTime(0);

}

/*********************************************************************//**
 * @brief		Funcion de interrupcion del Timer1
 ***********************************************************************/
void TIMER1_IRQHandler(void)
{

    if(T1IR & 0x01)					// Si interrumpio match 0
    {

    	T1IR |= 0x01; 				// Borro flag del Match 0

/*Calcula el tiempo actual en segundos diviendo la posicion actual de la cancion(menos los 44 primeros bytes que son los metadatos)
 *por la cantidad de bytes que hay en un segundo(8000)*/

    	G_tiempo_actual= (f_tell(&G_fp)-44) / 8000;

    	DisplayTime(G_tiempo_actual);


    }
}

