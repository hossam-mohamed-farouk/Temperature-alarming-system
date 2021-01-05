/*
 * key_pad.h
 *
 * Created: 5/21/2020 12:43:47 PM
 *  Author: H
 */ 


#ifndef KEY_PAD_H_
#define KEY_PAD_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif 

#include <util/delay.h>
#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"

#define  KEY_PORT	    PORTD
#define  KEY_DDR	    DDRD
#define  KEY_PIN		PIND
#define  KEY_ROWS_MSK  	0X0F
#define  KEY_COLS_MSK	0XF0	

#define  ROW_NUM		4
#define  COL_NUM		4

#define  KEY_NONE		0xFF

void key_pad_init(void);
U_8 key_pad_pressed_key(void);




#endif /* KEY_PAD_H_ */