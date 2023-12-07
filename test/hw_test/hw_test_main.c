#include "hw_test_main.h"
#include "lcd_hd44780.h"
#ifdef AVR
#include <util/delay.h>
#endif
#ifdef STM
#include "tim_delay.h"
#endif

void main_hw_test(void)
{
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

    while(1);
}