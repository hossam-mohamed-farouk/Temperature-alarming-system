/*
 * adc.c
 *
 * Created: 5/31/2020 10:49:35 AM
 *  Author: H
 */ 

#include "adc.h"

void adc_init(void)
{
	ADCSRA |= (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1);
	ADMUX = 0;
}

U_16 adc_read(U_8 adc_channel)
{
	ADMUX |= (adc_channel & 0x1F);
	set_bit(ADCSRA,ADSC);
	while(!read_bit(ADCSRA,ADIF));
	set_bit(ADCSRA,ADIF);
	return ADC;
}