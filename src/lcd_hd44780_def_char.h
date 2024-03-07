/**
 * @file lcd_hd44780_def_char.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.2
 * @date 2024-02-25
 * @addtogroup LCD_HD44780_lib_API
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _LCD_HD44780_DEF_CHAR_H_
#define _LCD_HD44780_DEF_CHAR_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
       /**
        * @struct char_bank_struct
        * @brief Structure that contain pointers to 8 user predefined characters. Structure is used to define user character banks.
        * Each bank can contain combinatio of maksimum 8 user special cahracters.
        *
        */
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

#if USE_DEF_CHAR_FUNCTION == ON
#define LCD_CGRAM_BYTES_PER_CHAR 8
#define DEF_CHAR_ADR_MASK 7
    /**********************USER CHAR DECLARATION SECTION*******************************/
    /**
     * @note To save flash when using defchar comment char definitions that are unused
     * */
    static const uint8_t Pol_e[8] = {32, 32, 14, 17, 31, 16, 14, 3};
    static const uint8_t Pol_o[8] = {2, 4, 14, 17, 17, 17, 14, 0};
    static const uint8_t Pol_s[8] = {2, 4, 14, 16, 14, 1, 30, 32};
    static const uint8_t Pol_l[8] = {12, 4, 6, 12, 4, 4, 14, 32};
    static const uint8_t Pol_c[8] = {2, 4, 14, 16, 16, 17, 14, 32};
    static const uint8_t Pol_a[8] = {32, 32, 14, 1, 15, 17, 15, 3};
    static const uint8_t Pol_n[8] = {2, 4, 22, 25, 17, 17, 17, 0};
    static const uint8_t Zn_wody[8] = {0, 0, 0, 6, 9, 2, 4, 15};
    // here add "definition" of new chars

    /**********************USER CHAR CGRAM BANKS DECALRATION SECTION*******************/
    static const struct char_bank_struct lcd_cgram_bank_1 = {
        Pol_e,
        Pol_o,
        Pol_s,
        Pol_l,
        Pol_c,
        Pol_a,
        Pol_n,
        Zn_wody};

    /**
     * @enum LCD_CGRAM_BANK_1_e
     * @brief Labels representing specific user defined chars collected in lcd_cgram_bank_1.
     * Labels value are equal to adress in lcd_cgram_bank_1 and addres of LCD_CGRAM where all chars from lcd_cgram_bank_1 will be written when using
     * lcd_load_char_bank() or lcd_def_char() when defining single char in LCD_CGRAM
     */
    enum LCD_CGRAM_BANK_1_e
    {
        pol_e,   /**< @brief label with vlaue 0 created for custom Char Piol_e placed under adress 0x00 in lcd_cgram_bank_1 and LCD_CGRAM*/
        pol_o,   /**< @brief label with vlaue 1 created for custom Char Piol_o placed under adress 0x01 in lcd_cgram_bank_1 and LCD_CGRAM*/
        pol_s,   /**< @brief label with vlaue 2 created for custom Char Piol_s placed under adress 0x02 in lcd_cgram_bank_1 and LCD_CGRAM*/
        pol_l,   /**< @brief label with vlaue 3 created for custom Char Piol_l placed under adress 0x03 in lcd_cgram_bank_1 and LCD_CGRAM*/
        pol_c,   /**< @brief label with vlaue 4 created for custom Char Piol_c placed under adress 0x03 in lcd_cgram_bank_1 and LCD_CGRAM*/
        pol_a,   /**< @brief label with vlaue 5 created for custom Char Piol_a placed under adress 0x03 in lcd_cgram_bank_1 and LCD_CGRAM*/
        pol_n,   /**< @brief label with vlaue 6 created for custom Char Piol_n placed under adress 0x03 in lcd_cgram_bank_1 and LCD_CGRAM*/
        zn_wody, /**< @brief label with vlaue 7 created for custom Char Zn_wody placed under adress 0x03 in lcd_cgram_bank_1 and LCD_CGRAM*/
    };
    // //here define new bank with adreses for chars that you want load to this specifci bank
    // static const struct char_bank_struct lcd_cgram_bank_x = {
    //     Pol_e,
    //     Pol_o,
    //     Pol_s,
    //     Pol_l,
    //     Pol_c,
    //     Pol_a,
    //     Pol_n,
    //     Zn_wody};
    // // here define labels for lcd_cgram_bank_x
    // enum LCD_CGRAM_BANK_x_e
    // {
    //     pol_e_bank_x,
    //     pol_o_bank_x,
    //     pol_s_bank_x,
    //     pol_l_bank_x,
    //     pol_c_bank_x,
    //     pol_a_bank_x,
    //     pol_n_bank_x,
    //     zn_wody_bank_x,
    // };
    /**********************USER CHAR CGRAM BANKS DEFINITIONS END*********************/

#endif // USE_DEF_CHAR_FUNC
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*_LCD_HD44780_DEF_CHAR_H_*/