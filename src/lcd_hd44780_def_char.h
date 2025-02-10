/**
 * @file lcd_hd44780_def_char.h
 * @author niwciu (niwciu@gmail.com)
 * @brief Header file for defining custom characters for the HD44780 LCD.
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
#include <stdint.h>
#include "lcd_hd44780_config.h"

#define LCD_CGRAM_BYTES_PER_CHAR 8
#define DEF_CHAR_ADR_MASK 7

    /**
     * @brief Structure for mapping ASCII characters to LCD memory equivalents.
     *
     * This structure defines a mapping between an ASCII character and its corresponding
     * representation in the LCD memory, which could be an address or an enum value.
     */
    typedef struct
    {
        char ascii_char;   /**< The ASCII character to be mapped. */
        char lcd_def_char; /**< The corresponding representation in LCD memory (e.g., address or enum). */
    } LCD_char_mapping_struct_t;

    /**
     * @struct char_bank_struct
     * @brief Structure that contains pointers to 8 user predefined characters. Structure is used to define user character banks.
     * Each bank can contain a combination of a maximum of 8 user special characters.
     */
    typedef struct
    {
        const uint8_t *char_0; /**< Pointer to the first custom character. */
        const uint8_t *char_1; /**< Pointer to the second custom character. */
        const uint8_t *char_2; /**< Pointer to the third custom character. */
        const uint8_t *char_3; /**< Pointer to the fourth custom character. */
        const uint8_t *char_4; /**< Pointer to the fifth custom character. */
        const uint8_t *char_5; /**< Pointer to the sixth custom character. */
        const uint8_t *char_6; /**< Pointer to the seventh custom character. */
        const uint8_t *char_7; /**< Pointer to the eighth custom character. */
    } char_bank_struct_t;

    /**********************USER CHAR DECLARATION SECTION*******************************/
    /**
     * @note To save flash when using defchar comment char definitions that are unused
     */
    static const uint8_t Pol_e[8] = {32, 32, 14, 17, 31, 16, 14, 3};
    static const uint8_t Pol_o[8] = {2, 4, 14, 17, 17, 17, 14, 0};
    static const uint8_t Pol_s[8] = {2, 4, 14, 16, 14, 1, 30, 32};
    static const uint8_t Pol_l[8] = {12, 4, 6, 12, 4, 4, 14, 32};
    static const uint8_t Pol_c[8] = {2, 4, 14, 16, 16, 17, 14, 32};
    static const uint8_t Pol_a[8] = {32, 32, 14, 1, 15, 17, 15, 3};
    static const uint8_t Pol_n[8] = {2, 4, 22, 25, 17, 17, 17, 0};
    static const uint8_t Zn_wody[8] = {0, 0, 0, 6, 9, 2, 4, 15};
    // Add additional custom characters definitions here

    /**********************USER CHAR CGRAM BANKS DECLARATION SECTION*******************/
    /**
     * @struct char_bank_struct_t
     * @brief Structure that contains pointers to 8 user predefined characters. Structure is used to define user character banks.
     * Each bank can contain a combination of a maximum of 8 user special characters.
     */
    static const char_bank_struct_t lcd_cgram_bank_1 = {
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
     * Label values are equal to addresses in lcd_cgram_bank_1 and the address of LCD_CGRAM where all chars from lcd_cgram_bank_1 will be written
     * when using lcd_load_char_bank() or lcd_def_char() for defining single characters in LCD_CGRAM.
     */
    enum LCD_CGRAM_BANK_1_e
    {
        pol_e,   /**< @brief Label with value 0 for custom character 'Pol_e' at address 0x00 in lcd_cgram_bank_1 and LCD_CGRAM. */
        pol_o,   /**< @brief Label with value 1 for custom character 'Pol_o' at address 0x01 in lcd_cgram_bank_1 and LCD_CGRAM. */
        pol_s,   /**< @brief Label with value 2 for custom character 'Pol_s' at address 0x02 in lcd_cgram_bank_1 and LCD_CGRAM. */
        pol_l,   /**< @brief Label with value 3 for custom character 'Pol_l' at address 0x03 in lcd_cgram_bank_1 and LCD_CGRAM. */
        pol_c,   /**< @brief Label with value 4 for custom character 'Pol_c' at address 0x04 in lcd_cgram_bank_1 and LCD_CGRAM. */
        pol_a,   /**< @brief Label with value 5 for custom character 'Pol_a' at address 0x05 in lcd_cgram_bank_1 and LCD_CGRAM. */
        pol_n,   /**< @brief Label with value 6 for custom character 'Pol_n' at address 0x06 in lcd_cgram_bank_1 and LCD_CGRAM. */
        zn_wody, /**< @brief Label with value 7 for custom character 'Zn_wody' at address 0x07 in lcd_cgram_bank_1 and LCD_CGRAM. */
    };

    /**
     * @brief Mapping between extended ASCII characters and their corresponding custom character addresses.
     *
     * This array maps specific extended ASCII characters (which are typically 1 byte in modern encodings like UTF-8)
     * to the custom character addresses defined in the `lcd_cgram_bank_1`.
     * This allows the usage of custom characters based on their extended ASCII representation.
     *
     * @warning It is required that this file and all files containing strings with Polish characters
     *          (e.g., 'ê', 'ó', 'œ', etc.) be saved with Windows-1250 encoding to ensure proper
     *          translation of Polish characters to the corresponding LCD-defined characters.
     */
    static const LCD_char_mapping_struct_t lcd_bank_1_special_chars_map[] = {
        {'ê', pol_o}, /**< Extended ASCII 'ê' mapped to the custom character 'ó' (address 0x01) */
        {'ó', pol_a}, /**< Extended ASCII 'ó' mapped to the custom character '¹' (address 0x05) */
        {'œ', pol_s}, /**< Extended ASCII 'œ' mapped to the custom character 'œ' (address 0x02) */
        {'³', pol_l}, /**< Extended ASCII '³' mapped to the custom character '³' (address 0x03) */
        {'æ', pol_c}, /**< Extended ASCII 'æ' mapped to the custom character 'æ' (address 0x04) */
        {'¹', pol_a}, /**< Extended ASCII '¹' mapped to the custom character '¹' (address 0x05) */
        {'ñ', pol_n}, /**< Extended ASCII 'ñ' mapped to the custom character 'ñ' (address 0x06) */
        {'\0', 0}     /**< Null terminator to mark the end of the mapping table */
    };

    /**********************USER CHAR CGRAM BANKS DEFINITIONS END*********************/

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*_LCD_HD44780_DEF_CHAR_H_*/
