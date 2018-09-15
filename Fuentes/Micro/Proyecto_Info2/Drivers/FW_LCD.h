/*
 * FW_LCD.h
 *
 *  Created on: 01/11/2013
 *      Author: el churrito
 */

/**
 * \file FW_LCD.h
 * \brief Header del driver del LCD
 */
#ifndef FW_LCD_H_
#define FW_LCD_H_

#include "regs.h"

#define LCD_CONTROL 0

#define LCD_DATA 1

#define TOPE_BUFFER_LCD 80


extern volatile uint32_t G_demora_LCD;

void LCDInit(void);

unsigned char PushLCD( unsigned char,unsigned char);

void RefreshLCD(void);

int PopLCD (void);


#endif /* FW_LCD_H_ */
