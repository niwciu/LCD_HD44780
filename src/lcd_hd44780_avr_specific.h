/**
 * @file lcd_hd44780_avr_specific.h
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.2
 * @date 2024-02-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _LCD_HD_44780_AVR_SPECIFIC_H_
#define _LCD_HD_44780_AVR_SPECIFIC_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
// #include <stdint.h>

void lcd_int_AVR(int val, uint8_t width, enum LCD_alignment_e alignment);
void lcd_hex_AVR(int val, uint8_t width, enum LCD_alignment_e alignment);
void lcd_bin_AVR(int val, uint8_t width);

void lcd_buf_int_AVR(int val, uint8_t width, enum LCD_alignment_e alignment);
void lcd_buf_hex_AVR(int val, uint8_t width, enum LCD_alignment_e alignment);
void lcd_buf_bin_AVR(int val, uint8_t width);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD_44780_AVR_SPECIFIC_H_*/
