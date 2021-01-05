/*
 * twi_eeprom.h
 *
 * Created: 6/10/2020 1:35:41 PM
 *  Author: H
 */ 


#ifndef TWI_EEPROM_H_
#define TWI_EEPROM_H_

#include "TWI.h"

#define EEPROM_SLA	0XA0

void twi_eeprom_init(void);
U_8  twi_eeprom_read_byte(U_16 u16_rom_addr);
void twi_eeprom_write_byte(U_16 u16_rom_addr,U_8 u8_data);



#endif /* TWI_EEPROM_H_ */