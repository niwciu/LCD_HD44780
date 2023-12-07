/*
 * im_delay.h
 *
 *  Created on: 26 wrz 2014
 *      Author: niw-lap
 */

#ifndef IM_DELAY_H_
#define IM_DELAY_H_

#include "main.h"

void _delay_ms (uint32_t delay_ms);
void _delay_us (uint32_t delay_us);

/*
 * Procedura w��czaj�ca odliczanie konkretnego op�nienia ale nie blokuj�ca.
 * Do wykorzystania w maszynach stanu gdzie w danym stanie trzeba byc przez okreslona ilos ms
 */
void count_ms (uint16_t *delay_ms);
void count_s (uint16_t *delay_s);

#endif /* IM_DELAY_H_ */
