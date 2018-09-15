/**
 * \file PR_Display7Seg.c
 * \brief Primitivas del teclado 4x1 y del teclado de la EXP3
 */

#include "FW_Teclado.h"
#include "PR_Teclado.h"

extern volatile uint32_t Delay_teclado;

/*********************************************************************//**
 * @brief		Obtiene la tecla presionada que se encuentra en el buffer del teclado
 * @return		Tecla del buffer del teclado
 ***********************************************************************/
uint8_t GetKey(void)
{
	uint8_t aux = NO_KEY;


	if (Key != NO_KEY )
	{
		if(!Delay_teclado)
		{
		aux = Key;

		Key = NO_KEY;

		Delay_teclado=200; //medio segundo de delay hasta que tome otra tecla
		}
		else
			Key = NO_KEY;
	}
	return aux;
}
