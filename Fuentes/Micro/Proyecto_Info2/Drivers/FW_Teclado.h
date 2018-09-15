/**
 * \file FW_Teclado.h
 * \brief Header del driver de lo teclados
 */

#ifndef FW_EXP3TECLADO_H_
#define FW_EXP3TECLADO_H_

#include "regs.h"

#define REBOTES	4

void BarridoTeclas (void);

extern volatile uint32_t Key;

#endif /* FW_EXP3TECLADO_H_ */
