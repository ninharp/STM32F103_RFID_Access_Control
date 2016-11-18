/*
 * ttcp229.c
 *
 *  Created on: 13.11.2016
 *      Author: Michael Sauer <sauer.uetersen@gmail.com>
 */

/* Includes ------------------------------------------------------------------*/
#include "ttp229.h"
#include "main.h"
#include "dwt.h"
#include "utils.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TTP229_MODE currentMode = KEYS_16_ACTIVE_HIGH;
/* Private function prototypes -----------------------------------------------*/
uint8_t _TTP229_Receive_8();
uint16_t _TTP229_Receive_16();
/* Public functions ----------------------------------------------------------*/
void TTP229_Init(TTP229_MODE mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	currentMode = mode;

	RCC_APB2PeriphClockCmd(TTP229_RCC_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TTP229_SCL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TTP229_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = TTP229_SDO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(TTP229_PORT, &GPIO_InitStructure);


	if (currentMode == KEYS_16_ACTIVE_LOW || currentMode == KEYS_8_ACTIVE_LOW)
		GPIO_SetBits(TTP229_PORT, TTP229_SCL);
}

TTP229_KEY TTP229_GetKey(void)
{
	uint16_t keys = TTP229_GetKeys();
	//printf("%s\r\n", getBin16(keys));

	if (currentMode == KEYS_16_ACTIVE_HIGH || currentMode == KEYS_8_ACTIVE_HIGH)
		keys = ~keys;

	if (keys & (1 << KEY_1))
		return KEY_1;
	else if (keys & (1 << KEY_2))
		return KEY_2;
	else if (keys & (1 << KEY_3))
		return KEY_3;
	else if (keys & (1 << KEY_4))
		return KEY_4;
	else if (keys & (1 << KEY_5))
		return KEY_5;
	else if (keys & (1 << KEY_6))
		return KEY_6;
	else if (keys & (1 << KEY_7))
		return KEY_7;
	else if (keys & (1 << KEY_8))
		return KEY_8;
	else if (keys & (1 << KEY_9))
		return KEY_9;
	else if (keys & (1 << KEY_10))
		return KEY_10;
	else if (keys & (1 << KEY_11))
		return KEY_11;
	else if (keys & (1 << KEY_12))
		return KEY_12;
	else if (keys & (1 << KEY_13))
		return KEY_13;
	else if (keys & (1 << KEY_14))
		return KEY_14;
	else if (keys & (1 << KEY_15))
		return KEY_15;
	else if (keys & (1 << KEY_16))
		return KEY_16;
	return KEY_NONE;
}

uint16_t TTP229_GetKeys(void)
{
	uint16_t keys = 0x0000;
	if (currentMode == KEYS_8_ACTIVE_LOW)
		keys = 0xFF00;

	switch (currentMode) {
		case KEYS_16_ACTIVE_HIGH:
		case KEYS_16_ACTIVE_LOW:	return _TTP229_Receive_16();

		case KEYS_8_ACTIVE_HIGH:
		case KEYS_8_ACTIVE_LOW:		return (keys + _TTP229_Receive_8());

		default:					return keys;

	}
	return keys;
}
/* Private functions ---------------------------------------------------------*/
uint8_t _TTP229_Receive_8()
{
	uint8_t temp = 0;

	for (int i = 0; i < 9; i++) {

		switch (currentMode) {
			case KEYS_8_ACTIVE_HIGH:
			case KEYS_16_ACTIVE_HIGH:
									GPIO_ResetBits(TTP229_PORT, TTP229_SCL);
									if (GPIO_ReadInputDataBit(TTP229_PORT, TTP229_SDO) && i != 0)
										temp |= 0x80;
									GPIO_SetBits(TTP229_PORT, TTP229_SCL);
									break;

			case KEYS_8_ACTIVE_LOW:
			case KEYS_16_ACTIVE_LOW:
									GPIO_SetBits(TTP229_PORT, TTP229_SCL);
									if (!GPIO_ReadInputDataBit(TTP229_PORT, TTP229_SDO) && i != 0)
										temp |= 0x80;
									GPIO_ResetBits(TTP229_PORT, TTP229_SCL);
									break;
			default: break;
		}

		temp >>= 1;
	}

	return temp;
}

uint16_t _TTP229_Receive_16()
{
	uint16_t temp = 0;

	for (int i = 0; i < 17; i++) {
		temp >>= 1;
		switch (currentMode) {
			case KEYS_8_ACTIVE_HIGH:
			case KEYS_16_ACTIVE_HIGH:
									GPIO_SetBits(TTP229_PORT, TTP229_SCL);
									if (!GPIO_ReadInputDataBit(TTP229_PORT, TTP229_SDO) && i != 0)
										temp |= 0x8000;
									GPIO_ResetBits(TTP229_PORT, TTP229_SCL);
									break;

			case KEYS_8_ACTIVE_LOW:
			case KEYS_16_ACTIVE_LOW:
									GPIO_SetBits(TTP229_PORT, TTP229_SCL);
									if (!GPIO_ReadInputDataBit(TTP229_PORT, TTP229_SDO) && i != 0)
										temp |= 0x8000;
									GPIO_ResetBits(TTP229_PORT, TTP229_SCL);
									break;
			default: break;
		}
	}

	return temp;
}


