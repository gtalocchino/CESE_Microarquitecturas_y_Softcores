/*
 * demod_ppm.c
 *
 *  Created on: Nov 30, 2022
 *      Author: gianfranco
 */

#include "demod_ppm.h"


int32_t DEMOD_PPM_receive(DEMOD_PPM_t *base) {
	while (!(base->READY & 1u));

	uint32_t data = base->DATA;

	if (data & 0b1000) {
		data |= 0xfffffff0;
	}

	return data;
}

void DEMOD_PPM_reset(DEMOD_PPM_t *base) {
	base->RESET = 1;
	base->RESET = 0;
}
