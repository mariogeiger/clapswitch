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
#include "compare.h"

int main(void)
{
	initialize_in_out();
	
	initialize_timer_beat();
	
	initialize_interrupt_clap();
	
	{
		eeprom_busy_wait();
		
		rec_size = eeprom_read_byte(&eep_size);
		
		uint8_t i;
		for (i = 0; i < rec_size; ++i)
			rec_beat[i] = eeprom_read_byte(&eep_beat[i]);
	}
	
	sei();
	
    
	for(;;){
		if (BUTTONPUSHED) {
			STOP_TIMER_BEAT;
			record_state = PENDING;
			
			RECLEDON;
		}
		
		if (flag_clap & (1<<NEEDCOMPARE)) {
			flag_clap &= ~(1<<NEEDCOMPARE);
			
			compare();
		}
    }
	
    return 0;
}
