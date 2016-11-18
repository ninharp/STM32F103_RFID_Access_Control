/*
 * keymatrix.h
 *
 *  Created on: 18.11.2016
 *      Author: Michael Sauer <sauer.uetersen@gmail.com>
 */

#ifndef LIB_KEYMATRIX_H_
#define LIB_KEYMATRIX_H_

/* Includes ------------------------------------------------------------------*/
#include "general.h"
/* Exported typedef -----------------------------------------------------------*/
/* Exported define ------------------------------------------------------------*/
#define KEYMATRIX_ROWS 5
#define KEYMATRIX_COLS 4
/* Exported macro -------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
const char keys[KEYMATRIX_ROWS][KEYMATRIX_COLS] = {
	{'L','0','R', 'C'},
	{'7','8','9', 'E'},
	{'4','5','6', 'D'},
	{'1','2','3', 'U'},
	{'F','G','#', '*'},
};
/* Exported function prototypes ----------------------------------------------*/

#endif /* LIB_KEYMATRIX_H_ */



