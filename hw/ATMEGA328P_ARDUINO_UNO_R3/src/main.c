#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "project_config.h"
#if DEBUG_CONSOLE == ON
#include "debug.h"
#endif

int main(void)
{
    DDRB|=1<<PINB5;

#if DEBUG_CONSOLE == ON
    // Init the debug UART allowing us to use `printf`
    debug_console_init();

    printf("Debug console test PASS!\r\n");
#endif
    while (1)
    {
        PORTB |=(1<<PINB5);
        _delay_ms(500);
#if DEBUG_CONSOLE == ON
    printf("LED is OFF\n");
#endif
        PORTB &=~(1<<PINB5);
        _delay_ms(500);
#if DEBUG_CONSOLE == ON
    printf("LED is ON\n");
#endif
    }
    return 0;
}