/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"
#include "lcd_hd44780.h"

#define SHIFT_DELAY 300
enum 
{
    slide_in_init,
    slide_in,
    slide_out_init,
    slide_out,
};

const char *demo_tekst = {"Congratulation, you have just run LCD demo example on ESP8266 using ESP826 NONOS SDK"};
// const char *demo_tekst = {"Congratulation, you hav SDK\0"};
const char *demo_title = {"LCD HD44780 Demo\0"};

static void lcd_buf_slide_str_in(const char *str, enum LCD_LINES_e lcd_line);
static void lcd_buf_slide_str_out(const char *str, enum LCD_LINES_e lcd_line);
static void blink_backlight(uint8_t blinks_no);

uint8_t j = 0;
uint8_t i = 0;
uint8_t shift_str_state_machine=0;

static os_timer_t  lcd_shift_timer;


void ICACHE_FLASH_ATTR lcd_update_cb(void *arg)
{
    switch(shift_str_state_machine)
    {
    case slide_in_init:
        lcd_buf_cls();
        lcd_buf_str(demo_title);
        lcd_update();
        i = LCD_X - 1;
        shift_str_state_machine=slide_in;
    case slide_in:
        lcd_buf_slide_str_in(demo_tekst,LINE_2);
        if(i==C1) shift_str_state_machine=slide_out_init;
        break;
    case slide_out_init:
        j=0;
        shift_str_state_machine=slide_out;
    case slide_out:
        lcd_buf_slide_str_out(demo_tekst,LINE_2);
        if(j > strlen(demo_tekst)) shift_str_state_machine=slide_in_init;
        break;
    default:
        shift_str_state_machine=slide_in_init;
        break;
    }

}

void ICACHE_FLASH_ATTR lcd_blink_cb(void *arg)
{
    static uint8_t blink_cnt=6;
    if((blink_cnt % 2)==0)
    {
        lcd_disable_backlight();
    }
    else
    {
        lcd_enable_backlight();  
    }
    if(--blink_cnt==0)
    {
        os_timer_disarm(&lcd_shift_timer);
        os_timer_setfn(&lcd_shift_timer,lcd_update_cb,NULL);
        os_timer_arm(&lcd_shift_timer,SHIFT_DELAY,1);
    }
}

void ICACHE_FLASH_ATTR user_init(void)
{

    lcd_init();
    lcd_enable_backlight();
    lcd_str(demo_title);

    os_timer_disarm(&lcd_shift_timer);
    os_timer_setfn(&lcd_shift_timer,lcd_blink_cb,NULL);
    os_timer_arm(&lcd_shift_timer,500,1);
}

static void lcd_buf_slide_str_out(const char *str, enum LCD_LINES_e lcd_line)
{
    
        uint8_t str_end_flag = 0;
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
        j++;
}

static void lcd_buf_slide_str_in(const char *str, enum LCD_LINES_e lcd_line)
{
        
        lcd_buf_locate(lcd_line, i);
        for (uint8_t j = 0; j < (LCD_X - i); j++)
        {
            lcd_buf_char(str[j]);
        }
        lcd_update();
        i--;
}
