/*
 *  interrupt_clap.c
 *  clapswitch
 *
 *  Created by Mario on 18.10.10.
 *  Copyright 2010 aucune. All rights reserved.
 *
 */

#include "interrupt_clap.h"
#include "timer_beat.h"

uint8_t rec_beat[MAXIMUM_BEAT];
uint8_t rec_size;

uint8_t tmp_beat[MAXIMUM_BEAT];
uint8_t tmp_size;

uint8_t record_state;

uint8_t flag_clap;

ISR(INT0_vect)
{
	if (TIMER_BEAT_ISRUNNING) {
		
		START_TIMER_BEAT;
		
		switch (record_state) {
			case DISABLED:
			case RUNNING:
				record_state = DISABLED;
				tmp_size = 0;
				break;
			case PENDING:
				record_state = RUNNING;
				rec_size = 0;
				break;
			default:
				break;
		}
		
	} else {
		
		if (record_state == RUNNING) {
			
			rec_beat[rec_size] = beat;
			rec_size++;
			
			beat = 0;
			
			if (rec_size == MAXIMUM_BEAT) {
				STOP_TIMER_BEAT;
			}
			
		} else {
			
			tmp_beat[tmp_size] = beat;			
			tmp_size++;
			
			beat = 0;
			
			if (tmp_size == rec_size) {
				STOP_TIMER_BEAT;
				flag_clap |= (1<<NEEDCOMPARE);
			}
			
		}
	}
}

void initialize_interrupt_clap()
{
	EICRA |= (1<<ISC01) | (1<<ISC00); // rising edge	
	EIMSK = (1<<INT0); // int0 enabled
	
	SREG = 0x80; // ?
}
