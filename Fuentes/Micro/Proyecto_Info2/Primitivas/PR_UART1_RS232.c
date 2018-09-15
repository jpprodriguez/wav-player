/*
 * PR_UART1_RS232.c
 *
 *  Created on: 01/11/2013
 *      Author: el churrito
 */

/**
 * \file PR_UART1_RS232.c
 * \brief Primitivas de la UART1
 */

#include "PR_UART1_RS232.h"
#include "PR_UART1_RS232.h"



volatile uint8_t bufferTx[BUFFER_SIZE];

volatile uint8_t bufferRx[BUFFER_SIZE];

uint8_t tx_in,tx_out;

uint8_t rx_in,rx_out;


uint8_t tx_buffer_full = 0, tx_buffer_empty = 1;

uint8_t rx_buffer_full = 0, rx_buffer_empty = 1;

/*********************************************************************//**
 * @brief		Carga un dato en el bufferTx de la UART1
 * @param		dato dato a cargar en el buffer
 * @return		1 si esta lleno el bufferTx,sino 0
 ***********************************************************************/
uint8_t PushTx(uint8_t dato)
{
	if(tx_buffer_full)

		return 1;

	bufferTx[tx_in] = dato;

	tx_in++;

	tx_in %= BUFFER_SIZE;

	tx_buffer_empty = 0;

	if(tx_in == tx_out){

		tx_buffer_full = 1;
		//Display_LCD("lleno",RENGLON_1);	//se lleno el buffer
	}

	if (txStart == 0)
	{
		txStart = 1;

		PopTx((uint8_t*)&U1THR);
	}
	return 0;
}

/*********************************************************************//**
 * @brief		Saca un dato del bufferTx de la UART1
 * @param		dato puntero al char donde se va a guardar el dato sacado del bufferTX
 * @return		1 si esta vacio el bufferTx,sino 0
 ***********************************************************************/
uint8_t PopTx( uint8_t *dato )
{

	if(tx_buffer_empty)

		return 1;

	*dato = (uint8_t) bufferTx[tx_out];

	tx_out++;

	tx_out %= BUFFER_SIZE;

	tx_buffer_full = 0;

	if(tx_out == tx_in)

		tx_buffer_empty = 1;

	return 0;
}
/*********************************************************************//**
 * @brief		Carga un dato en el bufferRx de la UART1
 * @param		dato dato a cargar en el buffer
 * @return		1 si esta lleno el bufferRx,sino 0
 ***********************************************************************/
uint8_t PushRx( uint8_t dato )
{
	if(rx_buffer_full)

		return 1;

	bufferRx[rx_in] = dato;

	rx_in ++;

	rx_in %= BUFFER_SIZE;

	rx_buffer_empty = 0;

	if(rx_in == rx_out)

		rx_buffer_full = 1;

	return 0;
}

/*********************************************************************//**
 * @brief		Saca un dato del bufferRx de la UART1
 * @param		dato puntero al char donde se va a guardar el dato sacado del bufferRX
 * @return		1 si esta vacio el bufferRx,sino 0
 ***********************************************************************/
uint8_t PopRx( uint8_t *dato )
{
	if(rx_buffer_empty)

		return 1;

	*dato = (uint8_t) bufferRx[rx_out];

	rx_out++;

	rx_out %= BUFFER_SIZE;

	rx_buffer_full = 0;

	if(rx_out == rx_in)

		rx_buffer_empty = 1;

	return 0;
}

/*********************************************************************//**
 * @brief		Envia un cadena de caracteres por la UART1
 * @param		str cadena de caracteres a enviar
 ***********************************************************************/
void EnviarString (const char *str)
{
	uint32_t i;

	for( i = 0 ; str[i]!='\0' ; i++ )

		PushTx( str[i] );

}

