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
	// opto
	DDRB = (1<<2);
	OPTOOFF;

	// recled
	DDRB |= (1<<1);
	RECLEDOFF;
}
