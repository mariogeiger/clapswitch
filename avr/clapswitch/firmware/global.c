/*
 *  global.c
 *  clapswitch
 *
 *  Created by Mario on 25.10.10.
 *  Copyright 2010 aucune. All rights reserved.
 *
 */

#include "global.h"
#include <avr/eeprom.h>

volatile uint8_t record_state;

uint8_t EEMEM eep_beat[MAXIMUM_BEAT];
uint8_t EEMEM eep_size;

volatile uint8_t rec_beat[MAXIMUM_BEAT];
volatile uint8_t rec_size;

volatile uint8_t tmp_beat[MAXIMUM_BEAT];
volatile uint8_t tmp_pos;

void initialize_global()
{
	record_state = DISABLED;

	eeprom_busy_wait();
	
	rec_size = eeprom_read_byte(&eep_size);
	
	uint8_t i;
	for (i = 0; i < rec_size; ++i)
		rec_beat[i] = eeprom_read_byte(&eep_beat[i]);

	tmp_pos = 0;
}
