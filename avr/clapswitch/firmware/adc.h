/*
 *  adc.h
 *  clapswitch
 *
 *  Created by Mario on 09.12.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <inttypes.h>

#define ADC_START  ADCSRA |= (1<<ADSC);
#define ADC_RUN    (ADCSRA & (1<<ADSC))

inline uint8_t adc_value()
{
	return ADCW;
}

void initialize_adc();

#endif
