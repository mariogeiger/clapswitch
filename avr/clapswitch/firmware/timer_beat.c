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

ISR(TIMER0_COMPA_vect)
{
	beat++;
	if (beat == 0) {
		STOP_TIMER_BEAT;
		RECLEDOFF;
	}
}

void initialize_timer_beat()
{
	TCCR0A = (1<<WGM01); // CTC
	TCCR0B = (1<<CS02); // 256
	OCR0A  = 30; // ~12ms
	
	beat = 0;
}
