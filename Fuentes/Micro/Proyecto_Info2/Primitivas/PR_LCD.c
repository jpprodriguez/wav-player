/* PR_LCD.c
 *
 *  Created on: 01/11/2013
 *      Author: el churrito
 */

/**
 * \file PR_LCD.c
 * \brief Primitivas del LCD
 */

#include "PR_LCD.h"
#include "FW_LCD.h"
#include "stdio.h"
#include "string.h"

#define RESETEAR_BARRIDO	DISPLAY_POS=0; TICK_RECORRER_LCD=0

static uint8_t DISPLAY_POS;

static uint8_t LINE1_WIDTH;

static uint8_t LINE2_WIDTH;

static uint32_t TICK_RECORRER_LCD=0;

static uint32_t DELAY_MUESTRA_LCD=0;

/*********************************************************************//**
 * @brief		Muestra un mensaje en un renglon del LCD
 * @param		msg	mensaje a mostrar
 * @param		renglon renglon en el que se mostrara el mensaje
 ***********************************************************************/

void DisplayLCD(char* msg,char renglon)
{

	unsigned char i;

	switch(renglon)
	{
	case RENGLON_1:

		PushLCD(0x80 , LCD_CONTROL);

		break;


	case RENGLON_2:

			PushLCD(0xc0 , LCD_CONTROL);

			break;
	}

	if((strlen(msg)) >40)   				//Para que no pase a la linea de abajo
			{
			for( i=0; i<39 ; i++) //Carga los primeros 40 caracteres en el renglon 1.el resto se pierde

				PushLCD(msg[i] , LCD_DATA);

			if(renglon==RENGLON_1)

				LINE1_WIDTH=40;
			else
				LINE2_WIDTH=40;

			}else{
				for( i=0; msg[i] != '\0' ; i++) //Carga el string en el LCD
						PushLCD(msg[i] , LCD_DATA);

				if(renglon==RENGLON_1)

					LINE1_WIDTH=strlen(msg);
				else
					LINE2_WIDTH=strlen(msg);
			}

	RESETEAR_BARRIDO;


}
/*********************************************************************//**
 * @brief		Limpia lo escrito en el LCD y deja en blanco la pantalla
 ***********************************************************************/
void LimpiarLCD(void)
{
	PushLCD( 0x01 , LCD_CONTROL);

	LINE1_WIDTH=0;

	LINE2_WIDTH=0;

	RESETEAR_BARRIDO;

}

/*********************************************************************//**
 * @brief		Mueve la posicion del LCD hasta que llega al final del texto y vuelve a la posicion original
 ***********************************************************************/
void RecorrerLCD(void)
{

		//Si la linea con mas caracteres tiene menos de 16 caracteres no hace falta shiftear el LCD
		if(GetLineMaxLenght()<=16)
			return;


		if(TICK_RECORRER_LCD==200) //Delay para que el LCD se vaya moviendo de a poco
		{
			if(DISPLAY_POS==0)//Si el LCD esta en la posicion inicial
			{
				if(DELAY_MUESTRA_LCD==5) //Tiempo que se espera para que el LCD quede quieto un tiempo antes de empezar a recorrerse
				{
				PushLCD(0x18 , LCD_CONTROL); //Shiftea el LCD una posicion hacia la izquierda

				DISPLAY_POS++;

				DELAY_MUESTRA_LCD=0;

				}else
					DELAY_MUESTRA_LCD++;

			}else if(DISPLAY_POS==GetLineMaxLenght()-16) //Si ya se mostro hasta el ultimo caracter del renglon mas largo
			{
				if(DELAY_MUESTRA_LCD==4)//Tiempo que se espera para que el LCD quede quieto un tiempo antes de volver al inicio
				{
				PushLCD(0x02 , LCD_CONTROL); //Manda el cursor y la posicion del LCD al principio

				DISPLAY_POS=0;

				DELAY_MUESTRA_LCD=0;

				}else
					DELAY_MUESTRA_LCD++;
			}else{

				PushLCD(0x18 , LCD_CONTROL); //Shiftea el LCD una posicion hacia la izquierda

				DISPLAY_POS++;
				}


			TICK_RECORRER_LCD=0;

		}else
			TICK_RECORRER_LCD++;
}

/*********************************************************************//**
 * @brief		Calcula que renglon tiene mas longitud
 * @return		El valor de la longitud del renglon mas largo
 ***********************************************************************/
uint8_t GetLineMaxLenght(void)
{
	uint8_t res = LINE1_WIDTH>LINE2_WIDTH ? LINE1_WIDTH : LINE2_WIDTH;

	return res;

}

/*********************************************************************//**
 * @brief		Devuelve la posicion del LCD a la inicial
 ***********************************************************************/
void ReiniciarPosicionLCD()
{

	PushLCD(0x02 , LCD_CONTROL);	//Manda el cursor y la posicion del LCD al principio
}
