/*
 *  interrupt_clap.c
 *  clapswitch
 *
 *  Created by Mario on 18.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "interrupt_clap.h"
#include "timer_beat.h"
#include "global.h"

volatile uint8_t flag_clap;

volatile uint8_t tmp_size;


ISR(INT0_vect)
{
	if (!TIMER_BEAT_ISRUNNING) {
		
		beat = 0;
		START_TIMER_BEAT;
		
		switch (record_state) {
			case RUNNING:
				record_state = DISABLED;
				if (eeprom_is_ready())
					eeprom_write_byte(&eep_size, rec_size);
			case DISABLED:
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
			if (eeprom_is_ready())
				eeprom_write_byte(&eep_beat[rec_size], beat);
			
			rec_size++;
			
			beat = 0;
			
			if (rec_size == MAXIMUM_BEAT) {
				STOP_TIMER_BEAT;
			}
			
		} else {
			
			tmp_beat[tmp_pos] = beat;
			tmp_pos++;
			
			beat = 0;
			
			if (tmp_pos >= MAXIMUM_BEAT) {
				tmp_pos = 0;
			}
			
			if (tmp_size >= rec_size) {
				flag_clap |= (1<<NEEDCOMPARE);
			} else {
				tmp_size++;
			}
		}
	}
}

void initialize_interrupt_clap()
{
#if defined (__AVR_ATmega8515__)
	
	MCUCR = (1<<ISC01) | (1<<ISC00); // rising edge	
	GICR = (1<<INT0); // int0 enabled
	
	SREG  = 0x80; // ?
	
#elif defined (__AVR_ATmega48__)
	
	EICRA = (1<<ISC01) | (1<<ISC00); // rising edge	
	EIMSK = (1<<INT0); // int0 enabled
	
	SREG  = 0x80; // ?
	
#endif

		
	flag_clap = 0;
	tmp_size = 0;
}
