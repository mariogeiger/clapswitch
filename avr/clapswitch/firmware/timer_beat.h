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

#define START_TIMER_BEAT TIMSK0 |= (1<<OCIE0A);

#define STOP_TIMER_BEAT TIMSK0 &= ~(1<<OCIE0A);

#define TIMER_BEAT_ISRUNNING (TIMSK0 & (1<<OCIE0A))


extern volatile uint8_t beat;

void initialize_timer_beat();

#endif
