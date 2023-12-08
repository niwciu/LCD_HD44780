

#ifndef _LCD_HD_44780_H_
#define _LCD_HD_44780_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#include "lcd_hd44780_config.h"
#include "lcd_hd44780_interface.h"

#define LCD_CGRAM_BYTES_PER_CHAR 8
#define DEF_CHAR_ADR_MASK 7
    static const uint8_t Pol_e[8] = {32, 32, 14, 17, 31, 16, 14, 3};
    static const uint8_t Pol_o[8] = {2, 4, 14, 17, 17, 17, 14, 0};
    static const uint8_t Pol_s[8] = {2, 4, 14, 16, 14, 1, 30, 32};
    static const uint8_t Pol_l[8] = {12, 4, 6, 12, 4, 4, 14, 32};
    static const uint8_t Pol_c[8] = {2, 4, 14, 16, 16, 17, 14, 32};
    static const uint8_t Pol_a[8] = {32, 32, 14, 1, 15, 17, 15, 3};
    static const uint8_t Pol_n[8] = {2, 4, 22, 25, 17, 17, 17, 0};
    static const uint8_t Zn_wody[8] = {0, 0, 0, 6, 9, 2, 4, 15};

enum LCD_CGRAM
{
    pol_e,
    pol_o,
    pol_s,
    pol_l,
    pol_c,
    pol_a,
    pol_n,
    zn_wody,
};

struct char_bank_struct
{
    const uint8_t *char_0;
    const uint8_t *char_1;
    const uint8_t *char_2;
    const uint8_t *char_3;
    const uint8_t *char_4;
    const uint8_t *char_5;
    const uint8_t *char_6;
    const uint8_t *char_7;
};
static const struct char_bank_struct char_bank_1 = {
    Pol_e,
    Pol_o,
    Pol_s,
    Pol_l,
    Pol_c,
    Pol_a,
    Pol_n,
    Zn_wody
};


void lcd_init(void);
void lcd_cls(void);

void lcd_def_char(enum LCD_CGRAM CGRAM_char_index, const uint8_t *def_char);
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