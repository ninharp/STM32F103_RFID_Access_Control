/**
 * @file dwt.h
 *
 * @brief This file includes the DWT function prototypes
 *
 * @author Michael Sauer <sauer.uetersen@gmail.com>
 *
 * @date 14.09.2014 - First Version
 */
#ifndef _DWT_H
#define _DWT_H

#include "stdint.h"
#include "stm32f10x.h"

/** @addtogroup Libraries
  * @{
  */

/** @addtogroup DWT_Library
  * @{
  */

/** @addtogroup DWT_Exported_Defines
  * @{
  */
#define _delay_ms(ms) { DWT_Delay_ms(ms); }
/**
  * @}
  */

/** @addtogroup DWT_Exported_Functions_Prototypes
  * @{
  */
void DWT_Init(void);
uint32_t DWT_Get(void);
uint8_t DWT_Compare(int32_t tp);
void DWT_Delay(uint32_t us);
void DWT_Delay_ms(uint16_t ms);
uint32_t millis();
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif // _DWT_H
