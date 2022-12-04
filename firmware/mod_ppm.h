/*
 * mod_ppm.h
 *
 *  Created on: Nov 30, 2022
 *      Author: gianfranco
 */

#ifndef SRC_MOD_PPM_H_
#define SRC_MOD_PPM_H_

#include <stdint.h>


typedef struct {
	volatile uint32_t RESET;
	volatile uint32_t START;
	volatile uint32_t DATA;
	volatile uint32_t PPM;
	volatile uint32_t BUSY;
} MOD_PPM_t;


void MOD_PPM_send(MOD_PPM_t *base, int32_t value);

#endif /* SRC_MOD_PPM_H_ */
