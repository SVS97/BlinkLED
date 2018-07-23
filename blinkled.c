#define F_CPU	16000000
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>

#define LED 0xE		/*3 LEDs on the PB3, PB2, PB1*/


/**
 * soft_delay() - wastes CPU time crunching cycle to achieve delay
 * @N:	number of outer "while" steps.
 *
 * This is very inefficient in terms of CPU and energy usage.
 * Better way is to use timer to count time and put CPU into sleep mode to save
 * energy.
 * But soft delays are useful for very precise timings (i.e. software USB
 * implementation, 1-Wire interface, etc.)
 * See <util/delay.h> for alternative implementation
 */
static void soft_delay(volatile uint16_t N)
{
	/* If volatile is not used, AVR-GCC will optimize this stuff out     */
        /* making our function completely empty                              */
	volatile uint8_t inner = 0xFF;
	while (N--) {
		while (inner--);
	}
}
/**
 * my_delay_ms() - system delay with 
 * random time
 */
static void my_delay_ms(volatile int ms)
{
	while (0 < ms){

		_delay_ms(1);
		--ms;
	}
}

int main(void)
{
	/* Configure GPIO */
	DDRB |= LED;						/* set PB3, PB2, PB1 to output  */
	PORTB |= LED;						/* set output to 1   */
	
	while(1) {
		 
		my_delay_ms(3 + rand() % 5);	/* opportunity to work with 
		//soft_delay(20 + rand() % 60);	 * different delays			*/ 
		PORTB ^= LED;					/* switch to opposite */
		
	}
	return 0;
}
