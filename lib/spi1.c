/*
 * spi1.c
 *
 *  Created on: 11.11.2016
 *      Author: michael
 */

/* Includes ------------------------------------------------------------------*/
#include "spi1.h"
#include "general.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPI1_GPIO              	GPIOA
#define SPI1_PIN_SCK           	GPIO_Pin_5
#define SPI1_PIN_MISO          	GPIO_Pin_6
#define SPI1_PIN_MOSI          	GPIO_Pin_7

#define SPI1_NSS_PORT			SPI1_GPIO
#define SPI1_PIN_NSS		   	GPIO_Pin_4

/* Private macro -------------------------------------------------------------*/
#define Timed(x) Timeout = 0xFFFF; while (x) { if (Timeout-- == 0) goto errReturn;}
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef   SPI_InitStructure;
/* Private function prototypes -----------------------------------------------*/
void _SPI1_Init_IO(void);
/* Public functions ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void SPI1_Init(void)
{
	_SPI1_Init_IO();

	SPI_I2S_DeInit(SPI1);

	/* enable SPI clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitStructure);

	/* Enable SPI1 */
	SPI_Cmd(SPI1, ENABLE);

}

void _SPI1_Init_IO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* enable gpio clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7; // CLK, MOSI
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //< Master Mode (AF PP)
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // MISO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // Master Mode (FLOATING)
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

Status SPI1_Read(uint8_t *buf,uint32_t nbyte)
{
  __IO uint32_t Timeout = 0;

  if (!nbyte)
    return Success;

  return Success;

errReturn:
  // Any cleanup here
  return Error;

}

__INLINE uint8_t SPI1_Write(const uint8_t buf)
{
	/* Transfer procedure */
	/* Wait for SPIy Tx buffer empty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	/* Send SPI1 data */
	SPI_I2S_SendData(SPI1, buf);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	return SPI1->DR;
}


