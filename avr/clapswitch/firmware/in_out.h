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

	// opto *16*
#define OPTOSW     PORTB ^=  (1<<2);
#define OPTOON     PORTB &= ~(1<<2);
#define OPTOOFF    PORTB |=  (1<<2);

	// rec led *15*
#define RECLEDON   PORTB &= ~(1<<1);
#define RECLEDOFF  PORTB |=  (1<<1);

	// rec button *4*
#define RECBUT     (!(PIND & (1<<2)))


void initialize_in_out();

#endif /* IN_OUT_H */
