/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <inttypes.h>

#include "mod_ppm.h"
#include "demod_ppm.h"

#define MOD_PPM_PER ((MOD_PPM_t *) 0x43C00000)
#define DEMOD_PPM_PER ((DEMOD_PPM_t *) 0x43C10000)



int main(void) {
    init_platform();

    print("Starting PPS system demo\r\n\r\n");

    while (1) {
    	printf("Enter a value: ");

    	char input[128] = {0};
    	scanf("%128s", input);

    	int32_t read_value = 0;

    	if (sscanf(input, "%ld", &read_value) != 1) {
    		printf("Error: not a number\r\n");
    		continue;
    	}

    	DEMOD_PPM_reset(DEMOD_PPM_PER);
    	MOD_PPM_send(MOD_PPM_PER, read_value);

    	int32_t received_value = DEMOD_PPM_receive(DEMOD_PPM_PER);

    	printf("Received value: %ld\r\n", received_value);
    }


    cleanup_platform();

    return 0;
}
