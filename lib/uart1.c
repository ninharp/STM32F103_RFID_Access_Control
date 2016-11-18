/**
 * @file uart1.c
 *
 * @brief This file includes the UART1 functions
 *
 * @author Michael Sauer <sauer.uetersen@gmail.com>
 *
 * @date 14.09.2014 - erste Version
 *
 */

#include "uart1.h"
#include "dwt.h"

/** @addtogroup Libraries
 * @{
 */

/** @addtogroup UART1_Library
 * @{
 */

/** @addtogroup UART1_Exported_Defines
 * @{
 */
/**
 * @}
 */

/** @addtogroup UART1_Exported_Variables
 * @{
 */
/**
 * @}
 */

/** @addtogroup UART1_Exported_Functions
 * @{
 */

/**
 * @brief  Logs Message to USART1 with Verbose Level
 *
 * @param  level	Verbose Level to use
 * @param	msg		Message to Send
 * @retval None
 *
 * @note	Add \\r\\n for breaks
 */
void Log(uint8_t level, char* msg)
{
	if (level <= VERBOSE)
		printf("[%d] %s", level, msg);
}

/**
 * @brief  Initializes USART1
 *
 * @param  baudrate	Baudrate to use
 * @retval None
 */
void USART1_Init(uint32_t baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Clock configuration -------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_Init(&NVIC_InitStructure);

	//GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);


	/* Configure the GPIO ports( USART1 Transmit and Receive Lines) */
	/* Configure the USART1_Tx as Alternate function Push-Pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure the USART1_Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);



	/* USART1 configuration ------------------------------------------------------*/
	/* USART1 configured as follow:
	 - BaudRate = like parameter (115200kbps)
	 - Word Length = 9 Bits
	 - One Stop Bit
	 - Even parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_DeInit(USART1);

	/* Configure the USART1 */
	USART_Init(USART1, &USART_InitStructure);

	/* Enable USART1 interrupt */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE,ENABLE);

	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);

	//packetTimer = 0;
	//packetTimeout = false;
}

/**
 * @brief  Puts a byte to USART1
 *
 * @param  ch		Byte to send
 * @retval None
 */
void USART1_Put(uint8_t ch)
{
	//unsigned long timerWait = millis();
	USART_SendData(USART1, (uint8_t) ch);
	//Loop until the end of transmission or timeout appears
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{
		//if ((millis() - timerWait) >= USART_TIMEOUT)
		//	break;
	}
}

/**
 * @brief  Gets one byte from USART1
 *
 * @retval None
 */
uint8_t USART1_Get(void)
{
	//unsigned long timerWait = millis();
	//bool timeout = false;
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
	{
			//if ((millis() - timerWait) >= USART_TIMEOUT) {
			//	timeout = true;
			//	break;
			//}
	};
	//if (timeout)
	//	return 0;
	//else
		return (uint8_t) USART_ReceiveData(USART1);
}

/**
 * @brief  Put string to USART1
 *
 * @param  s		String to send
 * @retval None
 */
void USART1_Puts(volatile char *s)
{
	unsigned long timerWait = millis();
	bool timeout = false;
	while (*s)
	{
		// wait until data register is empty
		while (!(USART1->SR & 0x00000040)) {
			/*if ((millis() - timerWait) >= USART_TIMEOUT) {
				timeout = true;
				break;
			}*/
		};
		//if (timeout) {
		//	return false;
		//} else {
			USART_SendData(USART1, *s++);
		//	return true;
		//}
		//*s++;
	}
}

/**
 * @brief  This is the interrupt request handler (IRQ) for ALL USART1 interrupts
 *
 * @retval None
 */
void USART1_IRQHandler(void)
{

// check if the USART1 receive interrupt flag was set
	if (USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		// get the new byte:
		char inChar = (uint8_t) USART_ReceiveData(USART1);
		//USART3_Put(inChar);
	}
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
