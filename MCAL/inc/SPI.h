/*
 * SPI.h
 *
 * Created: 6/7/2020 10:11:11 AM
 *  Author: H
 */ 


#ifndef SPI_H_
#define SPI_H_

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
	MODE_MASTER,MODE_SLAVE	
}SPI_MODE;

#define SPI_PORT		PORTB
#define SPI_DDR			DDRB

#define SPI_SS			PB0
#define SPI_SCK			PB1
#define SPI_MOSI		PB2
#define SPI_MISO		PB3

void spi_init(SPI_MODE spi_mode);
U_8  spi_tranceive(U_8 u8_data);


#endif /* SPI_H_ */