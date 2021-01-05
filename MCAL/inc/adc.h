/*
 * adc.h
 *
 * Created: 5/31/2020 10:49:01 AM
 *  Author: H
 */ 


#ifndef ADC_H_
#define ADC_H_

#ifndef F_CPU
#define F_CPU 2000000UL
#endif

#include <util/delay.h>
#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"

#define ADC_VREF 0x20 

void adc_init(void);  /*selects Avcc as the reference voltage, it enables the ADC hardware*/

U_16 adc_read(U_8 adc_channel);		/*selects the ADC channel source based on user input, 
									then starts the conversion and waits for conversion to be completed,
									prepare and return the ADC value to the user*/





#endif /* ADC_H_ */