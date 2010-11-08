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

#if defined (__AVR_ATmega8515__)
uint8_t trigger;
#endif

int main(void)
{
		//! ajouter le 2nd rythme
	initialize_global();
	
		//! rien ne change dans les entrée / sortie
	initialize_in_out();
	
		//! rien ne change avec le timer de rythme
		//! c'est enregistrer dans tmp_beat
	initialize_timer_beat();
	
		//! doit verifier la longeur du rythme selon rec_beat1 ou rec_beat2
	initialize_interrupt_clap();
		
	sei();
	
    
	for(;;){
#if defined (__AVR_ATmega8515__)
		if (CLAPBUT) {
			if (trigger > 200) {
				trigger = 0;
				clap();
			} else {
				trigger++;
			}
		} else {
			if (trigger > 0) {
				trigger--;
			}
		}
#endif
		
		if (RECBUT) {
			STOP_TIMER_BEAT;
			record_state = PENDING;
			
			RECLEDON;
		}
		
		if (flag_clap & (1<<NEEDCOMPARE)) {
			flag_clap &= ~(1<<NEEDCOMPARE);
			
				//! compare avec rec_beat1 ou rec_beat2
				//! selon la position de OPTO (optocoupleur activer ou non)
			compare();
		}
    }
	
    return 0;
}
