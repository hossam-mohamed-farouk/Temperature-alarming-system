/*
 * TWI.h
 *
 * Created: 6/8/2020 1:15:08 PM
 *  Author: H
 */ 


#ifndef TWI_H_
#define TWI_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "avr/interrupt.h"
#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"

/*Control status codes*/
#define SC_START			0X08
#define SC_RESTART			0X10

/*Master transmit status codes*/
#define SC_MT_SLA_ACK		0X18
#define SC_MT_SLA_NOTACK	0X20
#define SC_MT_DATA_ACK		0X28
#define SC_MT_DATA_NOTACK	0X30

/*Master receive status codes*/
#define SC_MR_SLA_ACK		0X40
#define SC_MR_SLA_NOTACK	0X48
#define SC_MR_DATA_ACK		0X50
#define SC_MR_DATA_NOTACK	0X58

/*100 KHZ*/
void twi_init(void);
Bool twi_start(void);
Bool twi_restart(void);
void twi_stop(void);
void twi_wait(void);

Bool twi_write_byte(U_8 u8_byte,U_8 u8_status_code);
Bool twi_read_byte(U_8* pu8_byte,U_8 u8_status_code);


#endif /* TWI_H_ */