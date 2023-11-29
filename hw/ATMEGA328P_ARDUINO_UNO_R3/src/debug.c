#include <stdio.h>
#include <avr/io.h>

static int uart_putchar(char c, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void debug_console_init(void) {
    /* ToDo cofigure uart tha you would like to use for debug console
        eample of avr uart config for Atmega328P  shown below 
    */
    UCSR0B = (1 << TXEN0); // Enable transmitter
    UCSR0C = (1<< UCSZ00)|(1<<UCSZ01); // Set data size to 8 bits
    UBRR0L = 3; // Set baud rate to 250k
    UBRR0H = 0;

    stdout = &mystdout;		// define the output stream
}

static int uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }

    // Wait for empty transmit buffer - atmega
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;

    // Put data into buffer, sends the data
    UDR0 = c;
    return 0;
}