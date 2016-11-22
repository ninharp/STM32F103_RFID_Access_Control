/*
 * feedback.c
 *
 *  Created on: 18.11.2016
 *      Author: Michael Sauer <sauer.uetersen@gmail.com>
 */

/* Includes ------------------------------------------------------------------*/
#include "feedback.h"
#include "dwt.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FEEDBACK_t Feedback[] =
{
	// Name    ,PORT , PIN       , PIN NUM, CLOCK               , Init State
	{ LED_RED,  GPIOA, GPIO_Pin_0,	0, 		RCC_APB2Periph_GPIOA, Bit_SET,   ACTIVE_LOW},
	{ LED_GREEN,GPIOA, GPIO_Pin_1,  1, 		RCC_APB2Periph_GPIOA, Bit_SET,   ACTIVE_LOW},
	{ BUZZER,  	GPIOB, GPIO_Pin_2, 	2, 		RCC_APB2Periph_GPIOB, Bit_RESET, ACTIVE_HIGH},
};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void Feedback_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	FEEDBACK_NAME_t feedback_pin;

	for (feedback_pin = 0; feedback_pin < FEEDBACK_COUNT; feedback_pin++)
	{
		// Clock Enable
		RCC_APB2PeriphClockCmd(Feedback[feedback_pin].FEEDBACK_CLOCK, ENABLE);

		// Configure as output mode push/pull
		GPIO_InitStructure.GPIO_Pin = Feedback[feedback_pin].FEEDBACK_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(Feedback[feedback_pin].FEEDBACK_PORT, &GPIO_InitStructure);

		// Set initial value
		if (Feedback[feedback_pin].FEEDBACK_INIT == Bit_RESET)
			GPIO_ResetBits(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN);
		else
			GPIO_SetBits(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN);
	}
}

void Feedback_Led(FEEDBACK_NAME_t feedback_pin, bool state)
{
	if (state) {
		if (Feedback[feedback_pin].FEEDBACK_ACTIVE == ACTIVE_HIGH)
				GPIO_SetBits(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN);
		else
				GPIO_ResetBits(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN);
	} else {
		if (Feedback[feedback_pin].FEEDBACK_ACTIVE == ACTIVE_HIGH)
			GPIO_ResetBits(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN);
		else
			GPIO_SetBits(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN);
	}
}

void Feedback_LedToggle(FEEDBACK_NAME_t feedback_pin)
{
	if (GPIO_ReadInputDataBit(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN) == 0)
		GPIO_SetBits(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN);
	else
		GPIO_ResetBits(Feedback[feedback_pin].FEEDBACK_PORT, Feedback[feedback_pin].FEEDBACK_PIN);
}

void Feedback_Beep(uint16_t delayms)
{
	if (Feedback[BUZZER].FEEDBACK_ACTIVE == ACTIVE_HIGH)
			GPIO_SetBits(Feedback[BUZZER].FEEDBACK_PORT, Feedback[BUZZER].FEEDBACK_PIN);
	else
			GPIO_ResetBits(Feedback[BUZZER].FEEDBACK_PORT, Feedback[BUZZER].FEEDBACK_PIN);
	DWT_Delay_ms(delayms);
	if (Feedback[BUZZER].FEEDBACK_ACTIVE == ACTIVE_HIGH)
			GPIO_ResetBits(Feedback[BUZZER].FEEDBACK_PORT, Feedback[BUZZER].FEEDBACK_PIN);
	else
			GPIO_SetBits(Feedback[BUZZER].FEEDBACK_PORT, Feedback[BUZZER].FEEDBACK_PIN);
}

void Feedback_BeepOff(void)
{
	if (Feedback[BUZZER].FEEDBACK_ACTIVE == ACTIVE_HIGH)
			GPIO_ResetBits(Feedback[BUZZER].FEEDBACK_PORT, Feedback[BUZZER].FEEDBACK_PIN);
	else
			GPIO_SetBits(Feedback[BUZZER].FEEDBACK_PORT, Feedback[BUZZER].FEEDBACK_PIN);
}
