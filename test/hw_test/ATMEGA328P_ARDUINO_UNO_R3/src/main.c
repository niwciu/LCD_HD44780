#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "project_config.h"
#if DEBUG_CONSOLE == ON
#include "debug.h"
#endif
#include "lcd_hd44780.h"

int main(void)
{

#if DEBUG_CONSOLE == ON
    // Init the debug UART allowing us to use `printf`
    debug_console_init();
#endif
    lcd_init();
    lcd_char('G');
    _delay_ms(2000);
    lcd_cls();
    lcd_def_char(pol_e,Pol_e);
    lcd_load_char_bank(&char_bank_1);
    lcd_char(pol_e);
    lcd_char(pol_o);
    lcd_char(zn_wody);
    lcd_char('l');
    while (1)
    {

    }
    return 0;
}