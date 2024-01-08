/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-06 21:40:29
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-08 20:44:22
 */

#ifndef _LCD_HD_44780_H_
#define _LCD_HD_44780_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#include "lcd_hd44780_config.h"
#include "lcd_hd44780_interface.h"
#if USE_DEF_CHAR_FUNCTION == ON
#include "lcd_hd44780_def_char.h"
#endif

    enum alignment
    {
        left,
        right
    };

    void lcd_init(void);
    void lcd_cls(void);

    void lcd_def_char(const uint8_t CGRAM_bank_x_char_adr, const uint8_t *def_char);
    void lcd_load_char_bank(const struct char_bank_struct *char_bank);

    void lcd_char(const char C);
    void lcd_str(const char *str);
    void lcd_int(int val, uint8_t width, enum alignment alignment);
    void lcd_hex(int val, uint8_t width, enum alignment alignment);
    void lcd_bin(int val, uint8_t width);

    void lcd_locate(enum LCD_LINES y, enum LCD_COLUMNS x);

    void lcd_home(void);
    void lcd_cursor_on(void);
    void lcd_cursor_off(void);
    void lcd_blinking_cursor_on(void);
    
#if LCD_BUFFERING == ON
    void lcd_buf_cls(void); 
    void lcd_buf_char(const char c);
    void lcd_buf_locate(enum LCD_LINES y, enum LCD_COLUMNS x);
    void lcd_buf_str(const char *str);
    void lcd_buf_print(void);
#endif   

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD_44780_H_ */