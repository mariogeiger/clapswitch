/*
 *  main.c
 *  clapswitch
 *
 *  Created by Mario on 18.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include "timer_beat.h"
#include "interrupt_clap.h"

	//! tolerance in per cent
#define TOLERANCE 50

uint8_t i;
uint16_t m, n;
uint16_t delta;
uint8_t fail;

int main(void)
{	
	initialize_timer_beat();
	
	initialize_interrupt_clap();
	
	DDRC  =          (1<<3) | (1<<4); // button | switch | led rec
	PORTC = (1<<2) | (1<<3) | (1<<4); // pullup |  off   |   off

	eeprom_busy_wait();
	rec_size = eeprom_read_byte(&eep_size);
	for (i = 0; i < rec_size; ++i) {
		rec_beat[i] = eeprom_read_byte(&eep_beat[i]);
	}
	
	sei();
	
    for(;;){
		if (PINC & (1<<2)) {
			STOP_TIMER_BEAT;
			record_state = PENDING;
		}
		
		if (record_state == RUNNING)
			PORTC &= ~(1<<4);
		else
			PORTC |= (1<<4);
		
		if (flag_clap & (1<<NEEDCOMPARE)) {
			flag_clap &= ~(1<<NEEDCOMPARE);
			
			fail = 0;
			for (i = 1; i < rec_size; ++i) {
				m = rec_beat[i - 1] * tmp_beat[i];
				n = tmp_beat[i - 1] * rec_beat[i];
				
				if (m > n)
					delta = m - n;
				else
					delta = n - m;
								
				if (delta > (m + n) / (200 / TOLERANCE)) {
						// test fail
					fail = 1;
					break;
				}
			}
				// test passed
			if (!fail) {
				PORTC ^= (1<<3);
			}
		}
    }

    return 0;
}
