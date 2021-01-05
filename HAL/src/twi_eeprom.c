/*
 * twi_eeprom.c
 *
 * Created: 6/10/2020 1:36:00 PM
 *  Author: H
 */ 
#include "twi_eeprom.h"

void twi_eeprom_init(void)
{
	twi_init();
}

U_8  twi_eeprom_read_byte(U_16 u16_rom_addr)
{
	U_8 u8_data = 0;
	twi_start();
	twi_write_byte((EEPROM_SLA) | (U_8)((u16_rom_addr & 0x0700)>>7),SC_MT_SLA_ACK);  //(U_8)((u16_rom_addr >> 7 ) & 0x0E
	twi_write_byte((U_8)(u16_rom_addr & 0XFF),SC_MT_DATA_ACK); 
	twi_restart();
	twi_write_byte((EEPROM_SLA | 0X01),SC_MR_SLA_ACK); 
	twi_read_byte(&u8_data,SC_MR_DATA_NOTACK);
	twi_stop();
	_delay_ms(10);
	return u8_data;
}

void twi_eeprom_write_byte(U_16 u16_rom_addr,U_8 u8_data)
{
	twi_start();
	twi_write_byte((EEPROM_SLA) | (U_8)((u16_rom_addr & 0x0700)>>7),SC_MT_SLA_ACK);  //(U_8)((u16_rom_addr >> 7 ) & 0x0E
	twi_write_byte((U_8)(u16_rom_addr & 0XFF),SC_MT_DATA_ACK); 
	twi_write_byte(u8_data,SC_MT_DATA_ACK); 
	twi_stop();	
	_delay_ms(10);
}