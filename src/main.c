/**
 * @file main.c
 *
 * @brief This file includes the main routines
 *
 * @author Michael Sauer <sauer.uetersen@gmail.com>
 *
 * @date 09.11.2016 - First Version
 *
 **/
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

/* MFRC522 Variables */
MIFARE_Key key;
int block=2;//this is the block number we will write into and then read. Do not write into 'sector trailer' block, since this can make the block unusable.

byte blockcontent[16] = "1234567890123456"; // an array with 16 bytes to be written into one of the 64 card blocks is defined
//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //all zeros. This can be used to delete a block.
byte readbackblock[18]; // This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.

/* Private function prototypes -----------------------------------------------*/
void IO_Init(void);
void RCC_Configuration(void);
void NVIC_Configuration(void);
void TimingDelay_Increment(void);
void SysTick_Handler(void);
void printClocks(void);

uint8_t Keypad_EnterPin(uint8_t pin_sec[4]);

uint8_t TAG_WriteName(char *name);
uint8_t TAG_WriteSurname(char *name);
uint8_t TAG_WritePin(uint8_t *pin);
uint8_t TAG_ReadPin(uint8_t *pin);
uint8_t TAG_ReadConfig(uint8_t *config);
uint8_t TAG_ReadName(char *name);
uint8_t TAG_ReadSurname(char *name);
uint8_t TAG_CheckID(uint8_t id[4]);

int main(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Create keypad instance */
	TM_KEYPAD_Button_t Keypad_Button;

	SystemInit();

	/* System Clock init */
	RCC_Configuration();

	/* NVIC Configuration init */
	NVIC_Configuration();

	/* SysTick init */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_Config((SystemCoreClock / 1000));

	/* GPIO init */
	IO_Init();

	/* USART1 init */
	USART1_Init(UART1_BAUDRATE);

	/* Data Watch init */
	DWT_Init();

	/* Feedback routines init */
	Feedback_Init();

	/* KeyMatrix init */
	TM_KEYPAD_Init();

	LedOn(LED_RED);
	LedOn(LED_GREEN);
	Beep();

	DelayMS(1000);
	LedOff(LED_RED);
	LedOff(LED_GREEN);
	//BeepBeep();

	/* Init MFRC522 Reader */
	PCD_Init();

	// Prepare the security key for the read and write functions - all six key bytes are set to 0xFF at chip delivery from the factory.
	// Since the cards in the kit are new and the keys were never defined, they are 0xFF
	// if we had a card that was programmed by someone else, we would need to know the key to be able to access it. This key would then need to be stored in 'key' instead.

	for (byte i = 0; i < 6; i++) {
			key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
	}
	//printf("Scan a MIFARE Classic card\r\n");

	/* TM_RFC522 RFID Reader init */
	//TM_MFRC522_Init();

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

	unsigned long timerUpdate = millis();
	unsigned long timerDebounce = millis();

	Delay(600000);
	printf("boot io! v%d.%d.%d\r\n\n", ver_maj, ver_min, ver_build);
#ifdef DEBUG
	//printClocks();
#endif

	bool cardPresent = false;

	/* Main Loop */
	while (1)
	{
start_loop:
		/*****************************************establishing contact with a tag/card**********************************************************************/
		do {
			cardPresent = PICC_IsNewCardPresent(); 	// sets successRead to 1 when we get read from reader otherwise 0
		} while (!cardPresent); 	//the program will not go further while you not get a successful read
		// Look for new cards (in case you wonder what PICC means: proximity integrated circuit card)
		// Select one of the cards
		if (PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see h lines 238-45)) contains the ID of the read card.
			// Among other things, the PICC_ReadCardSerial() method reads the UID and the SAK (Select acknowledge) into the uid struct, which is also instantiated
			// during this process.
			// The UID is needed during the authentication process
			//The Uid struct:
			//typedef struct {
			//byte		size;			// Number of bytes in the UID. 4, 7 or 10.
			//byte		uidByte[10];            //the user ID in 10 bytes.
			//byte		sak;			// The SAK (Select acknowledge) byte returned from the PICC after successful selection.
			//} Uid;

			//printf("card selected\r\n");
			Beep();
			printf("Tag ID: %02x%02x%02x%02x\r\n", uid.uidByte[0], uid.uidByte[1], uid.uidByte[2], uid.uidByte[3]);

			/*****************************************writing and reading a block on the card**********************************************************************/
			//TAG_WriteName("Sarah");
			//TAG_WriteSurname("Pradel");
			//uint8_t pin[4] = {2,0,1,2};
			//TAG_WritePin(pin);

			//PICC_DumpToSerial(&(uid));//uncomment this if you want to see the entire 1k memory with the block written into it.

			//Beep();
			//while(1);

			//The 'PICC_DumpToSerial' method 'dumps' the entire MIFARE data block into the serial monitor. Very useful while programming a sketch with the RFID reader...
			//Notes:
			//(1) MIFARE cards conceal key A in all trailer blocks, and shows 0x00 instead of 0xFF. This is a secutiry feature. Key B appears to be public by default.
			//(2) The card needs to be on the reader for the entire duration of the dump. If it is removed prematurely, the dump interrupts and an error message will appear.
			//(3) The dump takes longer than the time alloted for interaction per pairing between reader and card, i.e. the readBlock function below will produce a timeout if
			//    the dump is used.

			//DelayMS(1000);
			if (TAG_CheckID(uid.uidByte) == STATUS_OK) {
				char name[18];
				char fullname[36];
				uint8_t pin[4];
				memset(fullname, 0x00, 36);
				if (TAG_ReadName(name) == STATUS_OK) {
					printf("Name: %s ", name);
					strcat(fullname, name);
					if (TAG_ReadSurname(name) == STATUS_OK) {
						printf("%s\r\n", name);
						strcat(fullname, " ");
						strcat(fullname, name);
					} else {
						printf("\r\n");
					}
					TAG_ReadPin(pin);
					printf("PIN is %d %d %d %d\r\n", pin[0], pin[1], pin[2], pin[3]);
					LedBlink(LED_GREEN, 2);
					LedOn(LED_GREEN);
				} else {
					ErrorFeedback();
					goto start_loop;
				}

				PICC_HaltA();
				PCD_StopCrypto1();
				uint8_t status = Keypad_EnterPin(pin);
				if (status == STATUS_OK) {
					LedOff(LED_GREEN);
					printf("Welcome %s, have a good time!\r\n", fullname);
					LedBlink(LED_GREEN, 8);
					DelayMS(500);
					Beep();
					// Open here or whatever
				} else if (status == STATUS_INVALID) {
					LedOff(LED_GREEN);
					ErrorFeedback();
					DelayMS(500);
					printf("PIN Wrong for %s! Try will be reported!\r\n", fullname);
					LedOff(LED_RED);
				} else if (status == STATUS_TIMEOUT) {
					LedOff(LED_GREEN);
					ErrorFeedback();
					LedBlink(LED_RED, 8);
					DelayMS(500);
					printf("PIN Input timeout for %s! Try will be reported!\r\n", fullname);
					LedOff(LED_RED);
				}
			} else {
				LedBlink(LED_RED, 5);
				printf("TAG not allowed!\r\n");
				DelayMS(2500);
			}
		}

	}
}

#define PIN_LENGTH 4
#define KEYPAD_INPUT_TIMEOUT 5000

uint8_t Keypad_EnterPin(uint8_t pin_sec[4])
{
	TM_KEYPAD_Button_t Keypad_Button;
	long timerDebounce = millis();
	bool pin_complete = false;
	bool timeoutReached = false;
	uint8_t pin[PIN_LENGTH];
	//uint8_t pin_sec[PIN_LENGTH] = { 2,0,1,2 };
	uint8_t pin_pos = 0;
	long timerTimeout = millis();
	bool pin_correct = true;

	while(!pin_complete && !timeoutReached) {
		/* Read keyboard data */
		Keypad_Button = TM_KEYPAD_Read();

		/* Keypad was pressed */
		if (Keypad_Button != TM_KEYPAD_Button_NOPRESSED && ((millis() - timerDebounce) > 100)) {/* Keypad is pressed */
			if ((Keypad_Button < 9) || (Keypad_Button == TM_KEYPAD_Button_ENT))
				KeyFeedback();
			switch (Keypad_Button) {
				case TM_KEYPAD_Button_0:        /* Button 0 pressed */
					pin[pin_pos++] = 0;
					break;
				case TM_KEYPAD_Button_1:        /* Button 1 pressed */
					pin[pin_pos++] = 1;
					break;
				case TM_KEYPAD_Button_2:        /* Button 2 pressed */
					pin[pin_pos++] = 2;
					break;
				case TM_KEYPAD_Button_3:        /* Button 3 pressed */
					pin[pin_pos++] = 3;
					break;
				case TM_KEYPAD_Button_4:        /* Button 4 pressed */
					KeyFeedback();
					pin[pin_pos++] = 4;
					break;
				case TM_KEYPAD_Button_5:        /* Button 5 pressed */
					pin[pin_pos++] = 5;
					break;
				case TM_KEYPAD_Button_6:        /* Button 6 pressed */
					pin[pin_pos++] = 6;
					break;
				case TM_KEYPAD_Button_7:        /* Button 7 pressed */
					pin[pin_pos++] = 7;
					break;
				case TM_KEYPAD_Button_8:        /* Button 8 pressed */
					pin[pin_pos++] = 8;
					break;
				case TM_KEYPAD_Button_9:        /* Button 9 pressed */
					pin[pin_pos++] = 9;
					break;
				case TM_KEYPAD_Button_ENT:        /* Button Enter pressed */
					pin_complete = true;
					break;
				default:
					break;
			}
			if (pin_pos > 3)
				pin_pos = 0;
			Keypad_Button = TM_KEYPAD_Button_NOPRESSED;
			timerDebounce = millis();
			timerTimeout = millis();
		}

		if ((millis()-timerTimeout) >= KEYPAD_INPUT_TIMEOUT) {
			timeoutReached = true;
			return STATUS_TIMEOUT;
		}
	}
	printf("PIN Entered: ");
	for (uint8_t i = 0; i < PIN_LENGTH; i++) {
		if (pin_sec[i] != pin[i])
			pin_correct = false;
		printf("%d", pin[i]);
	}
	printf("\r\n");
	if (pin_correct)
		return STATUS_OK;
	else
		return STATUS_INVALID;
}

#define PICC_BLOCK_CONFIG 2
#define PICC_BLOCK_NAME 4
#define PICC_BLOCK_SURNAME 5
#define PICC_BLOCK_SIZE 16

uint8_t TAG_WriteName(char *name)
{
	uint8_t len = strlen(name);
	if (len > 16)
		len = 16;
	uint8_t out[PICC_BLOCK_SIZE];
	strcpy(out, name);
	for (int i = strlen(name); i < PICC_BLOCK_SIZE; i++)
		out[i] = 0x00;
	return writeBlock(PICC_BLOCK_NAME, out);
}

uint8_t TAG_WriteSurname(char *name)
{
	uint8_t len = strlen(name);
	if (len > 16)
		len = 16;
	uint8_t out[PICC_BLOCK_SIZE];
	strcpy(out, name);
	for (int i = strlen(name); i < PICC_BLOCK_SIZE; i++)
		out[i] = 0x00;
	return writeBlock(PICC_BLOCK_SURNAME, out);
}

uint8_t TAG_WritePin(uint8_t *pin)
{
	uint8_t config[PICC_BLOCK_SIZE+2];
	TAG_ReadConfig(config);
	for (uint8_t i = 0; i < PIN_LENGTH; i++)
		config[(PICC_BLOCK_SIZE-PIN_LENGTH)+i] = pin[i];
	return writeBlock(PICC_BLOCK_CONFIG, config);
}

uint8_t TAG_ReadPin(uint8_t *pin)
{
	char in[PICC_BLOCK_SIZE+2];
	uint8_t status = readBlock(PICC_BLOCK_CONFIG, in);
	for (int i = (PICC_BLOCK_SIZE-PIN_LENGTH); i < PICC_BLOCK_SIZE; i++) {
		pin[i-12] = in[i];
	}
	return status;
}

uint8_t TAG_ReadConfig(uint8_t *config)
{
	char in[PICC_BLOCK_SIZE+2];
	uint8_t status = readBlock(PICC_BLOCK_CONFIG, in);
	strcpy(config, in);
	return status;
}

uint8_t TAG_ReadName(char *name)
{
	char in[PICC_BLOCK_SIZE+2];
	uint8_t status = readBlock(PICC_BLOCK_NAME, in);
	strcpy(name, in);
	return status;
}

uint8_t TAG_ReadSurname(char *name)
{
	char in[PICC_BLOCK_SIZE+2];
	uint8_t status = readBlock(PICC_BLOCK_SURNAME, in);
	strcpy(name, in);
	return status;
}

uint8_t TAG_CheckID(uint8_t *id)
{
	uint8_t allowed_ids[3][4] = {
			{ 0x52, 0xb0, 0xdf, 0x6e }, //Michael
			{ 0x42, 0xde, 0xde, 0x6e }, //Hubert
			{ 0x37, 0x51, 0x42, 0xa1 }, //Sarah
	};
	uint8_t id_c = 0;
	for (uint8_t aid = 0; aid < 3; aid++) {
		for (uint8_t i = 0; i < 4; i++) {
			if (id[i] == allowed_ids[aid][i])
				id_c++;
		}
		if (id_c >= 4) {
			return STATUS_OK;
		} else {
			id_c = 0;
		}
	}
	return STATUS_INVALID;
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

	/* Init User Led on Nucleo Board PA5 (D13) also SPI SCK */
	/*
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	*/
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

int writeBlock(int blockNumber, byte arrayAddress[])
{
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber+1)%4 == 0){
	  printf("%d is a trailer block:", blockNumber);
	  return 2;
  }//block number is a trailer block (modulo 4); quit and send error code 2
  //printf("%d is a data block:", blockNumber);

  /*****************************************authentication of the desired block for access***********************************************************/
  byte status = PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(uid));
  //byte PCD_Authenticate(byte command, byte blockAddr, MIFARE_Key *key, Uid *uid);
  //this method is used to authenticate a certain block for writing or reading
  //command: See enumerations above -> PICC_CMD_MF_AUTH_KEY_A	= 0x60 (=1100000),		// this command performs authentication with Key A
  //blockAddr is the number of the block from 0 to 15.
  //MIFARE_Key *key is a pointer to the MIFARE_Key struct defined above, this struct needs to be defined for each block. New cards have all A/B= FF FF FF FF FF FF
  //Uid *uid is a pointer to the UID struct that contains the user ID of the card.
  if (status != STATUS_OK) {
         printf("PCD_Authenticate() failed: %s\r\n", GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  //it appears the authentication needs to be made before every block read/write within a specific sector.
  //If a different sector is being authenticated access to the previous one is lost.


  /*****************************************writing the block***********************************************************/

  status = MIFARE_Write(blockNumber, arrayAddress, 16);//valueBlockA is the block number, MIFARE_Write(block number (0-15), byte array containing 16 values, number of bytes in block (=16))
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != STATUS_OK) {
           printf("MIFARE_Write() failed: %s\r\n", GetStatusCodeName(status));
           return 4;//return "4" as error message
  }
  //printf("block was written\r\n");
  return status;
}


int readBlock(int blockNumber, byte arrayAddress[])
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector

  /*****************************************authentication of the desired block for access***********************************************************/
  byte status = PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(uid));
  //byte PCD_Authenticate(byte command, byte blockAddr, MIFARE_Key *key, Uid *uid);
  //this method is used to authenticate a certain block for writing or reading
  //command: See enumerations above -> PICC_CMD_MF_AUTH_KEY_A	= 0x60 (=1100000),		// this command performs authentication with Key A
  //blockAddr is the number of the block from 0 to 15.
  //MIFARE_Key *key is a pointer to the MIFARE_Key struct defined above, this struct needs to be defined for each block. New cards have all A/B= FF FF FF FF FF FF
  //Uid *uid is a pointer to the UID struct that contains the user ID of the card.
  if (status != STATUS_OK) {
         printf("PCD_Authenticate() failed (read): %s\r\n", GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  //it appears the authentication needs to be made before every block read/write within a specific sector.
  //If a different sector is being authenticated access to the previous one is lost.


  /*****************************************reading a block***********************************************************/

  byte buffersize = 18;//we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size...
  status = MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != STATUS_OK) {
          printf("MIFARE_read() failed: %s\r\n", GetStatusCodeName(status));
          return 4;//return "4" as error message
  }
  //printf("block was read\r\n");
  return status;
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
	/* Process keypad */
	TM_KEYPAD_Update();
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

