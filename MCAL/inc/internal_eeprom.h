/*
 * internal_eeprom.h
 *
 * Created: 5/31/2020 4:45:37 PM
 *  Author: H
 */ 


#ifndef INTERNAL_EEPROM_H_
#define INTERNAL_EEPROM_H_

#ifndef F_CPU
#define F_CPU 2000000UL
#endif

#include <util/delay.h>
#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"

void int_eeprom_write_byte(U_16 u16_rom_addr,U_8 u8_data);
U_8  int_eeprom_read_byte(U_16 u16_rom_addr);



#endif /* INTERNAL_EEPROM_H_ */