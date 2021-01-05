/*
 * seg.c
 *
 * Created: 5/21/2020 10:54:47 AM
 *  Author: H
 */ 

#include "seg.h"
static const U_8 numbers[11]={NUM_0,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9,NUM_DOT};

void seg_init(void)
{
	/*seg EN new*/
	set_bit(SEG_EN_DDR,SEG_EN_PIN);
	clear_bit(SEG_EN_PORT,SEG_EN_PIN);
	/*----------------------------------*/
	/*OUT*/
	set_all_bits(SEG_DATA_DDR);
	set_bits(SEG_DIGIT_DDR,SEG_DIGIT_MSK);
	/*DEFAULT*/
	set_all_bits(SEG_DATA_PORT);
	clear_bits(SEG_DIGIT_PORT,SEG_DIGIT_MSK);
}
void seg_display(U_8 u8_digit_num,U_8 u8_value)
{
	/*SELECT DIGIT*/
	set_bit(SEG_DIGIT_PORT,u8_digit_num - 1);
	/*APPLY DATA VALUE*/
	if (u8_value == '.')
	{
		SEG_DATA_PORT = numbers[10];
	} 
	else
	{
		SEG_DATA_PORT = numbers[u8_value];
	}
	/*WAIT FOR 1 ms*/
	_delay_ms(1);
	/*UNSELECT DIGIT*/
	clear_bit(SEG_DIGIT_PORT,u8_digit_num - 1);
}