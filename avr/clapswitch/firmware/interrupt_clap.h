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

#define NEEDCOMPARE 0
extern volatile uint8_t flag_clap;

#if defined (__AVR_ATmega8515__)
void clap();
#endif

void initialize_interrupt_clap();

#endif
