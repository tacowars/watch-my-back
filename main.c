/*
 *  PIR alarm
 *  Created on: Aug 17, 2012
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include "libs/trace.h"

#define LED PB3
unsigned n;


// wake from sleep
//EMPTY_INTERRUPT();
ISR(PCINT0_vect) {
	/* turn on status LED */
	PORTB |= _BV(LED); //ON!
}

ISR(TIM1_OVF_vect) {
	/* change alarm frequency to make klaxon sound.
	 * switching clock to get 4000hz and ~3000hz accuracy */
	if (OCR0A == 255) {
		OCR0A = 4;
		OCR0B = 2;
		TCCR0B |= _BV(CS01);
	} else {
		OCR0A = 255;
		OCR0B = 128;
		TCCR0B &= ~_BV(CS01);
	}
}


static void config_hardware(void) {
	   /* disable interrupts globally */
	     cli();

		/* power */
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		ADCSRA = 0x00; //Disable ADC
		PORTB = 0x00; // Disable any outputs

		/* init software serial tx (disabled in trace.h) */
		char bootmsg[] = "-- Tiny85 Alarm Boot --";
		dbg_tx_init();
		dbg_putstring(bootmsg);

		/* status led */
		DDRB |= (1 << LED);
		PORTB |= _BV(LED); //ON!

		/* crude delay to allow PIR sensor to initialize */
		n = 0;
		while (n <= 9)
		{
			_delay_ms(5000);
			n++;
		}

		/* Timer 0 - the oscillator */
	    TCCR0A |= _BV(WGM00) | _BV(WGM01) | _BV(COM0B0) | _BV(COM0B1); // Mode 7 fast PWM, TOP=OCRA
	    TCCR0B |= _BV(WGM02) | _BV(CS00); // Mode 7 fast PWM, TOP=OCRA.
	    OCR0A = 255;
	    OCR0B = 128;
	 	DDRB |= _BV(PB1); // enable OC0B as output

	 	/* Timer 1 - LFO for altering pitch */
	 	TCCR1 |= _BV(CS11) | _BV(CS13); // CK/32
	 	TIMSK |= _BV(TOIE1); // overflow interrupt

	 	/* PIR sensor setup */
	    DDRB |= (0 << PB4);
	    GIMSK |= _BV(PCIE); // pin change interrupt
	    PCMSK |= _BV(PCINT4); // triggers PCINT0_vect

	    /* showtime: enable interrupts */
	    sei();
}

int main(void)
{
	config_hardware();

	while (1) {

		if (!bit_is_set(PINB, PB4)) { // If PIR sensor is low, sleep.
			PORTB &= ~_BV(LED); // turn LED off
			sleep_mode();
		}
	};
	return 0;
}
