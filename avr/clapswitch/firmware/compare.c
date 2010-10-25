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
#define TOLERANCE 40

uint8_t i, j;
uint16_t m, n;
uint16_t delta;

void compare()
{
	for (i = rec_size - 1, j = tmp_pos - 1;
		 i > 0; --i, --j) {
		
		if (j >= MAXIMUM_BEAT) {
			j = MAXIMUM_BEAT - 1;
		}
		
		m = rec_beat[i - 1] * tmp_beat[j];
		n = tmp_beat[j - 1] * rec_beat[i];
		
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
