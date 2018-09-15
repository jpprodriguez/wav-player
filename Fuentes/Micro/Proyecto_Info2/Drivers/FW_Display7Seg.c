/*
 * FW_Display7Seg.c
 *
 *  Created on: 12/11/2013
 *      Author: elchurrito
 */

/**
 * \file FW_Display7Seg.c
 * \brief Drivers del display de 7 segmentos
 */

#include "KitInfo2_expansiones.h"
#include "UtilesInfo2.h"
#include "FW_Display7Seg.h"


volatile uint8_t Digitos[DIGITOS]; //!< Buffer donde se guardan los digitos a mostrar

/*********************************************************************//**
 * @brief	Realiza un barrido del display
 ***********************************************************************/

void BarridoDisplay( void )
{
	uint8_t aux ;

	static uint8_t	digito = 0 ;

	SetPIN(EX3_BCDA, ON);

	SetPIN(EX3_BCDB, ON);

	SetPIN(EX3_BCDC, ON);

	SetPIN(EX3_BCDD, ON);

	SetPIN(EX3_DP, OFF);


	if(!digito)
	{

		SetPIN(EX3_RST,ON);

		SetPIN(EX3_RST,OFF);

	}
	else
	{

		SetPIN(EX3_CLK,OFF);

		SetPIN(EX3_CLK,ON);



	}
 	aux = Digitos[digito] ;


 	SetPIN(EX3_BCDA, (aux >> 0) & 0x01);

 	SetPIN(EX3_BCDB, (aux >> 1) & 0x01);

 	SetPIN(EX3_BCDC, (aux >> 2) & 0x01);

 	SetPIN(EX3_BCDD, (aux >> 3) & 0x01);


	// Incremento el indice del display
	digito++;

	digito %= DIGITOS;
}


