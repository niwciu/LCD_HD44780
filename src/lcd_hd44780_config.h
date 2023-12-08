/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-06 21:38:27 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 14:08:18
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
 *   LCD_TYPE -> set one of the predefined types:
 *               2004 -> 4 lines 20 characters per line
 *               1604 -> 4 lines 16 characters per line
 *               1602 -> 2 lines 16 characters per line
 *   USE_RW_PIN -> Defines HW connection between LCD and uC
 *               ON - when RW pin is connected
 *               OFF - when RW pin is not connected
 ********************************************************************************************/
#define LCD_TYPE       2004
#define USE_RW_PIN     OFF 

/********************  definitions of Line and collumn labels for lcd_locate ****************/
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
 *          ON  - add specific procedure to complilation
 *          OFF - exclude specific procedure from complitaion
********************************************************************************************/
#define USE_DEF_CHAR_FUNCTION           ON

#define USE_LCD_CURSOR_HOME             ON
#define USE_LCD_CURSOR_ON               ON
#define USE_LCD_CURSOR_OFF              ON
#define USE_LCD_BLINKING_CURSOR_ON      ON



#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD44780_CONFIG_H_ */