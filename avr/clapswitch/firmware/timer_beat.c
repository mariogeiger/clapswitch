/*
 *  timer_beat.c
 *  clapswitch
 *
 *  Created by Mario on 18.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "timer_beat.h"
#include "in_out.h"

volatile uint8_t beat;

#if defined (__AVR_ATmega8515__)
ISR(TIMER0_COMP_vect)

#elif defined (__AVR_ATmega48__)
ISR(TIMER0_COMPA_vect)

#endif
{
	beat++;
	if (beat == 0) {
		STOP_TIMER_BEAT;
		RECLEDOFF;
	}
}

void initialize_timer_beat()
{
#if defined (__AVR_ATmega8515__)
	
	TCCR0  = (1<<WGM01); // CTC
	TCCR0 |= (1<<CS02); // 256
	OCR0   = 180; // ~12ms
	
#elif defined (__AVR_ATmega48__)
	
	TCCR0A = (1<<WGM01); // CTC
	TCCR0B = (1<<CS02) | (1<<CS00); // 1024
	OCR0A  = 90; // ~12ms
	
#endif
	
	
	beat = 0;
}
