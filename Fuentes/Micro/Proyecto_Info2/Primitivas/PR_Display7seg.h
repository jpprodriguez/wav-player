/*
 * PR_Display7seg.h
 *
 *  Created on: 12/11/2013
 *      Author: elchurrito
 */

/**
 * \file PR_Display7Seg.h
 * \brief Header de las primitivas del display de 7 segmentos
 */

#ifndef PR_DISPLAY7SEG_H_
#define PR_DISPLAY7SEG_H_

#include "regs.h"
#include "FW_Display7Seg.h"

#define MINUTOS		0

#define SEGUNDOS	1

void Display(uint16_t valor, uint8_t dsp);

void ResetDisplay();

void DisplayTime(uint32_t time_in_segs);

#endif /* PR_DISPLAY7SEG_H_ */

