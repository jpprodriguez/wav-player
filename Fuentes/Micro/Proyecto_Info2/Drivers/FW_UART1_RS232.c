/*
 * FW_UART1_RS232.c
 *
 *  Created on: 01/11/2013
 *      Author: el churrito
 */

/**
 * \file FW_UART1_RS232.c
 * \brief Drivers de la UART1
 */

#include "regs.h"
#include "UtilesInfo2.h"
#include "PR_UART1_RS232.h"
#include "PR_LCD.h"

uint8_t txStart;

volatile uint32_t G_Timer_Rx=0; //!< Cuando esta en 0 significa que no hay conexion con la PC ya que no se estan recibiendo datos

/*********************************************************************//**
 * @brief		Inicializa la UART1
 ***********************************************************************/
void InitUART1 (void)
{

	PCONP |= 0x01<<4;

	PCLKSEL0 &= ~(0x03<<8);

	U1LCR = 0x00000083;

	U1DLM = 0;

	U1DLL = 0xA3;

	SetPINSEL(P0,15,PINSEL_FUNC1);

	SetPINSEL(P0,16,PINSEL_FUNC1);

	U1LCR = 0x03;

	U1IER = 0x03;

	ISER0 |= (1<<6);
}

/*********************************************************************//**
 * @brief		Funcion de interrupcion de la UART1
 ***********************************************************************/
void UART1_IRQHandler (void)
{
	uint8_t IIR, dato;


	do
	{

		IIR = U1IIR;

		if ( IIR & 0x02 ) //THRE
		{
			if( !PopTx(&dato) )

				U1THR = dato;
			else
				txStart = 0;
		}
		if ( IIR & 0x04 ) //Data ready
		{
			PushRx((uint8_t) U1RBR);

			G_Timer_Rx=200; //Cada vez que recibe un dato G_Timer_Rx se carga para avisar que esta conectado con la pc
		}

	}
	while( !( IIR & 0x01 ) );
}

