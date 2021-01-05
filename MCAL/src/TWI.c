/*
 * TWI.c
 *
 * Created: 6/8/2020 1:15:21 PM
 *  Author: H
 */ 
#include "TWI.h"

void twi_init(void)
{
	TWBR = 32; /*100 KHz , TWPS 1:0*/
}

Bool twi_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	twi_wait();
	return ((TWSR&0XF8) == SC_START);
}

Bool twi_restart(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	twi_wait();
	return ((TWSR&0XF8) == SC_RESTART);
}

void twi_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
/*wait for TWINT == 1*/
void twi_wait(void)
{
	while (!(TWCR & (1<<TWINT)));
}

Bool twi_write_byte(U_8 u8_byte,U_8 u8_status_code)
{
	TWDR = u8_byte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	twi_wait();
	return ((TWSR&0XF8) == u8_status_code);
}

Bool twi_read_byte(U_8* pu8_byte,U_8 u8_status_code)
{
	Bool result = FALSE;
	TWCR = (1<<TWINT)|(1<<TWEN);
	/*Return ack for the slave if wanted*/
	if (u8_status_code == SC_MR_DATA_ACK)
	{
		TWCR |= (1<<TWEA);
	}
	twi_wait();
	/*Check if the operation was done successful*/
	if (((TWSR&0XF8) == u8_status_code))
	{
		(*pu8_byte) = TWDR;
		result = TRUE;
	}
	return result;
}