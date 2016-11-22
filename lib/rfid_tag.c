/*
 *  @file rfid_tag.c
 *
 *  @description
 *
 *  @date: 22.11.2016
 *  @author: Michael Sauer <sauer.uetersen@gmail.com>
 */

/* Includes ------------------------------------------------------------------*/
#include "rfid_tag.h"
#include "tm_keypad.h"
#include "mfrc522.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
StatusCode_t TAG_WriteName(char *name, MIFARE_Key *key)
{
	uint8_t len = strlen(name);
	if (len > 16)
		len = 16;
	uint8_t out[PICC_BLOCK_SIZE];
	strcpy(out, name);
	for (int i = strlen(name); i < PICC_BLOCK_SIZE; i++)
		out[i] = 0x00;
	return PICC_WriteBlock(PICC_BLOCK_NAME, out, key);
}

StatusCode_t TAG_WriteSurname(char *name, MIFARE_Key *key)
{
	uint8_t len = strlen(name);
	if (len > 16)
		len = 16;
	uint8_t out[PICC_BLOCK_SIZE];
	strcpy(out, name);
	for (int i = strlen(name); i < PICC_BLOCK_SIZE; i++)
		out[i] = 0x00;
	return PICC_WriteBlock(PICC_BLOCK_SURNAME, out, key);
}

StatusCode_t TAG_WritePin(uint8_t *pin, MIFARE_Key *key)
{
	uint8_t config[PICC_BLOCK_SIZE+2];
	TAG_ReadConfig(config, key);
	for (uint8_t i = 0; i < PIN_LENGTH; i++)
		config[(PICC_BLOCK_SIZE-PIN_LENGTH)+i] = pin[i];
	return PICC_WriteBlock(PICC_BLOCK_CONFIG, config, key);
}

StatusCode_t TAG_ReadPin(uint8_t *pin, MIFARE_Key *key)
{
	char in[PICC_BLOCK_SIZE+2];
	StatusCode_t status = PICC_ReadBlock(PICC_BLOCK_CONFIG, in, key);
	for (int i = (PICC_BLOCK_SIZE-PIN_LENGTH); i < PICC_BLOCK_SIZE; i++) {
		pin[i-12] = in[i];
	}
	return status;
}

StatusCode_t TAG_ReadConfig(uint8_t *config, MIFARE_Key *key)
{
	char in[PICC_BLOCK_SIZE+2];
	StatusCode_t status = PICC_ReadBlock(PICC_BLOCK_CONFIG, in, key);
	strcpy(config, in);
	return status;
}

StatusCode_t TAG_ReadName(char *name, MIFARE_Key *key)
{
	char in[PICC_BLOCK_SIZE+2];
	StatusCode_t status = PICC_ReadBlock(PICC_BLOCK_NAME, in, key);
	strcpy(name, in);
	return status;
}

StatusCode_t TAG_ReadSurname(char *name, MIFARE_Key *key)
{
	char in[PICC_BLOCK_SIZE+2];
	StatusCode_t status = PICC_ReadBlock(PICC_BLOCK_SURNAME, in, key);
	strcpy(name, in);
	return status;
}

StatusCode_t TAG_CheckID(uint8_t *id)
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



