/*
 * FW_Teclado.c
 *
 *  Created on: 31/10/2013
 *      Author: el churrito
 */

/**
 * \file FW_Teclado.c
 * \brief Drivers del teclado 4x1 y del teclado de la expansion 3
 */

#include "KitInfo2.h"
#include "KitInfo2_Expansiones.h"
#include "FW_Teclado.h"

#define	NO_KEY		0xFF


volatile uint32_t Key;

/*********************************************************************//**
 * @brief		Antirrebote de tecla por software
 * @param		codigoActual Tecla a validar
 ***********************************************************************/
static void CheckBounce(uint8_t codigoActual)
{
	static uint8_t codigoAnterior = NO_KEY;

	static uint8_t estadosEstables;

	if( codigoActual == NO_KEY )
	{
		codigoAnterior = NO_KEY;

		estadosEstables = 0;

		return;
	}

	if( estadosEstables == 0  )
	{
		codigoAnterior = codigoActual;

		estadosEstables = 1;

		return;
	}

	if( codigoActual != codigoAnterior )
	{
		codigoAnterior = NO_KEY;

		estadosEstables = 0;

		return;
	}

	if( estadosEstables == REBOTES )
	{
		Key = codigoActual;

		estadosEstables++;

		return;
	}

	if( estadosEstables == REBOTES + 1)

		return;

	estadosEstables ++;

	return;
}

/*********************************************************************//**
 * @brief		Obtiene la tecla presionada en el teclado de la Expansion 3
 * @return		Tecla presionada
 ***********************************************************************/
 static uint8_t EXP3GetKeyHw(void)
{
	uint8_t value=NO_KEY;

	SetPIN(EX3_COL0, OFF);

	SetPIN(EX3_COL1, ON);

	if ( GetPIN(EX3_FILA0) == OFF )
		value= 5;

	if ( GetPIN(EX3_FILA1) == OFF )
		value= 6;

	if ( GetPIN(EX3_FILA2) == OFF )
		value= 7;

	if ( GetPIN(EX3_FILA3) == OFF )
		value= 8;

	SetPIN(EX3_COL0, ON);

	SetPIN(EX3_COL1, OFF);

	if ( GetPIN(EX3_FILA0) == OFF )
		value= 12;

	if ( GetPIN(EX3_FILA1) == OFF )
		value= 11;

	if ( GetPIN(EX3_FILA2) == OFF )
		value= 10;

	if ( GetPIN(EX3_FILA3) == OFF )
		value= 9;

	SetPIN(EX3_COL0, ON);

	SetPIN(EX3_COL1, ON);

	return value;
}

 /*********************************************************************//**
  * @brief		Obtiene la tecla presionada y realiza el antirrebote por software
  ***********************************************************************/
 void BarridoTeclas(void)
 {

 	uint8_t tecla_actual;

 	tecla_actual = EXP3GetKeyHw();

 	CheckBounce(tecla_actual);


 }
