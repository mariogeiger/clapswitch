/*
 *  interrupt_clap.h
 *  clapswitch
 *
 *  Created by Mario on 18.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#ifndef INTERRUPT_CLAP_H
#define INTERRUPT_CLAP_H

#include <avr/interrupt.h>
#include <avr/eeprom.h>

#define DISABLED 0
#define PENDING  1
#define RUNNING  2
extern volatile uint8_t record_state;

#define MAXIMUM_BEAT 20
extern uint8_t EEMEM eep_beat[];
extern uint8_t EEMEM eep_size;

extern volatile uint8_t rec_beat[];
extern volatile uint8_t rec_size;

extern volatile uint8_t tmp_beat[];
extern volatile uint8_t tmp_size;

#define NEEDCOMPARE 0
extern volatile uint8_t flag_clap;

void initialize_interrupt_clap();

#endif
