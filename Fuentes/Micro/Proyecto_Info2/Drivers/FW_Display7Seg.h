/*
 * FW_Display7Seg.h
 *
 *  Created on: 12/11/2013
 *      Author: elchurrito
 */

/**
 * \file FW_Display7Seg.h
 * \brief Header del driver del Display de 7 segmentos
 */
#ifndef FW_EXP3DISPLAY_H_
#define FW_EXP3DISPLAY_H_

#include "regs.h"

#include "KitInfo2_Expansiones.h"

#define DIGITOS		4

void BarridoDisplay(void);

extern volatile uint8_t Digitos[];

#endif /* FW_EXP3DISPLAY_H_ */
