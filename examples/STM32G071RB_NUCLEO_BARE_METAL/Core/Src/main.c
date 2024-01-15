/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <string.h>

#include "main.h"
#include "core_init.h"
#include "lcd_hd44780.h"
#include "tim_delay.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define SHIFT_DELAY 350

const char *demo_tekst = {"Congratulation, you have just run LCD demo example on STM32G071RB Nucleo eval board."};
const char *demo_title = {"LCD HD44780 Demo"};

static void lcd_buf_slide_str_in(const char *str, enum LCD_LINES lcd_line, uint16_t speed);
static void lcd_buf_slide_str_out(const char *str, enum LCD_LINES lcd_line, uint16_t speed);

uint8_t j = 0;
uint8_t i = 0;

int main(void)
{
  core_init();

  lcd_init();
  lcd_buf_str(demo_title);
  lcd_update();
	for(;;)
  {
    lcd_buf_slide_str_in(demo_tekst, LINE_2, SHIFT_DELAY);
    lcd_buf_slide_str_out(demo_tekst, LINE_2, SHIFT_DELAY);
  }
}


void lcd_buf_slide_str_out(const char *str, enum LCD_LINES lcd_line, uint16_t speed)
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

void lcd_buf_slide_str_in(const char *str, enum LCD_LINES lcd_line, uint16_t speed)
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