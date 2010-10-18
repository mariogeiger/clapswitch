/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t rec_beat[20];
uint8_t rec_size = 0;

uint8_t tmp_beat[20];
uint8_t tmp_size = 0;

uint8_t counter = 0;
uint8_t record = 0;

uint8_t i;
uint16_t m, n;
uint16_t d, e;

ISR(INT0_vect)
{
	if (timer_run()) {
		start_timer();
		
		if (record) {
			rec_size = 0;
		} else {
			tmp_size = 0;
		}

	} else {
		if (record) {
			rec_beat[rec_size] = counter;
			rec_size++;
			counter = 0;
		} else {
			if (tmp_size < rec_size) {
				tmp_beat[tmp_size] = counter;
				counter = 0;
			}
			
			tmp_size++;
			
			if (tmp_size == rec_size) {
				stop_timer();
				check_beat();
			}
		}
	}
}

ISR(TIMER0_COMPA_vect)
{
	counter++;
	if (counter == 0) {
		stop_timer();
	}
}

void start_timer()
{
	TIMSK0 |= (1<<OCIE0A);
}

void stop_timer()
{
	TIMSK0 &= ~(1<<OCIE0A);
	record = 0;
}

uint8_t timer_run()
{
	return TIMSK0 & (1<<OCIE0A);
}

void check_beat()
{
	for (i = 1; i < rec_size; ++i) {
        m = rec_beat[0] * tmp_beat[i];
        n = tmp_beat[0] * rec_beat[i];
		
        if (m > n)
            d = m - n;
        else
            d = n - m;
		
        e = (m + n) / 4;
				
        if (d > e) {
				// test fail
            return;
        }
    }
		// test passed
	PORTC ^= (1<<3);
}

int main(void)
{
		// external interupt
	EICRA = (1<<ISC01);
	EIMSK = (1<<INT0);
	SREG |= 0x80;
 
		// timer 0
	TCCR0A = (1<<WGM01);
	TCCR0B = 0x3;
	OCR0A  = 23;
	TCNT0  = 0x00;
	TIMSK0 = (1<<OCIE0A);
	
	DDRC |= (1<<3);
	
    for(;;){
		if (PINC & (1<<2)) {
			stop_timer();
			record = 1;
		}
    }

    return 0;
}
