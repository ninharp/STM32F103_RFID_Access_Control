/*
 * utils.c
 *
 *  Created on: 11.11.2016
 *      Author: Michael Sauer <sauer.uetersen@gmail.com>
 */

#ifndef LIB_UTILS_C_
#define LIB_UTILS_C_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>
/* Exported typedef -----------------------------------------------------------*/
/* Exported define ------------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
const char * getBin8(uint8_t x)
{
	static char b[9];
	b[0] = '\0';
	int z;
	for (z = 128; z > 0; z >>= 1)
	{
		strcat(b, ((x & z) == z) ? "1" : "0");
	}

	return b;
}

const char * getBin16(uint16_t x)
{
	static char b[17];
	b[0] = '\0';

	int z;
	for (z = 32768; z > 0; z >>= 1)
	{
		if (z == 128)
			strcat(b, " ");
		strcat(b, ((x & z) == z) ? "1" : "0");
	}

	return b;
}

const char * invStr(char *in)
{
	static char b[128];
	b[0] = '\0';

	int z;
	for (z = strlen(in)-1; z >= 0; z--)
	{
		char c[2];
		c[0] = in[z];
		c[1] = '\0';
		strcat(b, c);
	}
	b[strlen(in)] = '\0';

	return b;
}
#endif /* LIB_UTILS_C_ */



