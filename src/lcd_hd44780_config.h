/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-06 21:38:27
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-09 21:20:52
 */

#ifndef _LCD_HD44780_CONFIG_H_
#define _LCD_HD44780_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define ON 1
#define OFF 0

    // clang-format off
/************************************  LCD HARDWARE SETTINGS *******************************
 *   LCD_TYPE -> Set one of the predefined types:
 *               2004 -> 4 lines 20 characters per line
 *               1604 -> 4 lines 16 characters per line
 *               1602 -> 2 lines 16 characters per line
 *   USE_RW_PIN -> Defines HW connection between LCD and uC
 *               ON - when the RW pin is connected
 *               OFF - when the RW pin is not connected
 ********************************************************************************************/
#define LCD_TYPE       1602
#define USE_RW_PIN     OFF 

#define LCD_BUFFERING  ON

//definitions of Line and column labels for lcd_locate 
enum LCD_LINES
{
    LINE_1,
    LINE_2,
 #if ((LCD_TYPE==2004) ||(LCD_TYPE ==1604))
    LINE_3,
    LINE_4,
#endif
};
enum LCD_COLUMNS{
    C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,
#if LCD_TYPE==2004
    C17,C18,C19,C20
#endif
};

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
