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
    _delay_ms(1000);
    lcd_cls();
    lcd_def_char(pol_e, Pol_e);
    lcd_load_char_bank(&lcd_cgram_bank_1);
    lcd_char(pol_e);
    lcd_char(pol_o);
    lcd_char(zn_wody);
    lcd_char('l');

    _delay_ms(1000);
    lcd_cls();
    lcd_cursor_on();
    _delay_ms(1000);
    lcd_cursor_off();
    _delay_ms(1000);
    lcd_blinking_cursor_on();
    _delay_ms(1000);
    lcd_char('1');
    _delay_ms(1000);
    lcd_home();
    lcd_char('2');
    lcd_locate(LINE_2, C8);
    lcd_char('W');
    _delay_ms(1000);
    lcd_cls();
    lcd_str("TEst");
    lcd_hex(24, 6, right);
    lcd_int(24, 6, right);
    lcd_locate(LINE_2, C1);
    lcd_bin(5, 1);
    lcd_locate(LINE_2, C8);
    lcd_bin(5, 8);
    while (1)
        ;
}