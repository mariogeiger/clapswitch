/*
 *  global.h
 *  clapswitch
 *
 *  Created by Mario on 25.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <inttypes.h>

#define DISABLED 0
#define PENDING  1
#define RUNNING  2
extern volatile uint8_t record_state;

#define MAXIMUM_BEAT 32
extern uint8_t eep_beat[];
extern uint8_t eep_size;

extern volatile uint8_t rec_beat[];
extern volatile uint8_t rec_size;

	//! ajouter rec_beat2[]
	//! re rec_size2

extern volatile uint8_t tmp_beat[];
extern volatile uint8_t tmp_pos;

void initialize_global();

#endif
