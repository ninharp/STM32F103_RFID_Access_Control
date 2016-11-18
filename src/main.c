/*
 * @version 0.1.38
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f10x.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Version Variables */
static uint8_t ver_maj = VER_MAJOR;
static uint8_t ver_min = VER_MINOR;
static uint16_t ver_build = VER_BUILD;
/* Timer Variables */
static __IO uint32_t TimingDelay_ms;

/* Private function prototypes -----------------------------------------------*/
void IO_Init(void);
void RCC_Configuration(void);
void NVIC_Configuration(void);
void TimingDelay_Increment(void);
void SysTick_Handler(void);
void printClocks(void);

int main(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	SystemInit();

	/* System Clock init */
	RCC_Configuration();

	/* NVIC Configuration init */
	NVIC_Configuration();

	/* SysTick init */
	SysTick_Config((SystemCoreClock / 1000));
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

	/* GPIO init */
	IO_Init();

	/* USART1 init */
	USART1_Init(UART1_BAUDRATE);

	/* Data Watch init */
	DWT_Init();

	/* Feedback routines init */
	Feedback_Init();

	LedOn(LED_RED);
	LedOn(LED_GREEN);
	Beep();

	DelayMS(1500);
	LedOff(LED_RED);
	BeepBeep();

#ifdef KEY_TOUCH_TTP229
	/* Init TTP229 */
#if (KEY_TOUCH_TTP229 == 0)
	TTP229_Init(KEYS_16_ACTIVE_LOW);
#elif (KEY_TOUCH_TTP229 == 1)
	TTP229_Init(KEYS_16_ACTIVE_HIGH);
#elif (KEY_TOUCH_TTP229 == 2)
	TTP229_Init(KEYS_8_ACTIVE_LOW);
#elif (KEY_TOUCH_TTP229 == 3)
	TTP229_Init(KEYS_8_ACTIVE_HIGH);
#endif
#endif

	//unsigned long timerUpdate = millis();

	Delay(600000);
	printf("boot io! v%d.%d.%d\r\n\n", ver_maj, ver_min, ver_build);
#ifdef DEBUG
	printClocks();
#endif

	/* Main Loop */
	while (1)
	{
		/*
		TTP229_KEY key = TTP229_GetKey();
		if (key != KEY_NONE) {
			printf("%d\r\n", key+1);
		}
		DWT_Delay_ms(100); // Simplest Debouncing
		*/
	}
}

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : IO_Init
 * Description    : Configures the Input/Output Ports.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Init User Button on Nucleo Board PC13 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN | GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Init User Led on Nucleo Board PA5 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
 * Function Name  : RCC_Configuration
 * Description    : Configures the different system clocks.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;
	// RCC system reset(for debug purpose)
	RCC_DeInit();

	// Enable HSE
	RCC_HSEConfig(RCC_HSE_ON);

	// Wait till HSE is ready
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus == SUCCESS)
	{
		// HCLK = SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		// PCLK2 = HCLK
		RCC_PCLK2Config(RCC_HCLK_Div1);

		// PCLK1 = HCLK/2
		RCC_PCLK1Config(RCC_HCLK_Div1);

		// PLLCLK = 8MHz * 9 = 72 MHz
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		//RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_3);

		// Enable PLL
		RCC_PLLCmd(ENABLE);

		// Wait till PLL is ready
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		// Select PLL as system clock source
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		// Wait till PLL is used as system clock source
		while (RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
}

/*******************************************************************************
 * Function Name  : NVIC_Configuration
 * Description    : Configures Vector Table base location.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM  
	/* Set the Vector Table base location at 0x20000000 */
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
}

/*******************************************************************************
 * Function Name  : Delay
 * Description    : Inserts a delay time.
 * Input          : nCount: specifies the delay time length.
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Delay(vu32 nCount) { for (; nCount != 0; nCount--); }

void printClocks(void)
{
	RCC_ClocksTypeDef RCC_ClockFreq;
	RCC_GetClocksFreq (&RCC_ClockFreq);
	printf (
	  "Running at following clocks: \r\n  SYSCLK = %ld MHz\r\n  HCLK   = %ld MHz\r\n  PCLK1  = %ld MHz\r\n  PCLK2  = %ld MHz\r\n\r\n",
	  RCC_ClockFreq.SYSCLK_Frequency / 1000000,
	  RCC_ClockFreq.HCLK_Frequency / 1000000,
	  RCC_ClockFreq.PCLK1_Frequency / 1000000,
	  RCC_ClockFreq.PCLK2_Frequency / 1000000);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void DelayMS(__IO uint32_t nTime)
{
	uint32_t timerDelay = GetMillis();
	while ((GetMillis() - timerDelay) < nTime);
}

uint32_t GetMillis(void) { return TimingDelay_ms; }


/**
  * @brief  Increments the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Increment(void)
{
	if (TimingDelay_ms != 0xFFFFFFFF) {
		TimingDelay_ms++;
	}
}


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Increment();
}

#ifdef DEBUG
/*******************************************************************************
 * Function Name  : assert_failed
 * Description    : Reports the name of the source file and the source line number
 *                  where the assert_param error has occurred.
 * Input          : - file: pointer to the source file name
 *                  - line: assert_param error line source number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void assert_failed(u8* file, u32 line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	printf("Wrong parameters value: file %s on line %d\r\n", (char*) file,
			(int) line);
	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/******************* (C) COPYRIGHT 2014 Michael Sauer *****END OF FILE****/

