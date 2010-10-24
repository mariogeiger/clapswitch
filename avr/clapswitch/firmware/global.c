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
volatile uint8_t tmp_size;
