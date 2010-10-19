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
#include "in_out.h"
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
	initialize_in_out();
	
	initialize_timer_beat();
	
	initialize_interrupt_clap();
	
	eeprom_busy_wait();
	
	rec_size = eeprom_read_byte(&eep_size);
	
	for (i = 0; i < rec_size; ++i)
		rec_beat[i] = eeprom_read_byte(&eep_beat[i]);
	
	sei();
	
    
	for(;;){
		if (BUTTONPUSHED) {
			STOP_TIMER_BEAT;
			record_state = PENDING;
		}
		
		if (record_state == RUNNING) {
			RECLEDON;
		} else {
			RECLEDOFF;
		}
		
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
				SWITCHOPTO;
			}
		}
    }

    return 0;
}
