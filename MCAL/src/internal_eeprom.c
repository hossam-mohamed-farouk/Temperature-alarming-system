/*
 * internal_eeprom.c
 *
 * Created: 5/31/2020 4:45:47 PM
 *  Author: H
 */ 

#include "internal_eeprom.h"

void int_eeprom_write_byte(U_16 u16_rom_addr,U_8 u8_data)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	EEAR = u16_rom_addr;
	EEDR = u8_data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

U_8  int_eeprom_read_byte(U_16 u16_rom_addr)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address register */
	EEAR = u16_rom_addr;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}
