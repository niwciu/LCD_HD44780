/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-06 21:39:30 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-06 22:33:11
 */


#include "lcd_hd44780.h"

static const struct LCD_IO_driver_interface_struct *LCD = NULL;

/**
 * @brief  Function that initialize LCD in 4-bit mode with or without LCD R/W Pin handling.
 * @attention LCD R/W handling should be configured in lcd_hd44780_config.h by setting USE_RW_PIN to  1 (Enable R/W Pin
 * handling) or 0 (disable R/W Pin handling).
 */
void lcd_init(void)
{
    /**************************BASIC LCD INIT - taken from DS***************************************/
    //init I/O for LCD

    // set all LCD signals to High for more than 15ms

    // send 0x03 & wait more then 4,1ms

    // send 0x03 & wait more then 100us
    
    // send 0x03 & wait more then 100us

    // send 0x02 & wait more then 100us

    // FUNCTION SET ->send cmd -> LCD in 4-bit mode, 2 rows, char size 5x7

    // DISPLAY_ON_OFF send cmd -> enable lcd

    // ENTRY MODe SET do not shift LCD shift cursor right after placing a char

    // LCD clear screen
    /*********************************END of BASIC LCD INIT***************************************/
    // define sepcial characters in LCD CGRAM

}