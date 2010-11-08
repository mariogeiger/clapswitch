/*
 *  in-out.h
 *  clapswitch
 *
 *  Created by Mario on 19.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#ifndef IN_OUT_H
#define IN_OUT_H

#include <avr/io.h>

#if defined (__AVR_ATmega8515__)

	// opto
#	define OPTOSW     PORTC ^=  (1<<2);
#	define OPTOON     PORTC &= ~(1<<2);
#	define OPTOOFF    PORTC |=  (1<<2);
#	define OPTO       (PINC & (1<<2))

	// rec led
#	define RECLEDON   PORTC &= ~(1<<1);
#	define RECLEDOFF  PORTC |=  (1<<1);

	// rec button
#	define RECBUT     (~PIND & (1<<1))

	// clap button
#	define CLAPBUT    (~PIND & (1<<2))

	// debug
#	define DBGLEDSW   PORTC ^=  (1<<0);
#	define DBGLEDON   PORTC &= ~(1<<0);
#	define DBGLEDOFF  PORTC |=  (1<<0);

#elif defined (__AVR_ATmega48__)

	// opto
#	define OPTOSW     PORTC ^=  (1<<2);
#	define OPTOON     PORTC &= ~(1<<2);
#	define OPTOOFF    PORTC |=  (1<<2);
#	define OPTO       (PINC & (1<<2))

	// rec led
#	define RECLEDON   PORTC &= ~(1<<1);
#	define RECLEDOFF  PORTC |=  (1<<1);

	// rec button
#	define RECBUT     (PIND & (1<<1))

#endif

void initialize_in_out();

#endif /* IN_OUT_H */
