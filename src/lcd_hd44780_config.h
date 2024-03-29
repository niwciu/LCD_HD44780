/**
 * @file lcd_hd44780_config.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.2
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 * @addtogroup LCD_HD44780_lib_API
 *
 */

#ifndef _LCD_HD44780_CONFIG_H_
#define _LCD_HD44780_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    // clang-format off
#define ON      1
#define OFF     0
#define HIGH    1
#define LOW     0

/************************************  LCD HARDWARE SETTINGS *******************************
 *   LCD_TYPE -> Set one of the predefined types:
 *               2004 -> 4 lines 20 characters per line
 *               1604 -> 4 lines 16 characters per line
 *               1602 -> 2 lines 16 characters per line
 *   USE_RW_PIN -> Defines HW connection between LCD and uC
 *               ON - when the RW pin is connected
 *               OFF - when the RW pin is not connected
 ********************************************************************************************/
#define LCD_TYPE                1602
#define USE_RW_PIN              OFF 

#define LCD_BCKL_PIN_EN_STATE   HIGH

#define LCD_BUFFERING           ON

/********************************  LCD LIBRARY COMPILATION SETTINGS ************************
 *      Setting USE_(procedure name) to:
 *          ON  - add specific procedure to compilation
 *          OFF - exclude specific procedure from compilation
********************************************************************************************/
#define USE_DEF_CHAR_FUNCTION           ON
#define USE_LCD_INT                     ON
#define USE_LCD_HEX                     ON
#define USE_LCD_BIN                     ON

#define USE_LCD_CURSOR_HOME             ON
#define USE_LCD_CURSOR_ON               ON
#define USE_LCD_CURSOR_OFF              ON
#define USE_LCD_BLINKING_CURSOR_ON      ON

#if LCD_BUFFERING == ON
#define USE_LCD_BUF_INT                 ON
#define USE_LCD_BUF_HEX                 ON
#define USE_LCD_BUF_BIN                 ON
#endif


/********************  definitions of Line address for different LCD screens ****************/
//https://web.alfredstate.edu/faculty/weimandn/lcd/lcd_addressing/lcd_addressing_index.html

#if LCD_TYPE ==1604
#define LCD_Y   4 
#define LCD_X   16 
#define LCD_LINE1_ADR   0x00 
#define LCD_LINE2_ADR   0x40 
#define LCD_LINE3_ADR   0x10 
#define LCD_LINE4_ADR   0x50 
#endif

#if LCD_TYPE==2004
#define LCD_Y   4 
#define LCD_X   20 
#define LCD_LINE1_ADR   0x00 
#define LCD_LINE2_ADR   0x40 
#define LCD_LINE3_ADR   0x14 
#define LCD_LINE4_ADR   0x54 
#endif

#if LCD_TYPE==1602
#define LCD_Y   2 
#define LCD_X   16 
#define LCD_LINE1_ADR   0x00 
#define LCD_LINE2_ADR   0x40 
#endif

    // clang-format on

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD44780_CONFIG_H_ */
