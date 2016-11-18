/*
 * i2c1.h
 *
 *  Created on: 11.11.2016
 *      Author: michael
 */

#ifndef LIB_I2C1_H_
#define LIB_I2C1_H_

/* Includes ------------------------------------------------------------------*/
#include "general.h"
/* Exported typedef -----------------------------------------------------------*/
typedef enum {Error = 0, Success = !Error } Status;
/* Exported define ------------------------------------------------------------*/
#define I2C_SPEED               300000					///< The I2C Address (must be under 400kHz)
#define I2C_SLAVE_ADDRESS7      0x48					///> Unshifted I2C Address to use
/* Exported macro -------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
Status I2C1_Write(const uint8_t* buf,  uint32_t nbyte, uint8_t SlaveAddress, bool sendStop);
Status I2C1_Read(uint8_t *buf,uint32_t nbyte, uint8_t SlaveAddress);
void I2C1_Init(unsigned long speed);

#endif /* LIB_I2C1_H_ */



