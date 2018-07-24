
#define F_CPU	16000000
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>

#define PORTOUT PORTB 		
#define ClearOutBit PORTOUT &= ~(0xE)	 //logical 0 on GPIO 
#define SetOutBit	PORTOUT |= 0xE		 //logical 1 on the GPIO


static void soft_delay(volatile uint16_t N)
{
	/* If volatile is not used, AVR-GCC will optimize this stuff out     */
    /* making our function completely empty                              */
	volatile uint8_t inner = 0xFF;
	while (N--) {
		while (inner--);
	}
}

double myrand(int *x)
{
	 /*linear congruential generator*/
	const int m = 100; 
	const int a = 8; 
	const int inc = 65;
	*x = ((a * (*x)) + inc) % m ; 
	return (*x / (double)m) * 65535;
}

void PWM (int delay)
{
	/*Generation PWM*/
	SetOutBit;
	soft_delay(delay);
	ClearOutBit;
	soft_delay(delay);
}

int main(void)
{
		/* Configure GPIO */
	DDRB |= 0XE;						/* set PB3, PB2, PB1 to output	 */
	PORTB |= 0xE;						/* set output to 1				 */
	volatile uint16_t  res;				/* random result				*/
	int x0 = 2;							/* start value					*/
	while(1) {
		
		// generate random number from 0 to 65536
		res = myrand(&x0);
		// imitate probability density
		if (res >= 65536) {
			PWM(2);  // maximum pwm level
			} else if (res > 50000) {
			PWM(3);
			} else if (res > 40078) {
			PWM(5);
			} else if (res > 30801) {
			PWM(7);
			} else if (res > 27524) {
			PWM(10);
			} else if (res > 24247) {
			PWM(15);
			} else if (res > 20971) {
			PWM(20);
			} else if (res > 17694) {
			PWM(25);
			} else if (res > 14417) {
			PWM(30);
			} else if (res > 11140) {
			PWM(35);
			} else if (res > 7863) {
			PWM(40);
			} else if (res > 4587) {
			PWM(45);
			} else if (res > 1965) {
			PWM(50);
			} else if (res > 1310) {
			PWM(55);
			} else if (res > 654) {
			PWM(60);
			} else {
			PWM(0);  // logical 0
		}
		 
	}
	return 0;
}