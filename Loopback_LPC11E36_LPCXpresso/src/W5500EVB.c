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

#include "spiHandler.h"
#include "w5500_init.h"
#include "common.h"
#include "loopback.h"

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
///////////////////////////////////////
// Debugging Message Printout enable //
///////////////////////////////////////
#define _MAIN_DEBUG_

///////////////////////////
// Demo Firmware Version //
///////////////////////////
#define VER_H		1
#define VER_L		00

//////////////////////////////////////////////////
// Socket & Port number definition for Examples //
//////////////////////////////////////////////////
#define SOCK_TCPS       0
#define SOCK_UDPS       1
#define PORT_TCPS		5000
#define PORT_UDPS       3000

////////////////////////////////////////////////
// Shared Buffer Definition for LOOPBACK TEST //
////////////////////////////////////////////////

uint8_t gDATABUF[DATA_BUF_SIZE];

///////////////////////////
// Network Configuration //
///////////////////////////
wiz_NetInfo gWIZNETINFO = { .mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},
                            .ip = {192, 168, 0, 91},
                            .sn = {255, 255, 255, 0},
                            .gw = {192, 168, 0, 1},
                            .dns = {8, 8, 8, 8},
                            .dhcp = NETINFO_STATIC };

// For TCP client loopback examples; destination network info
uint8_t destip[4] = {192, 168, 0, 248};
uint16_t destport = 5000;

int main(void) {
    //int32_t loopback_ret;

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
	Net_Conf(gWIZNETINFO);

#ifdef _MAIN_DEBUG_
	uint8_t tmpstr[6] = {0,};

	ctlwizchip(CW_GET_ID,(void*)tmpstr);

    printf("\r\n=======================================\r\n");
	printf(" WIZnet %s EVB Demos v%d.%.2d\r\n", tmpstr, VER_H, VER_L);
	printf("=======================================\r\n");
	printf(">> W5500 based Loopback Example\r\n");
	printf("=======================================\r\n");

	Display_Net_Conf(); // Print out the network information to serial terminal
#endif

	while(1) {
		/* Loopback Test: TCP Server and UDP */
		// Test for Ethernet data transfer validation
		{
			loopback_tcps(SOCK_TCPS, gDATABUF, PORT_TCPS);
			loopback_udps(SOCK_UDPS, gDATABUF, PORT_UDPS);
			//loopback_ret = loopback_tcpc(SOCK_TCPS, gDATABUF, destip, destport);

			//if(loopback_ret < 0) printf("loopback ret: %ld\r\n", loopback_ret); // TCP Socket Error code
		}
	}
#endif

    return 0 ;
}
