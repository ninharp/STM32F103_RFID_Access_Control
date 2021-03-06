/*
 * feedback.h
 *
 * @description This file holds the functions for all feedback from system.
 * 				LEDs and Beeping output implemented by now
 *
 * 				This file uses the STM32 Standard Peripherie Library
 *
 *  Created on: 18.11.2016
 *      Author: Michael Sauer <sauer.uetersen@gmail.com>
 */

#ifndef LIB_FEEDBACK_H_
#define LIB_FEEDBACK_H_

/* Includes ------------------------------------------------------------------*/
#include "general.h"
/* Exported typedef -----------------------------------------------------------*/
/* Exported define ------------------------------------------------------------*/
#define LED_RED_PORT	GPIOA
#define LED_RED_PIN		GPIO_Pin_1
#define LED_GREEN_PORT	GPIOA
#define LED_GREEN_PIN	GPIO_Pin_0

/* Exported macro -------------------------------------------------------------*/
#define LedOn(pin) Feedback_Led(pin, true);
#define LedOff(pin) Feedback_Led(pin, false);
#define LedToggle(pin) Feedback_LedToggle(pin);
#define LedBlink(pin, amount) for (uint8_t i = 0; i < amount+1; i++) { LedToggle(pin); DWT_Delay_ms(75); } LedOff(pin);
#define LedKey() Feedback_Led(LED_RED, true); DWT_Delay_ms(50); Feedback_Led(LED_RED, false);
#define Beep() Feedback_Beep(150);
#define BeepKey() Feedback_Beep(90);
#define BeepBeep() Beep(); DWT_Delay_ms(100); Beep();
#define KeyFeedback() Feedback_Led(LED_GREEN, true); Feedback_Beep(90); Feedback_Led(LED_GREEN, false);
#define ErrorFeedback() Feedback_Led(LED_RED, true); BeepBeep(); DWT_Delay_ms(100); Feedback_Led(LED_RED, false);
/* Exported variables ---------------------------------------------------------*/
/*
 * List of all Pins for the feedbacks
 * (no duplicate numbers and start with 0)
 */
typedef enum
{
  LED_GREEN = 0, // LED Green Pin
  LED_RED = 1,   // LED Red Pin
  BUZZER = 2,	 // Buzzer Pin
}FEEDBACK_NAME_t;

typedef enum
{
	ACTIVE_LOW = 0,	// Active Low
	ACTIVE_HIGH, 	// Active High
	ACTIVE_AF,		// Active through alternate function
} FEEDBACK_ACTIVE_t;

/* Struct of one Pin */
typedef struct {
  FEEDBACK_NAME_t FEEDBACK_NAME;		// Name of Pin
  GPIO_TypeDef* FEEDBACK_PORT; 		    // Port
  const uint16_t FEEDBACK_PIN; 			// Pin
  const uint8_t FEEDBACK_PINNUM;	    // Pin Number
  const uint32_t FEEDBACK_CLOCK; 		// Clock
  BitAction FEEDBACK_INIT;     			// Initial State
  FEEDBACK_ACTIVE_t FEEDBACK_ACTIVE;	// Active on low/high
}FEEDBACK_t;

#define FEEDBACK_COUNT   3 // Count of Feedback_t
/* Exported function prototypes ----------------------------------------------*/
void Feedback_Init(void);									///< Initialize the Feedback I/O Ports
void Feedback_Led(FEEDBACK_NAME_t feedback_pin, bool state);///< Sets Feedback LED to on or off
void Feedback_LedToggle(FEEDBACK_NAME_t feedback_pin);			///< Toggles Feedback LED
void Feedback_Beep(uint16_t delayms);						///< Beep the Buzzer fo x milliseconds
void Feedback_BeepOff(void);
#endif /* LIB_FEEDBACK_H_ */



