/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#include "AppFunctions.h"
#include "PR_Teclado.h"

/**
 * \file main.c
 * \brief Archivo Principal
 */


int main(void)
{
	uint8_t key=NO_KEY;

 	InitApp();


	while(1)
	{
		CheckSD();

		MaqEstadoDMA();

		UARTRx();

		CheckCommand();

		CheckPcConnection();

		if(G_modo==PLACA)
		{
		key= GetKey();

		FuncKey(key);

		CheckEndOfSong();
		}


	}


	return 0;

}
