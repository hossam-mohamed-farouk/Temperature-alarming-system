/*
 * SPI.c
 *
 * Created: 6/7/2020 10:10:56 AM
 *  Author: H
 */ 

#include "SPI.h"

void spi_init(SPI_MODE spi_mode)
{
	switch(spi_mode)
	{
		case MODE_MASTER:
		/*OUTOUT*/
		set_bit(SPI_DDR,SPI_MOSI);
		set_bit(SPI_DDR,SPI_SCK);
		set_bit(SPI_DDR,SPI_SS);
		/*INPUT*/
		clear_bit(SPI_DDR,SPI_MISO);
		/*Master Mode select*/
		set_bit(SPCR,MSTR);
		/*Unselect for slave*/
		set_bit(SPI_PORT,SPI_SS);
		break;
		
		case MODE_SLAVE:
		/*OUTOUT*/
		set_bit(SPI_DDR,SPI_MISO);
		/*INPUT*/
		clear_bit(SPI_DDR,SPI_MOSI);
		clear_bit(SPI_DDR,SPI_SCK);
		clear_bit(SPI_DDR,SPI_SS);
		/*Slave Mode select*/
		clear_bit(SPCR,MSTR);
		break;
	}
	/*Enable SPI*/
	set_bit(SPCR,SPE);	
	//_delay_ms();
}

U_8  spi_tranceive(U_8 u8_data)
{
	/*Update Data reg*/
	SPDR = u8_data;		/*shift started*/
	/*Wait for shift complete flag*/
	while(!(SPSR&(1<<SPIF)));
	/*Return data reg*/
	return SPDR;
}