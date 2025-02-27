/**
 * @file lcd_hd44780_def_char.h
 * @author LCD custom char code generator app written by niwciu (niwciu@gmail.com)
 * @brief Header file for defining custom characters for the HD44780 LCD.
 * @version <add version no>
 * @date 2025-02-26
 * @addtogroup LCD_HD44780_lib_API
 * @copyright Copyright (c) 2025
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
#define CHAR_MAP_END '\0'

    /**
     * @brief Structure for mapping ASCII characters to LCD memory equivalents.
     *
     * This structure defines a mapping between an ASCII character and its corresponding
     * representation in the LCD memory, which could be an address or an enum value.
     */
    typedef struct
    {
        char ascii_char;           /**< The ASCII character to be mapped. */
        uint8_t lcd_def_char_addr; /**< The corresponding representation in LCD memory (e.g., address or enum). */
    } lcd_char_mapping_struct_t;

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

    /**
     * @struct lcd_def_char_load_struct_t
     * @brief Structure for loading custom character banks and their corresponding mapping tables.
     *
     * This structure is used to define a custom character bank along with its associated
     * character mapping table. It contains a pointer to the character bank and a pointer
     * to the mapping table that maps ASCII characters to their LCD memory equivalents.
     */
    typedef struct
    {
        char_bank_struct_t *char_bank;               /**< The pointer to the character bank to load. */
        lcd_char_mapping_struct_t *char_mapping_tab; /**< The pointer to the corresponding character mapping table. */
    } lcd_bank_load_struct_t;

    /**********************USER CHAR DECLARATION SECTION*******************************/
    /**
     * @note To save flash when using defchar, comment out char definitions that are not used
     */
    static const uint8_t Pol_e[8] = {0, 0, 14, 17, 31, 16, 14, 3};
    static const uint8_t Pol_o[8] = {2, 4, 14, 17, 17, 17, 14, 0};
    static const uint8_t Pol_s[8] = {2, 4, 14, 16, 14, 1, 30, 0};
    static const uint8_t Pol_l[8] = {12, 4, 6, 12, 4, 4, 14, 0};
    static const uint8_t Pol_c[8] = {2, 4, 14, 16, 16, 17, 14, 0};
    static const uint8_t Pol_a[8] = {0, 0, 14, 1, 15, 17, 15, 3};
    static const uint8_t Pol_n[8] = {2, 4, 22, 25, 17, 17, 17, 0};
    static const uint8_t Zn_wody[8] = {0, 0, 0, 6, 9, 2, 4, 15};
    // Add additional custom characters definitions here

    /**********************USER CHAR CGRAM 'bank_1' DECLARATION SECTION*******************/
    /**
     * @struct bank_1
     * @brief Structure that contains pointers to 8 user predefined characters. Structure is used to define user character banks.
     * Each bank can contain a combination of a maximum of 8 user special characters.
     */
    static char_bank_struct_t bank_1 = {
        Pol_e,   /**< @brief Label with value 0 for custom character 'Pol_e' at address 0x00 in bank_1 and LCD_CGRAM. */
        Pol_o,   /**< @brief Label with value 1 for custom character 'Pol_o' at address 0x01 in bank_1 and LCD_CGRAM. */
        Pol_s,   /**< @brief Label with value 2 for custom character 'Pol_s' at address 0x02 in bank_1 and LCD_CGRAM. */
        Pol_l,   /**< @brief Label with value 3 for custom character 'Pol_l' at address 0x03 in bank_1 and LCD_CGRAM. */
        Pol_c,   /**< @brief Label with value 4 for custom character 'Pol_c' at address 0x04 in bank_1 and LCD_CGRAM. */
        Pol_a,   /**< @brief Label with value 5 for custom character 'Pol_a' at address 0x05 in bank_1 and LCD_CGRAM. */
        Pol_n,   /**< @brief Label with value 6 for custom character 'Pol_n' at address 0x06 in bank_1 and LCD_CGRAM. */
        Zn_wody, /**< @brief Label with value 7 for custom character 'Zn_wody' at address 0x07 in bank_1 and LCD_CGRAM. */
    };

    /**
     * @enum LCD_CGRAM_BANK_1_e
     * @brief Labels representing specific user defined chars collected in LCD_CGRAM_BANK_1_e.
     * Label values are equal to addresses in LCD_CGRAM_BANK_1_e and the address of LCD_CGRAM where all chars from LCD_CGRAM_BANK_1_e will be written
     * when using lcd_load_char_bank() or lcd_def_char() for defining single characters in LCD_CGRAM.
     */
    enum LCD_CGRAM_BANK_1_e
    {
        bank_1_Pol_e,   /**< @brief Label with value 0 for custom character 'Pol_e' at address 0x00 in bank_1 and LCD_CGRAM. */
        bank_1_Pol_o,   /**< @brief Label with value 1 for custom character 'Pol_o' at address 0x01 in bank_1 and LCD_CGRAM. */
        bank_1_Pol_s,   /**< @brief Label with value 2 for custom character 'Pol_s' at address 0x02 in bank_1 and LCD_CGRAM. */
        bank_1_Pol_l,   /**< @brief Label with value 3 for custom character 'Pol_l' at address 0x03 in bank_1 and LCD_CGRAM. */
        bank_1_Pol_c,   /**< @brief Label with value 4 for custom character 'Pol_c' at address 0x04 in bank_1 and LCD_CGRAM. */
        bank_1_Pol_a,   /**< @brief Label with value 5 for custom character 'Pol_a' at address 0x05 in bank_1 and LCD_CGRAM. */
        bank_1_Pol_n,   /**< @brief Label with value 6 for custom character 'Pol_n' at address 0x06 in bank_1 and LCD_CGRAM. */
        bank_1_Zn_wody, /**< @brief Label with value 7 for custom character 'Zn_wody' at address 0x07 in bank_1 and LCD_CGRAM. */
    };

    /**
     * @brief Mapping of extended ASCII characters to their corresponding custom character addresses for bank_1.
     *
     * This array maps selected extended ASCII characters (which typically occupy 1 byte in modern encodings like UTF-8)
     * to custom character addresses defined in `lcd_cgram_bank_1`.
     * This allows the use of custom characters based on their extended ASCII representation.
     *
     * @warning This file and all files containing strings with Polish characters
     *          (e.g., '?', 'ó', etc.) **must** be saved using the Windows-1250 encoding.
     *          Failure to do so will result in incorrect character translation on the LCD.
     *
     * @warning A null terminator **must** be placed at the end of the mapping table.
     *          Without this, the mapping algorithm will cause a critical fault.
     */
    static lcd_char_mapping_struct_t lcd_bank_1_def_chars_map[] = {
        // HERE YOU CAN DEFINE MAPPING OF YOUR DEF CHAR TO ANY U8 ASCII CHAR
        // Defined ASCII U8 Char will be displayed on LCD as mapped def char
        // You can mapp more ASCI char to one def char. Look on example bellow
        // {'³', bank_1_Pol_l}, /**< Extended ASCII '³' mapped to the custom character '³' (address = enum bank_1_Pol_l) */
        // {'£', bank_1_Pol_l}, /**< Extended ASCII '£' mapped to the custom character '³' (address = enum bank_1_Pol_l) */

        {'ê', bank_1_Pol_e}, /**< Extended ASCII 'ê' mapped to the custom character 'ê' (address 0x00) */
        {'ó', bank_1_Pol_o}, /**< Extended ASCII 'ó' mapped to the custom character 'ó' (address 0x01) */
        {'œ', bank_1_Pol_s}, /**< Extended ASCII 'œ' mapped to the custom character 'œ' (address 0x02) */
        {'Œ', bank_1_Pol_s}, /**< Extended ASCII 'Œ' mapped to the custom character 'œ' (address 0x02) */
        {'³', bank_1_Pol_l}, /**< Extended ASCII '³' mapped to the custom character '³' (address 0x03) */
        {'£', bank_1_Pol_l}, /**< Extended ASCII '£' mapped to the custom character '³' (address 0x03) */
        {'æ', bank_1_Pol_c}, /**< Extended ASCII 'æ' mapped to the custom character 'æ' (address 0x04) */
        {'Æ', bank_1_Pol_c}, /**< Extended ASCII 'Æ' mapped to the custom character 'æ' (address 0x04) */
        {'¹', bank_1_Pol_a}, /**< Extended ASCII '¹' mapped to the custom character '¹' (address 0x05) */
        {'ñ', bank_1_Pol_n}, /**< Extended ASCII 'ñ' mapped to the custom character 'ñ' (address 0x06) */
        {CHAR_MAP_END, 0}    /**< MANDATORY!!! - Null terminator to mark the end of the mapping table */
    };

    /**
     * @brief Structure for loading a custom character bank and its associated character mapping table.
     *
     * This structure is used to define a custom character bank and its corresponding
     * character mapping table. It is used to load custom characters into the LCD's
     * CGRAM and map them to specific extended ASCII characters.
     *
     * @see bank_1
     * @see lcd_bank_1_def_chars_map
     */
    static const lcd_bank_load_struct_t bank_1_load_data = {
        &bank_1,                  /**< Pointer to the custom character bank containing user-defined characters. */
        lcd_bank_1_def_chars_map, /**< Pointer to the mapping table that associates extended ASCII characters with custom character addresses. */
    };

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LCD_HD44780_DEF_CHAR_H_ */
