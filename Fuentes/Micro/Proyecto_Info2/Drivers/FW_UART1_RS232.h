/*
 * FW_UART1_RS232.h
 *
 *  Created on: 01/11/2013
 *      Author: el churrito
 */

/**
 * \file FW_UART1_RS232.h
 * \brief Header del driver de la UART1
 */
#ifndef FW_UART1_RS232_H_
#define FW_UART1_RS232_H_


#include "regs.h"


void InitUART1 (void);

extern uint8_t txStart;
extern volatile uint32_t G_Timer_Rx;


#endif /* FW_UART1_RS232_H_ */
