/*
 * uart.c
 *
 * Created: 6/3/2020 2:31:06 PM
 *  Author: H
 */ 

#include "uart.h"

void uart_init(UART_NUM uart_num,U_32 baud_rate)
{
	U_16 ubrr = 0;
	ubrr = ((8000000UL) / (16*baud_rate)) - 1;
	switch(uart_num)
	{
		case UART_0:
		/* Set baud rate */
		UBRR0H = (U_8)(ubrr>>8);
		UBRR0L = (U_8)ubrr;
		/* Enable receiver and transmitter */
		//UCSR0B=(1<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
		UCSR0B = (1<<RXEN)|(1<<TXEN);
		/* Set frame format: 8data, 1stop bit */
		UCSR0C = (3<<UCSZ0);
		break;
		
		case UART_1:
		UBRR1H = (U_8)(ubrr>>8);
		UBRR1L = (U_8)ubrr;
		/* Enable receiver and transmitter */
		UCSR1B = (1<<RXEN)|(1<<TXEN);
		/* Set frame format: 8data, 1stop bit */
		UCSR1C = (3<<UCSZ0);
		break;
	}
}

void uart_send_byte(UART_NUM uart_num,U_8 u8_data)
{
	switch(uart_num)
	{
		case UART_0:
		 /* Wait for empty transmit buffer */
		 while ( !( UCSR0A & (1<<UDRE)));
		 /* Put data into buffer, sends the data */
		 UDR0 = u8_data;
		break;
		
		case UART_1:
		 /* Wait for empty transmit buffer */
		 while ( !( UCSR1A & (1<<UDRE)) );
		 /* Put data into buffer, sends the data */
		 UDR1 = u8_data;
		break;
	}
}

U_8  uart_receive_byte(UART_NUM uart_num)
{
	U_8 u8_data = 0;
	switch(uart_num)
	{
		case UART_0:
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC)) );
		/* Get and return received data from buffer */
		u8_data = UDR0;
		break;
		
		case UART_1:
		/* Wait for data to be received */
		while ( !(UCSR1A & (1<<RXC)) );
		/* Get and return received data from buffer */
		u8_data = UDR1;
		break;
	}
	return u8_data;
}

void uart_send_str(UART_NUM uart_num,U_8* pu8_str)
{
	U_32 ind = 0;
	
	while(*pu8_str != '\0')
	{
		uart_send_byte(uart_num,pu8_str[ind]);
		pu8_str ++;
	}
}

Bool uart_receive_byte_unblock(UART_NUM uart_num,U_8* pu8_data)
{
	Bool result = FALSE;
	switch(uart_num)
	{
		case UART_0:
		if (UCSR0A & (1<<RXC))
		{
			result = TRUE;
			(*pu8_data) = UDR0;
		}
		break;
		
		case UART_1:
		if (UCSR1A & (1<<RXC))
		{
			result = TRUE;
			(*pu8_data) = UDR1;
		}
		break;
	}
	return result;	
}

void  uart_receive_int_enable(UART_NUM uart_num)
{
	switch(uart_num)
	{
		case UART_0:
		/* Enable  RX complete int */
		UCSR0B |= (1<<RXCIE0);
		break;
		
		case UART_1:
		/* Enable  RX complete int */
		UCSR1B |= (1<<RXCIE1);
		break;
	}
}