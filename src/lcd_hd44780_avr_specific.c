/**
 * @file lcd_hd44780_avr_specific.c
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.2
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 */

#include "lcd_hd44780.h"
#include "lcd_hd44780_avr_specific.h"
#include <stdlib.h>
#include <string.h>

#define VAL_PREFIX_LENGHT 2

#if ((USE_LCD_INT == ON) || (USE_LCD_HEX == ON))
static void lcd_put_spaces(uint8_t empty_spaces);
#endif
#if ((LCD_BUFFERING == ON) && ((USE_LCD_BUF_INT == ON) || (USE_LCD_BUF_HEX == ON)))
static void lcd_buf_put_spaces(uint8_t empty_spaces);
#endif

#if ((USE_LCD_INT == ON) || (USE_LCD_HEX == ON))
static void lcd_put_spaces(uint8_t empty_spaces)
{
    for (uint8_t i = 0; i < empty_spaces; i++)
    {
        lcd_char(' ');
    }
}
#endif
#if LCD_BUFFERING == ON
#if ((USE_LCD_BUF_INT == ON) || (USE_LCD_BUF_HEX == ON))
static void lcd_buf_put_spaces(uint8_t empty_spaces)
{
    for (uint8_t i = 0; i < empty_spaces; i++)
    {
        lcd_buf_char(' ');
    }
}
#endif
#endif

#if USE_LCD_INT == ON
void lcd_int_AVR(int val, uint8_t width, enum LCD_alignment_e alignment)
{
    uint8_t buf_lenght = 0;
    char buffer[20]; // 19chars for 64 bit int + end char '\0'
    buffer[0] = '\0';
    itoa(val, buffer, 10);
    buf_lenght = strlen(buffer);
    if (buf_lenght >= (width))
    {
        lcd_str(buffer);
    }
    else
    {
        uint8_t empty_spaces_qty = width - buf_lenght;
        if (alignment == right)
        {
            lcd_put_spaces(empty_spaces_qty);
            lcd_str(buffer);
        }
        else
        {
            lcd_str(buffer);
            lcd_put_spaces(empty_spaces_qty);
        }
    }
}
#endif
#if USE_LCD_HEX == ON
void lcd_hex_AVR(int val, uint8_t width, enum LCD_alignment_e alignment)
{
    char buffer[17];
    buffer[0] = '\0';
    itoa(val, buffer, 16);
    static const char *prefix = {"0x"};
    if (width <= (strlen(buffer) + VAL_PREFIX_LENGHT))
    {
        lcd_str(prefix);
        lcd_str(buffer);
    }
    else
    {
        uint8_t empty_spaces_qty = width - (VAL_PREFIX_LENGHT + strlen(buffer));

        if (alignment == right)
        {
            lcd_put_spaces(empty_spaces_qty);
            lcd_str(prefix);
            lcd_str(buffer);
        }
        else
        {
            lcd_str(prefix);
            lcd_str(buffer);
            lcd_put_spaces(empty_spaces_qty);
        }
    }
}
#endif
#if USE_LCD_BIN == ON
void lcd_bin_AVR(int val, uint8_t width)
{
    char buffer[35]; // 0b 0000 0000 0000 0000 0000 0000 0000 0000
    static char const *prefix = {"0b"};
    buffer[0] = '\0';

    itoa(val, buffer, 2);
    if (width <= (strlen(buffer) + VAL_PREFIX_LENGHT))
    {
        lcd_str(prefix);
        lcd_str(buffer);
    }
    else
    {
        uint8_t zeros_qty = (width - (VAL_PREFIX_LENGHT + strlen(buffer)));
        lcd_str(prefix);
        for (uint8_t i = 0; i < zeros_qty; i++)
        {
            lcd_char('0');
        }
        lcd_str(buffer);
    }
}
#endif

#if LCD_BUFFERING == ON
#if USE_LCD_BUF_INT == ON
void lcd_buf_int_AVR(int val, uint8_t width, enum LCD_alignment_e alignment)
{
    uint8_t buf_lenght = 0;
    char buffer[20]; // 19chars for 64 bit int + end char '\0'
    buffer[0] = '\0';
    itoa(val, buffer, 10);
    buf_lenght = strlen(buffer);
    if (buf_lenght >= (width))
    {
        lcd_buf_str(buffer);
    }
    else
    {
        uint8_t empty_spaces_qty = width - buf_lenght;
        if (alignment == right)
        {
            lcd_buf_put_spaces(empty_spaces_qty);
            lcd_buf_str(buffer);
        }
        else
        {
            lcd_buf_str(buffer);
            lcd_buf_put_spaces(empty_spaces_qty);
        }
    }
}
#endif

#if USE_LCD_BUF_HEX == ON
void lcd_buf_hex_AVR(int val, uint8_t width, enum LCD_alignment_e alignment)
{
    char buffer[17];
    buffer[0] = '\0';
    itoa(val, buffer, 16);
    static const char *prefix = {"0x"};
    if (width <= (strlen(buffer) + VAL_PREFIX_LENGHT))
    {
        lcd_buf_str(prefix);
        lcd_buf_str(buffer);
    }
    else
    {
        uint8_t empty_spaces_qty = width - (VAL_PREFIX_LENGHT + strlen(buffer));

        if (alignment == right)
        {
            lcd_buf_put_spaces(empty_spaces_qty);
            lcd_buf_str(prefix);
            lcd_buf_str(buffer);
        }
        else
        {
            lcd_buf_str(prefix);
            lcd_buf_str(buffer);
            lcd_buf_put_spaces(empty_spaces_qty);
        }
    }
}
#endif
#if USE_LCD_BUF_BIN == ON
void lcd_buf_bin_AVR(int val, uint8_t width)
{
    char buffer[35]; // 0b 0000 0000 0000 0000 0000 0000 0000 0000
    static const char *prefix = {"0b"};
    buffer[0] = '\0';

    itoa(val, buffer, 2);
    if (width <= (strlen(buffer) + VAL_PREFIX_LENGHT))
    {
        lcd_buf_str(prefix);
        lcd_buf_str(buffer);
    }
    else
    {
        uint8_t zeros_qty = (width - (VAL_PREFIX_LENGHT + strlen(buffer)));
        lcd_buf_str(prefix);
        for (uint8_t i = 0; i < zeros_qty; i++)
        {
            lcd_buf_char('0');
        }
        lcd_buf_str(buffer);
    }
}
#endif
#endif