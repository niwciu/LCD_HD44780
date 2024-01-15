#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "project_config.h"
#if DEBUG_CONSOLE == ON
#include "debug.h"
#endif
#include "lcd_hd44780.h"

#define SHIFT_DELAY 300

const char *demo_tekst = {"Congratulation, you have just run LCD demo example."};
const char *demo_title = {"LCD HD44780 Demo"};

static void lcd_buf_slide_str_in(const char *str, enum LCD_LINES lcd_line, uint16_t speed);
static void lcd_buf_slide_str_out(const char *str, enum LCD_LINES lcd_line, uint16_t speed);
static void blink_backlight(uint8_t blinks_no);

uint8_t j = 0;
uint8_t i = 0;

int main(void)
{

#if DEBUG_CONSOLE == ON
    // Init the debug UART allowing us to use `printf`
    debug_console_init();
#endif
    lcd_init();
    lcd_enable_backlight();
    lcd_buf_str(demo_title);
    lcd_update();
    blink_backlight(3);
    while (1)
    {
        lcd_buf_slide_str_in(demo_tekst, LINE_2, SHIFT_DELAY);
        lcd_buf_slide_str_out(demo_tekst, LINE_2, SHIFT_DELAY);
    }
    return 0;
}

static void lcd_buf_slide_str_out(const char *str, enum LCD_LINES lcd_line, uint16_t speed)
{
    uint8_t str_end_flag = 0;
    for (j = 0; j <= strlen(str); j++)
    {
        _delay_ms(speed);
        lcd_buf_locate(lcd_line, C1);
        for (i = 0; i < LCD_X; i++)
        {
            if ((str[j + i] != '\0') && (str_end_flag == 0))
            {
                lcd_buf_char(str[j + i]);
            }
            else
            {
                str_end_flag = 0xFF;
                lcd_buf_char(' ');
            }
        }
        str_end_flag = 0;
        lcd_update();
    }
}

static void lcd_buf_slide_str_in(const char *str, enum LCD_LINES lcd_line, uint16_t speed)
{
    for (i = LCD_X - 1; i > C1; i--)
    {
        _delay_ms(speed);
        lcd_buf_locate(lcd_line, i);
        for (uint8_t j = 0; j < (LCD_X - i); j++)
        {
            lcd_buf_char(str[j]);
        }
        lcd_update();
    }
}

static void blink_backlight(uint8_t blinks_no)
{
    for(uint8_t i=0; i<blinks_no; i++)
    {
        lcd_disable_backlight();
        _delay_ms(500);
        lcd_enable_backlight();
        _delay_ms(500);
    }
}
