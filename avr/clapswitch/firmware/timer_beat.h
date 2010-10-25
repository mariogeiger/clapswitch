/*
 *  timer_beat.h
 *  clapswitch
 *
 *  Created by Mario on 18.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#ifndef TIMER_BEAT_H
#define TIMER_BEAT_H

#include <avr/interrupt.h>

#if defined (__AVR_ATmega8515__)

#	define START_TIMER_BEAT TIMSK |= (1<<OCIE0);

#	define STOP_TIMER_BEAT TIMSK &= ~(1<<OCIE0);

#	define TIMER_BEAT_ISRUNNING (TIMSK & (1<<OCIE0))

#elif defined (__AVR_ATmega48__)

#	define START_TIMER_BEAT TIMSK0 |= (1<<OCIE0A);

#	define STOP_TIMER_BEAT TIMSK0 &= ~(1<<OCIE0A);

#	define TIMER_BEAT_ISRUNNING (TIMSK0 & (1<<OCIE0A))

#endif


extern volatile uint8_t beat;

void initialize_timer_beat();

#endif
