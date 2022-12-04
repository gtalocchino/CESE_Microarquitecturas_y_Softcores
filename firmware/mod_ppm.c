/*
 * mod_ppm.c
 *
 *  Created on: Nov 30, 2022
 *      Author: gianfranco
 */

#include "mod_ppm.h"


void MOD_PPM_send(MOD_PPM_t *base, int32_t value) {
	base->START = 0;
	base->DATA = value;
	base->RESET = 1;


	base->RESET = 0;
	base->START = 1;

	while((base->BUSY & 1u));
}
