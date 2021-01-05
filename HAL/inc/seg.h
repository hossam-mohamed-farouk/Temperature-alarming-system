/*
 * seg.h
 *
 * Created: 5/21/2020 10:54:32 AM
 *  Author: H
 */ 


#ifndef SEG_H_
#define SEG_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"

#define SEG_DATA_PORT	PORTC
#define SEG_DATA_DDR	DDRC

#define SEG_DIGIT_PORT	PORTA
#define SEG_DIGIT_DDR	DDRA
#define SEG_DIGIT_MSK	0X0F

/*nEW with kit for 7_seg enable*/
#define SEG_EN_PORT 	PORTF
#define SEG_EN_DDR		DDRA
#define SEG_EN_PIN		PF2		/*Active low*/

#define  NUM_0		0XC0
#define  NUM_1		0XF9
#define  NUM_2		0XA4
#define  NUM_3		0XB0
#define  NUM_4		0X99
#define  NUM_5		0X92
#define  NUM_6		0X82
#define  NUM_7		0XF8
#define  NUM_8		0X80
#define  NUM_9		0X90
#define  NUM_DOT	0X7F


/*
	u8_digit (1-4)
	u8_value (0-9,'.')
*/
void seg_init(void);
void seg_display(U_8 u8_digit_num,U_8 u8_value);






#endif /* SEG_H_ */