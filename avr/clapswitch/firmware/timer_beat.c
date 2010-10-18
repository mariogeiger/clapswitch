/*
 *  timer_beat.c
 *  clapswitch
 *
 *  Created by Mario on 18.10.10.
 *  Copyright 2010 aucune. All rights reserved.
 *
 */

#include "timer_beat.h"

volatile uint8_t beat;

ISR(TIMER0_COMPA_vect)
{
	beat++;
	if (beat == 0) {
		STOP_TIMER_BEAT;
	}
}

void initialize_timer_beat()
{
	TCCR0A = (1<<WGM01); // CTC
	TCCR0B = (1<<CS02) | (1<<CS00); // 1024
	OCR0A  = 90; // ~12ms
}
