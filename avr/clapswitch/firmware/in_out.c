/*
 *  in-out.c
 *  clapswitch
 *
 *  Created by Mario on 19.10.10.
 *  Copyright 2010 aucune. All rights reserved.
 *
 */

#include "in_out.h"

void initialize_in_out()
{		
#if defined (__AVR_ATmega8515__)

	// opto
	DDRC = (1<<2);
	OPTOOFF;

	// recled
	DDRC |= (1<<1);
	RECLEDOFF;
	
	// debug
	DDRC |= (1<<0);
	DBGLEDOFF;

#elif defined (__AVR_ATmega48__)

	// opto
	DDRC = (1<<2);
	OPTOOFF;

	// recled
	DDRC |= (1<<1);
	RECLEDOFF;

#endif
}
