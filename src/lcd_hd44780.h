/**
 * @file lcd_hd44780.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.2
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 * @defgroup LCD_HD44780_lib_API
 * @{
 */

#ifndef _LCD_HD_44780_H_
#define _LCD_HD_44780_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#include "lcd_hd44780_def_char.h"
#include <stdbool.h>
    /**
     * @brief Labels for alignment parameter used by lcd_int() and lcd_hex() functions
     * @enum  LCD_alignment_e
     */
    enum LCD_alignment_e
    {
        left, /**< @brief pass as argument when calling lcd_int() or lcd_buf_int() or lcd_hex() or lcd_buf_hex() to set left alighment */
        right /**< @brief pass as argument when calling lcd_int() or lcd_buf_int() or lcd_hex() or lcd_buf_hex() to set right alighment */
    };
    /**
     * @brief Line labels used when calling lcd_locate() or lcd_buf_locate() function
     * @enum LCD_LINES_e
     */
    enum LCD_LINES_e
    {
        LINE_1, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to first line of LCD */
        LINE_2, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to second line of LCD */
        LINE_3, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to third line of LCD */
        LINE_4, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to fourth line of LCD */
    };

    /**
     * @enum LCD_COLUMNS_e
     * @brief Column labels used when calling lcd_locate() or lcd_buf_locate() function
     *
     */
    enum LCD_COLUMNS_e
    {
        C1,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 1'st char/collumn of LCD */
        C2,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 2'nd char/collumn of LCD */
        C3,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 3'th char/collumn of LCD */
        C4,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 4'th char/collumn of LCD */
        C5,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 5'th char/collumn of LCD */
        C6,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 6'th char/collumn of LCD */
        C7,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 7'th char/collumn of LCD */
        C8,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 8'th char/collumn of LCD */
        C9,  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 9'th char/collumn of LCD */
        C10, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 10'th char/collumn of LCD */
        C11, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 11'th char/collumn of LCD */
        C12, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 12'th char/collumn of LCD */
        C13, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 13'th char/collumn of LCD */
        C14, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 14'th char/collumn of LCD */
        C15, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 15'th char/collumn of LCD */
        C16, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 16'th char/collumn of LCD */
        C17, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 17'th char/collumn of LCD */
        C18, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 18'th char/collumn of LCD */
        C19, /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 19'th char/collumn of LCD */
        C20  /**< @brief pass as argument when calling lcd_locate() or lcd_buf_locate() to move curson to 20'th char/collumn of LCD */
    };

    extern bool LCD_BUFFER_UPDATE_FLAG;

    void lcd_init(void);
    void lcd_enable_backlight(void);
    void lcd_disable_backlight(void);
    void lcd_cls(void);

    void lcd_def_char(const uint8_t CGRAM_bank_x_char_adr, const uint8_t *def_char);
    void lcd_load_char_bank(const char_bank_struct_t *char_bank);

    void lcd_char(const char C);
    void lcd_str(const char *str);
    void lcd_int(int val, uint8_t width, enum LCD_alignment_e alignment);
    void lcd_hex(int val, uint8_t width, enum LCD_alignment_e alignment);
    void lcd_bin(int val, uint8_t width);

    void lcd_locate(enum LCD_LINES_e y, enum LCD_COLUMNS_e x);

    void lcd_home(void);
    void lcd_cursor_on(void);
    void lcd_cursor_off(void);
    void lcd_blinking_cursor_on(void);

    void lcd_buf_cls(void);
    void lcd_buf_char(const char c);
    void lcd_buf_locate(enum LCD_LINES_e y, enum LCD_COLUMNS_e x);
    void lcd_buf_str(const char *str);
    void lcd_update(void);

    void lcd_buf_int(int val, uint8_t width, enum LCD_alignment_e alignment);
    void lcd_buf_hex(int val, uint8_t width, enum LCD_alignment_e alignment);
    void lcd_buf_bin(int val, uint8_t width);
/**@}*/
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD_44780_H_ */