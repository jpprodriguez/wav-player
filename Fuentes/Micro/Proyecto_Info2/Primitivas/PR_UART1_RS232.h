/*
 * PR_UART1_RS232.h
 *
 *  Created on: 01/11/2013
 *      Author: el churrito
 */

/**
 * \file PR_UART1_RS232.h
 * \brief Header de las primitivas de la UART1
 */

#ifndef PR_UART1_RS232_H_
#define PR_UART1_RS232_H_

#include <FW_UART1_RS232.h>
#include <regs.h>

#define BUFFER_SIZE	1024   //32

uint8_t PushTx(uint8_t dato);

uint8_t PopTx( uint8_t *dato );

uint8_t PushRx(uint8_t dato);

uint8_t PopRx( uint8_t *dato );

void EnviarString (const char *str);

#endif /* PR_UART1_RS232_H_ */
