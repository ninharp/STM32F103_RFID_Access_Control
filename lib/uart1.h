/**
 * @file uart1.h
 *
 * @brief This file includes the UART1 functions
 *
 * @author Michael Sauer <sauer.uetersen@gmail.com>
 *
 * @date 14.09.2014 - erste Version
 *
 */

//--------------------------------------------------------------
#ifndef _UART1_H
#define _UART1_H

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
#include "general.h"

/** @addtogroup Libraries
  * @{
  */

/** @addtogroup UART1_Library
  * @{
  */

/** @addtogroup UART1_Exported_Functions_Prototypes
  * @{
  */

void USART1_Init(uint32_t baudrate);
void USART1_Put(uint8_t ch);
uint8_t USART1_Get(void);
void USART1_Puts(volatile char *s);
void Log(uint8_t level, char* msg);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

//--------------------------------------------------------------
#endif // __UART1_H
