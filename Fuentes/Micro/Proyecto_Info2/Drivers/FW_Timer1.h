/*
 * FW_Timer1.h
 *
 *  Created on: 27/12/2013
 *      Author: elchurrito
 */

/**
 * \file FW_Timer1.h
 * \brief Header del driver del Timer 1
 */

#ifndef FW_TIMER1_H_
#define FW_TIMER1_H_

#include "regs.h"
#include "UtilesInfo2.h"

extern volatile uint32_t G_tiempo_actual;

void InitTimer1();

void StartTimer1();

void StopTimer1();


#endif /* FW_TIMER1_H_ */
