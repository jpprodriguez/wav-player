/*
 * FW_Timertick.c
 *
 *  Created on: 31/10/2013
 *      Author: el churrito
 */

/**
 * \file FW_Timertick.c
 * \brief Drivers del Systick
 */

#include "PR_Teclado.h"
#include "PR_LCD.h"
#include "PR_Display7Seg.h"
#include "FW_DAC.h"
#include "FW_Timer1.h"
#include "PR_UART1_RS232.h"
#include "stdlib.h"
#include "AppFunctions.h"



volatile uint32_t Timer1=0;

volatile uint32_t Delay_LCD=0;

volatile uint32_t Delay_teclado=0;

/*********************************************************************//**
 * @brief		Inicializa el Systick con un valor de carga de "useg"
 * @param		useg tiempo en microsegundos
 ***********************************************************************/
void InitSystick (uint32_t useg)
{
	uint32_t value;

	value = useg * 100 - 1;

	STRELOAD = value;

	STCURR = 0;

	STCTRL = 0x00000007;
}
/*********************************************************************//**
 * @brief		Funcion de interrupcion del Systick
 ***********************************************************************/
void SysTick_Handler(void)
{

	RefreshLCD();

	RecorrerLCD();

	BarridoTeclas();

	BarridoDisplay();


	if(G_demora_LCD)
		G_demora_LCD--;

	if(Timer1)
		Timer1--;

	if(Delay_LCD)
			Delay_LCD--;

	if(Delay_teclado)
				Delay_teclado--;

	if(G_Timer_Rx)
		G_Timer_Rx--;


	if(G_Timer_Buzzer)
	{
		if(G_Timer_Buzzer==1)
		{
			SetPIN(BUZZ,BUZZ_ON); //Apaga el buzzer
			G_Timer_Buzzer=0;
		}
		else
			G_Timer_Buzzer--;
	}



}

