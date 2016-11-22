/*
 *  @file rfid_tag.h
 *
 *  @description
 *
 *  @date: 22.11.2016
 *  @author: Michael Sauer <sauer.uetersen@gmail.com>
 */

#ifndef LIB_RFID_TAG_H_
#define LIB_RFID_TAG_H_

/* Includes ------------------------------------------------------------------*/
#include "general.h"
#include "mfrc522.h"
/* Exported typedef -----------------------------------------------------------*/
/* Exported define ------------------------------------------------------------*/
#define PICC_BLOCK_CONFIG 2
#define PICC_BLOCK_NAME 4
#define PICC_BLOCK_SURNAME 5
#define PICC_BLOCK_SIZE 16
/* Exported macro -------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
StatusCode_t TAG_WriteName(char *name, MIFARE_Key *key);
StatusCode_t TAG_WriteSurname(char *name, MIFARE_Key *key);
StatusCode_t TAG_WritePin(uint8_t *pin, MIFARE_Key *key);
StatusCode_t TAG_ReadPin(uint8_t *pin, MIFARE_Key *key);
StatusCode_t TAG_ReadConfig(uint8_t *config, MIFARE_Key *key);
StatusCode_t TAG_ReadName(char *name, MIFARE_Key *key);
StatusCode_t TAG_ReadSurname(char *name, MIFARE_Key *key);
StatusCode_t TAG_CheckID(uint8_t id[4]);
#endif /* LIB_RFID_TAG_H_ */



