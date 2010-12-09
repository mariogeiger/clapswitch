/*
 *  main.c
 *  clapswitch
 *
 *  Created by Mario on 18.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include <avr/io.h>
#include "in_out.h"
#include "timer_beat.h"
#include "interrupt_clap.h"
#include "compare.h"
#include "global.h"
#include "adc.h"

uint8_t curr_sound;
uint8_t last_sound;

int main(void)
{
	initialize_global();
	
	initialize_in_out();
	
	initialize_timer_beat();
	
	initialize_interrupt_clap();
		
	sei();
	
    
	for(;;){
		
		ADC_START;
		
		do {
			if (RECBUT) {
				STOP_TIMER_BEAT;
				record_state = PENDING;
			
				RECLEDON;
			}
		
			if (flag_clap & (1<<NEEDCOMPARE)) {
				flag_clap &= ~(1<<NEEDCOMPARE);
			
				compare();
			}
		} while (ADC_RUN);
		
		curr_sound = adc_value();
		
		if (curr_sound > last_sound * 2) {
			interrupt_clap();
		}
		
		last_sound = curr_sound;
    }
	
    return 0;
}
