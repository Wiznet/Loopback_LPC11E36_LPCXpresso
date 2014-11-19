/*
===============================================================================
 Name        : W5500EVB.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include "spi_handler.h"
#include "w5500_init.h"
#include "common.h"
#include "loopback.h"

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

////////////////////////////////////////////////
// Shared Buffer Definition for LOOPBACK TEST //
////////////////////////////////////////////////

uint8_t gDATABUF[DATA_BUF_SIZE];

int main(void) {
	uint8_t ret = 0;
	uint8_t sn = 0;

#if defined (__USE_LPCOPEN)
#if !defined(NO_BOARD_LIB)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
    Board_LED_Set(1, true);
    Board_LED_Set(2, true);
#endif
#endif

#if 0
    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
#else
	SPI_Init();
	W5500_Init();
	Net_Conf();

	while(1) {
#if LOOPBACK_MODE == LOOPBACK_NONBLOCK_API
		//Accept for client
		if((ret = loopback_tcps(sn, gDATABUF, 3000)) < 0)
		{
			printf("%d:loopback_tcps error:%ld\r\n",sn,ret);
			break;
		}
		if((ret = loopback_tcps(sn+1, gDATABUF, 3000 + 1)) < 0)
		{
			printf("%d:loopback_tcps error:%ld\r\n",sn+1,ret);
			break;
		}
		if((ret = loopback_tcps(sn+2, gDATABUF, 3000 + 2)) < 0)
		{
			printf("%d:loopback_tcps error:%ld\r\n",sn+2,ret);
			break;
		}
		if((ret=loopback_udps(sn+3,gDATABUF,10000)) < 0)
		{
			printf("%d:loopback_udps error:%ld\r\n",sn+1,ret);
			break;
		}
#endif
	}
#endif
    return 0 ;
}
