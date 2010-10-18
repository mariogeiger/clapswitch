/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_beat.h"
#include "interrupt_clap.h"

uint8_t i;
uint16_t m, n;
uint16_t d;

int main(void)
{
	initialize_timer_beat();
	
	initialize_interrupt_clap();
	
	DDRC |= (1<<3); // switch on/off
	
	sei();
	
    for(;;){
		if (PINC & (1<<2)) {
			STOP_TIMER_BEAT;
			record_state = PENDING;
		}
		
		if (flag_clap & (1<<NEEDCOMPARE)) {
			flag_clap &= ~(1<<NEEDCOMPARE);
			
			for (i = 1; i < rec_size; ++i) {
				m = rec_beat[i - 1] * tmp_beat[i];
				n = tmp_beat[i - 1] * rec_beat[i];
				
				if (m > n)
					d = m - n;
				else
					d = n - m;
								
				if (d > (m + n) / 4) {
						// test fail
					return;
				}
			}
				// test passed
			PORTC ^= (1<<3);			
		}
    }

    return 0;
}
