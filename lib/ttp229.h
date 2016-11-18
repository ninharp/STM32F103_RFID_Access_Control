/*
 * ttp229.h
 *
 *  Created on: 13.11.2016
 *      Author: Michael Sauer <sauer.uetersen@gmail.com>
 *
 *	TP1=0 / TP2=0   =  16 keys active-high
 *	TP1=1 / TP2=0	=  16 keys active-low
 *	TP1=0 / TP2=1   =   8 keys active-high
 *	TP1=1 / TP2=1	=   8 keys active-low
 *
 *  This Library supports only single key, two group functions or multi key at one group at the moment
 *  Multi Key, One Group TP3=1 / TP4=1
 *  Single Key, Two Groups TP3=1 / TP4=0
 *
 *  In Multi Key Mode the GetKey Function only returns the first touched button,
 *  if you want to use complete multi key mode than use the GetKeys function, that will
 *  return the state of multi key presses.
 */

#ifndef LIB_TTP229_H_
#define LIB_TTP229_H_

/* Includes ------------------------------------------------------------------*/
#include "general.h"
/* Exported typedef -----------------------------------------------------------*/
typedef enum TTP229_MODE {
	KEYS_16_ACTIVE_HIGH = 0,	// TP1=0 / TP2=0
	KEYS_16_ACTIVE_LOW,			// TP1=1 / TP2=0
	KEYS_8_ACTIVE_HIGH,			// TP1=0 / TP2=1
	KEYS_8_ACTIVE_LOW,			// TP1=1 / TP2=1
} TTP229_MODE;

typedef enum TTP229_KEY {
	KEY_1 = 0, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8,
	KEY_9, KEY_10, KEY_11, KEY_12, KEY_13, KEY_14, KEY_15, KEY_16, KEY_NONE
} TTP229_KEY;
/* Exported define ------------------------------------------------------------*/
#define TTP229_PORT GPIOA
#define TTP229_RCC_CLOCK RCC_APB2Periph_GPIOA
#define TTP229_SCL GPIO_Pin_0
#define TTP229_SDO GPIO_Pin_1
/* Exported macro -------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void TTP229_Init(uint8_t mode);
TTP229_KEY TTP229_GetKey(void);
uint16_t TTP229_GetKeys(void);

#endif /* LIB_TTP229_H_ */



