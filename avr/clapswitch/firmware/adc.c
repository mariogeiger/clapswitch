/*
 *  adc.c
 *  clapswitch
 *
 *  Created by Mario on 09.12.10.
 *  Copyright 2010 aucune. All rights reserved.
 *
 */

#include "adc.h"

void initialize_adc()
{
	ADMUX = (1<<REFS0); // Vref : 5.0V
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1); //set clock divisor 64
	ADMUX |= (1<<MUX0); // ADC1
	DDRC &= ~(1<<1);

	PRR &= ~(1<<PRADC); // disable power reduce
	ADCSRA |= (1<<ADEN); // enable ADC
}