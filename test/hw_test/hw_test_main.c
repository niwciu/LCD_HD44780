#include "hw_test_main.h"
#include "lcd_hd44780.h"
#ifdef AVR
#include <util/delay.h>
#endif
#ifdef STM
#include "tim_delay.h"
#endif

#define BASIC_FUNCTIONS_TESTS       OFF
#define BUFFERING_FUNCTION_TESTS    ON
#define LCD_BACKLIGHT_TEST          ON

#if BASIC_FUNCTIONS_TESTS == ON
static void basic_func_tests(void);
#endif
#if BUFFERING_FUNCTION_TESTS == ON
static void buffering_func_tests(void);
#endif
#if LCD_BACKLIGHT_TEST == ON
static void lcd_backlight_test(void);
#endif

void main_hw_test(void)
{
    #if LCD_BACKLIGHT_TEST == ON
    lcd_backlight_test();
    #endif
    #if BASIC_FUNCTIONS_TESTS == ON
    basic_func_tests();
    #endif
    #if BUFFERING_FUNCTION_TESTS == ON
    buffering_func_tests();
    #endif

    while (1);
}

#if BASIC_FUNCTIONS_TESTS == ON
void basic_func_tests(void)
{
    lcd_init();
    lcd_enable_backlight();
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
    _delay_ms(1000);
}
#endif 
#if BUFFERING_FUNCTION_TESTS == ON
void buffering_func_tests(void)
{
    lcd_init();
    lcd_enable_backlight();
    lcd_buf_char('G');
    lcd_buf_locate(0,2);
    lcd_buf_str("Test");
    lcd_update();
    _delay_ms(1000);
    lcd_locate(0,0);
    lcd_buf_char('a');
    lcd_update();
    _delay_ms(1000);
    lcd_buf_cls();
    lcd_load_char_bank(&lcd_cgram_bank_1);
    lcd_buf_char(pol_e);
    lcd_buf_char(pol_o);
    lcd_buf_char(zn_wody);
    lcd_update();
    _delay_ms(1000);
    lcd_buf_cls();
    #if LCD_TYPE==1602
    lcd_buf_locate(LINE_1,C16);
    lcd_buf_str("test1");
    lcd_buf_locate(LINE_2,C16);
    lcd_buf_str("test2");
    #elif LCD_TYPE==2004
    lcd_buf_locate(LINE_1,C20);
    lcd_buf_str("test1");
    lcd_buf_locate(LINE_2,C20);
    lcd_buf_str("test2");
    lcd_buf_locate(LINE_3,C20);
    lcd_buf_str("test3");
    lcd_buf_locate(LINE_4,C20);
    lcd_buf_str("test4");
    #else
    #endif
    lcd_update();
    lcd_buf_cls();
    lcd_buf_hex(24, 6, right);
    lcd_buf_int(24, 6, right);
    lcd_buf_locate(LINE_2, C1);
    lcd_buf_bin(5, 1);
    lcd_buf_locate(LINE_2, C8);
    lcd_buf_bin(5, 8);
    _delay_ms(1000);
    lcd_update();
}

static void lcd_backlight_test(void)
{
    lcd_init();
    lcd_str("LCD Backlight");
    lcd_locate(LINE_2,C1);
    lcd_str("TEST");
    for(uint8_t i=0; i<3; i++)
    {
        lcd_enable_backlight();
        _delay_ms(500);
        lcd_disable_backlight();
        _delay_ms(500);
    }

}
#endif
