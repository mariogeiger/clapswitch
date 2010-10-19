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
	DDRC = (1<<2);
	OPTOOFF;
	
		// recled
	DDRC |= (1<<3);
	RECLEDOFF;
	
		// button
		// pull-up : no
}
