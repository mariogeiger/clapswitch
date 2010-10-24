/*
 *  compare.c
 *  clapswitch
 *
 *  Created by Mario on 25.10.10.
 *  Copyright 2010 aucune. All rights reserved.
 *
 */

#include "compare.h"
#include "global.h"
#include "in_out.h"

	//! tolerance in per cent
#define TOLERANCE 50

uint8_t i;
uint16_t m, n;
uint16_t delta;

void compare()
{
	for (i = 1; i < rec_size; ++i) {
		m = rec_beat[i - 1] * tmp_beat[i];
		n = tmp_beat[i - 1] * rec_beat[i];
		
		if (m > n)
			delta = m - n;
		else
			delta = n - m;
		
		if (delta > (m + n) / (200 / TOLERANCE)) {
				// test fail
			return;
		}
	}
		// test passed
	SWITCHOPTO;
}
