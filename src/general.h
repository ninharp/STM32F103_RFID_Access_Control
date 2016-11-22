/**
* @file general.h
*
* @brief This file includes the general program settings
*
* @author Michael Sauer <sauer.uetersen@gmail.com>
*
* @date 20.03.2014 - first Version
*
**/
#ifndef _GENERAL_H
#define _GENERAL_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
#define UART1_BAUDRATE  115200    	///< Bluetooth/RS232 Baudrate

#define DEBUG       	           	///< Uncomment for Debug Mode
#define VERBOSE		5				///< Verbose level in debug mode

//#define KEY_TOUCH_TTP229 0		///< Uncomment for Touch Input Mode with TTP229,
									///  the value was set the type of TTP229 run mode
#define KEY_MATRIX					///< Comment if used with Touch Input Mode

#ifdef KEY_TOUCH_TTP229
#ifdef KEY_MATRIX
#pragma error "error message";
#endif
#endif

/* Version Defines (automagically increased on build) */
#define VER_MAJOR 0
#define VER_MINOR 1
#define VER_BUILD 407

/* Type definitions */
typedef unsigned char  byte; // 1byte
typedef unsigned short  word; // 2bytes
typedef unsigned long  dword; //4bytes

// Return codes from the functions in this class. Remember to update GetStatusCodeName() if you add more.
typedef enum StatusCode {
	STATUS_OK				= 1,	// Success
	STATUS_ERROR			= 2,	// Error in communication
	STATUS_COLLISION		= 3,	// Collission detected
	STATUS_TIMEOUT			= 4,	// Timeout in communication.
	STATUS_NO_ROOM			= 5,	// A buffer is not big enough.
	STATUS_INTERNAL_ERROR	= 6,	// Internal error in the code. Should not happen ;-)
	STATUS_INVALID			= 7,	// Invalid argument.
	STATUS_CRC_WRONG		= 8,	// The CRC_A does not match
	STATUS_MIFARE_NACK		= 9		// A MIFARE PICC responded with NAK.
} StatusCode_t;

//--------------------------------------------------------------
// Structures
//--------------------------------------------------------------

extern uint32_t SystemCoreClock;

#endif // _GENERAL_H
