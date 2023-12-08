

#ifndef _LCD_HD_44780_H_
#define _LCD_HD_44780_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#include "lcd_hd44780_config.h"
#include "lcd_hd44780_interface.h"
#if USE_DEF_CHAR == OFF
#include "lcd_hd44780_def_char.h"
#endif

void lcd_init(void);
void lcd_cls(void);

void lcd_def_char(const uint8_t CGRAM_bank_x_char_adr, const uint8_t *def_char);
void lcd_load_char_bank(const struct char_bank_struct *char_bank);

void lcd_char(char C);

void lcd_home(void);
void lcd_cursor_on(void);
void lcd_cursor_off(void);
void lcd_blinking_cursor_on(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD_44780_H_ */