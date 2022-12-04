/*
 * demod_ppm.h
 *
 *  Created on: Nov 30, 2022
 *      Author: gianfranco
 */

#ifndef SRC_DEMOD_PPM_H_
#define SRC_DEMOD_PPM_H_

#include <stdint.h>


typedef struct {
	volatile uint32_t RESET;
	volatile uint32_t DATA;
	volatile uint32_t READY;
} DEMOD_PPM_t;


int32_t DEMOD_PPM_receive(DEMOD_PPM_t *base);

void DEMOD_PPM_reset(DEMOD_PPM_t *base);

#endif /* SRC_DEMOD_PPM_H_ */
