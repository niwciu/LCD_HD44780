/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-08 11:15:52 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 12:28:49
 */

#ifndef _LCD_HD44780_DEF_CHAR_H_
#define _LCD_HD44780_DEF_CHAR_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
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
    static const struct char_bank_struct lcd_cgram_bank_1 = {
        Pol_e,
        Pol_o,
        Pol_s,
        Pol_l,
        Pol_c,
        Pol_a,
        Pol_n,
        Zn_wody};
    enum LCD_CGRAM_BANK_1
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

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*_LCD_HD44780_DEF_CHAR_H_*/