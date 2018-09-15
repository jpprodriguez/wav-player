/*
 * FW_LCD.c
 *
 *  Created on: 01/11/2013
 *      Author: el churrito
 */

/**
 * \file FW_LCD.c
 * \brief Drivers del LCD
 */

#include "FW_LCD.h"
#include "KitInfo2.h"

static char Buffer_LCD[TOPE_BUFFER_LCD];

static uint32_t inxInLCD= 0;

static uint32_t inxOutLCD = 0;

static uint32_t cantidadColaLCD = 0;

volatile uint32_t G_demora_LCD;

/*********************************************************************//**
 * @brief		Inicializa el LCD
 ***********************************************************************/
void LCDInit() {

	int i;

	SetPIN(LCD_E,OFF);

	G_demora_LCD = 10;

	while(G_demora_LCD);

	for(i= 0 ; i<3 ;i++)
	{
		SetPIN(LCD_D4,1);

		SetPIN(LCD_D5,1);

		SetPIN(LCD_D6,1);

		SetPIN(LCD_D7,0);

		SetPIN(LCD_RS , OFF);

		SetPIN(LCD_E , ON);

		SetPIN(LCD_E , OFF);

		G_demora_LCD = 2;

		while (G_demora_LCD);
	}

			SetPIN(LCD_D4,0);

			SetPIN(LCD_D5,1);

			SetPIN(LCD_D6,0);

			SetPIN(LCD_D7,0);

			SetPIN(LCD_RS , OFF);

			SetPIN(LCD_E , ON);

			SetPIN(LCD_E , OFF);

			G_demora_LCD = 1;

			while (G_demora_LCD);

			PushLCD( 0x28 , LCD_CONTROL);

			PushLCD( 0x08 , LCD_CONTROL);

			PushLCD( 0x01 , LCD_CONTROL);

			PushLCD( 0x06, LCD_CONTROL);

			PushLCD( 0x0C , LCD_CONTROL);  //DISPLAY ON/OFF  CURSOR ON/OFF BLINKING ON/OFF

}

/*********************************************************************//**
 * @brief		Carga un dato en el buffer del LCD
 * @param		dato	dato a cargar en el buffer
 * @param		control	caracter que indica si el dato es informacion o si es un comando de control de LCD
 * @return		1 si se lleno el buffer del LCD,sino 0
 ***********************************************************************/
unsigned char PushLCD ( unsigned char dato, unsigned char control)
{
	if(cantidadColaLCD >= TOPE_BUFFER_LCD)

		return -1;

	Buffer_LCD [inxInLCD] = (dato >> 4) & 0x0f;

	if(control == LCD_CONTROL)

		Buffer_LCD[inxInLCD] |= 0x80;

	inxInLCD ++;

	Buffer_LCD[inxInLCD] = dato & 0x0f;

	if(control == LCD_CONTROL)

		Buffer_LCD[inxInLCD] |= 0x80;

	cantidadColaLCD += 2;

	inxInLCD ++;

	inxInLCD %= TOPE_BUFFER_LCD;

	return 0;
}
/*********************************************************************//**
 * @brief		Muestra un dato del buffer en el LCD
 ***********************************************************************/
void RefreshLCD(void)
{
	int data;

	if((data = PopLCD()) == -1)

		return;

	SetPIN(LCD_D7 , ((unsigned char) data) >> 3 & 0x01);

	SetPIN(LCD_D6 , ((unsigned char) data) >> 2 & 0x01);

	SetPIN(LCD_D5 , ((unsigned char) data) >> 1 & 0x01);

	SetPIN(LCD_D4 , ((unsigned char) data) >> 0 & 0x01);

	if( ((unsigned char) data) & 0x80)

		SetPIN(LCD_RS , OFF);

		else
			SetPIN(LCD_RS , ON);

	SetPIN(LCD_E , ON) ;

	SetPIN(LCD_E , OFF);
 }

/*********************************************************************//**
 * @brief		Saca un dato del buffer del LCD y lo devuelve como entero
 * @return		Un dato sacado del buffer del LCD
 ***********************************************************************/
int PopLCD (void)
{
	char dato;

	if( cantidadColaLCD == 0)

		return -1;

	dato = Buffer_LCD[inxOutLCD];

	cantidadColaLCD --;

	inxOutLCD ++;

	inxOutLCD %= TOPE_BUFFER_LCD;

	return dato;
}
