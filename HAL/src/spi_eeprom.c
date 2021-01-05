/*
 * ext_eeprom.c
 *
 * Created: 6/7/2020 1:49:07 PM
 *  Author: H
 */ 

#include "spi_eeprom.h"

static void spi_eeprom_write_enable(void);

void spi_eeprom_init(void)
{
	spi_init(MODE_MASTER);
}

static void spi_eeprom_write_enable(void)
{
	clear_bit(SPI_PORT,SPI_SS);
	spi_tranceive(INS_WRITE_ENABLE);
	set_bit(SPI_PORT,SPI_SS);
	_delay_ms(10);
}

U_8  spi_eeprom_read_byte(U_16 u16_rom_addr)
{
	U_8 result = 0;
	clear_bit(SPI_PORT,SPI_SS);
	/*Send the read instruction with the MSB of  the rom_addr*/
	spi_tranceive(INS_READ | (((u16_rom_addr>>5) & 0x08)));  //spi_tranceive(INS_WRITE | ((u16_rom_addr>>5) & (1<<3)));
	spi_tranceive((U_8)u16_rom_addr);
	/*save the return of spi receiver then return it*/
		/*Send dummy data as we care of the return*/
	result = spi_tranceive(0x00);	
	
	set_bit(SPI_PORT,SPI_SS);
	_delay_ms(10);
	return result;
}

void spi_eeprom_write_byte(U_16 u16_rom_addr,U_8 u8_data)
{
	spi_eeprom_write_enable();
	clear_bit(SPI_PORT,SPI_SS);
	/*Send the write instruction with the MSB of  the rom_addr*/
	spi_tranceive(INS_WRITE | (((u16_rom_addr>>5) & 0x08)));  //spi_tranceive(INS_WRITE | ((u16_rom_addr>>5) & (1<<3)));
	spi_tranceive((U_8)u16_rom_addr);
	spi_tranceive(u8_data);
	 
	set_bit(SPI_PORT,SPI_SS);
	_delay_ms(10);
}

