/*
 * spi1.h
 *
 *  Created on: 11.11.2016
 *      Author: michael
 */

#ifndef LIB_SPI1_H_
#define LIB_SPI1_H_

/* Includes ------------------------------------------------------------------*/
#include "general.h"
/* Exported typedef -----------------------------------------------------------*/
typedef enum {Error = 0, Success = !Error } Status;
/* Exported define ------------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
uint8_t SPI1_Write(const uint8_t buf);
Status SPI1_Read(uint8_t *buf,uint32_t nbyte);
void SPI1_Init(void);

#endif /* LIB_SPI1_H_ */



