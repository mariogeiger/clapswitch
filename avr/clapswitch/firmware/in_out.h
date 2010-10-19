/*
 *  in-out.h
 *  clapswitch
 *
 *  Created by Mario on 19.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include <avr/io.h>

	// opto
#define SWITCHOPTO PORTC ^=  (1<<2);
#define OPTOON     PORTC &= ~(1<<2);
#define OPTOOFF    PORTC |=  (1<<2);

	// recled
#define RECLEDON   PORTC &= ~(1<<3);
#define RECLEDOFF  PORTC |=  (1<<3);

	// button
#define BUTTONPUSHED (PINC & (1<<4))


void initialize_in_out();
