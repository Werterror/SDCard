#include <avr/io.h>
#include <stdio.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif
#include <util/setbaud.h>

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */

void uart_init(unsigned int baud) {


	//UBRRH = UBRRH_VALUE;
	//UBRRL = UBRRL_VALUE;
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	#if USE_2X
	UCSRA |= _BV(U2X0);
	#else
	UCSRA &= ~(_BV(U2X));
	#endif
	UCSRB = (1<<RXEN) | (1<<TXEN);   /* Enable RX and TX */
	UCSRC = (1<<URSEL) | (3<<UCSZ0); /* 8-bit data */


}
//UART_TX - write out, output to terminal
void uart_putchar(char c, FILE *stream) {
	if (c == '\n') {
		uart_putchar('\r', stream);
	}
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
}


//UART_RX - input from terminal
char uart_getchar(FILE *stream) {

	loop_until_bit_is_set(UCSRA, RXC);

	//while ( !(UCSRA & (1<<RXC)) );
	return UDR;
}
void USART_TX(unsigned char data){
	while( !(UCSRA & (1<<UDRE)) );
	UDR = data;
}
