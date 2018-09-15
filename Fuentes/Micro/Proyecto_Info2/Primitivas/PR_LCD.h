/*
 * PR_LCD.h
 *
 *  Created on: 01/11/2013
 *      Author: el churrito
 */

/**
 * \file PR_LCD.h
 * \brief Header de las primitivas del LCD
 */

#ifndef PR_LCD_H_
#define PR_LCD_H_

#include "regs.h"
#include "FW_LCD.h"

#define RENGLON_1 0

#define RENGLON_2 1

#define RIGHT	1

#define LEFT	0

#define ON		1

#define OFF		0

uint8_t GetLineMaxLenght(void);

void ReiniciarPosicionLCD();

void RecorrerLCD(void);

void DisplayLCD(char *,char);

void LimpiarLCD(void);



#endif /* PR_LCD_H_ */
