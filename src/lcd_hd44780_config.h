/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-06 21:38:27 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 13:41:57
 */

#ifndef _LCD_HD44780_CONFIG_H_
#define _LCD_HD44780_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define ON 1
#define OFF 0

#define LCD_TYPE 2004
#define USE_RW_PIN                      OFF

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