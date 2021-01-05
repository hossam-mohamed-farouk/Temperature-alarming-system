/*
 * uart.h
 *
 * Created: 6/3/2020 2:30:50 PM
 *  Author: H
 */ 


#ifndef UART_H_
#define UART_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "avr/interrupt.h"
#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"

typedef enum
{
	UART_0,UART_1	
	
}UART_NUM;

void uart_init(UART_NUM uart_num,U_32 baud_rate);
void uart_send_byte(UART_NUM uart_num,U_8 u8_data);
U_8  uart_receive_byte(UART_NUM uart_num);


void uart_send_str(UART_NUM uart_num,U_8* pu8_str);
Bool uart_receive_byte_unblock(UART_NUM uart_num,U_8* pu8_data);
void  uart_receive_int_enable(UART_NUM uart_num);



#endif /* UART_H_ */