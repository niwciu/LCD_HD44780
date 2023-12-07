

#ifndef _LCD_HD_44780_H_
#define _LCD_HD_44780_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#include "lcd_hd44780_config.h"
#include "lcd_hd44780_interface.h"

void lcd_init(void);
void lcd_cls(void);

void lcd_char(char C);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD_44780_H_ */