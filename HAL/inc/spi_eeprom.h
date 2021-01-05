/*
 * ext_eeprom.h
 *
 * Created: 6/7/2020 1:48:52 PM
 *  Author: H
 */ 


#ifndef SPI_EEPROM_H_
#define SPI_EEPROM_H_

#include "SPI.h"

#define INS_READ				0x03
#define INS_WRITE				0x02
#define INS_WRITE_ENABLE		0x06

void spi_eeprom_init(void);
U_8  spi_eeprom_read_byte(U_16 u16_rom_addr);
void spi_eeprom_write_byte(U_16 u16_rom_addr,U_8 u8_data);




#endif /* SPI_EEPROM_H_ */