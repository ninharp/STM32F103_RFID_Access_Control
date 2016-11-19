/**
 * @file main.h
 *
 * @brief This file includes the main variables, structs, ...
 *
 * @author Michael Sauer <sauer.uetersen@gmail.com>
 *
 * @date 09.11.2016 - First Version
 **/

//--------------------------------------------------------------
#ifndef _MAIN_H
#define _MAIN_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "uart1.h" // uart1 library
#include "dwt.h" // dwt library
#include "utils.h" // utils library
#ifdef KEY_TOUCH_TTP229
#include "ttp229.h" // TTP229 Touch Controller Library
#endif
#include "feedback.h" // feedback routines
#include "tm_keypad.h" // keymatrix input library
#include "tm_mfrc522.h" // mfrc522 rfid reader library
#include "general.h" // general includes and defines

void Delay(vu32 nCount);
void DelayUS(__IO uint32_t nTime);
void DelayMS(__IO uint32_t nTime);
uint32_t GetMillis();

//--------------------------------------------------------------
// Variables
//--------------------------------------------------------------

//--------------------------------------------------------------
#endif // __MAIN_H
