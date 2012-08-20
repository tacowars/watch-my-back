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

#define LED PB2
unsigned n;

// just use this to wake from sleep
EMPTY_INTERRUPT(PCINT0_vect);

ISR(TIM1_OVF_vect) {
	/* change alarm to make klaxon sound */
	OCR0A = OCR0A > 254 ? 200 : 255;
}


static void config_hardware(void) {
	   /* disable interrupts globally */
	     cli();

		/* init software serial tx and say hi */
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
	 	DDRB = _BV(PB1); // enable OC0B as output

	 	/* Timer 1 - LFO for altering pitch */
	 	TCCR1 |= _BV(CS11) | _BV(CS13); // CK/32
	 	TIMSK |= _BV(TOIE1); // overflow interrupt

        /* turn on internal pull-up resistor for the sensor */
        //PORTB |= _BV(PB4);
	    DDRB |= (0 << PB4);

	    /* pin change interrupt setup for PIR sensor  */
	    GIMSK |= _BV(PCIE);
	    PCMSK |= _BV(PCINT4);

	    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	    /* showtime: enable interrupts */
	    sei();
}

int main(void)
{
	config_hardware();

	while (1) {

		if (!bit_is_set(PINB, PB4)) { // If PIR sensor is low, sleep.
			sleep_mode();
		}
	};

	return 0;
}
