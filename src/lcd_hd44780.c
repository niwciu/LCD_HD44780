/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-06 21:39:30
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:01:47
 */

#include "lcd_hd44780.h"
#include <stddef.h>

#define BUSY_FLAG 1 << 7

// LCD driver commands
// clang-format off
#define LCDC_CLS            0x01
#define LCDC_HOME           0x02
/********************************/
#define LCDC_ENTRY_MODE     0x04
    #define LCDC_ENTRYR     0x02
    #define LCDC_ENTRYL     0x00
    #define LCDC_MOVE       0x01
/********************************/
#define LCDC_ONOFF          0x08
    #define LCDC_DISPLAYON  0x04
    #define LCDC_CURSORON   0x02
    #define LCDC_CURSOROFF  0x00
    #define LCDC_BLINKON    0x01
/********************************/
#define LCDC_SHIFT          0x10
    #define LCDC_SHIFTDISP  0x08
    #define LCDC_SHIFTR     0x04
    #define LCDC_SHIFTL     0x00
/********************************/
#define LCDC_FUNC           0x20
    #define LCDC_FUNC8B     0x10
    #define LCDC_FUNC4B     0x00
    #define LCDC_FUNC2L     0x08
    #define LCDC_FUNC1L     0x00
    #define LCDC_FUNC5x10   0x04
    #define LCDC_FUNC5x7    0x00
/********************************/
#define LCDC_SET_CGRAM      0x40
#define LCDC_SET_DDRAM      0x80
// clang-format on




static const struct LCD_IO_driver_interface_struct *LCD = NULL;
// const struct char_bank_struct *char_bank = &char_bank_1;

static void register_LCD_IO_driver(void);
static void lcd_set_all_SIG(void);
static void lcd_reset_all_SIG(void);
static void lcd_write_4bit_data(uint8_t data);
static void lcd_write_cmd(uint8_t cmd);
static void lcd_write_data(uint8_t data);
static void lcd_write_byte(uint8_t byte);
#if USE_RW_PIN == ON
static uint8_t lcd_read_byte(void);
static uint8_t lcd_read_4bit_data(void);
#endif

static void register_LCD_IO_driver(void)
{
    LCD = LCD_IO_driver_interface_get();
}

static void lcd_set_all_SIG(void)
{
    LCD->set_SIG(LCD_E);
    LCD->set_SIG(LCD_RS);
#if USE_RW_PIN == ON
    LCD->set_SIG(LCD_RW);
#endif
}

static void lcd_reset_all_SIG(void)
{
#if USE_RW_PIN == ON
    LCD->reset_SIG(LCD_RW);
#endif
    LCD->reset_SIG(LCD_RS);
    LCD->reset_SIG(LCD_E);
}

void lcd_write_4bit_data(uint8_t data)
{
    LCD->set_SIG(LCD_E);
    data &= 0x0F;
    LCD->write_data(data);
    LCD->reset_SIG(LCD_E);
}

static void lcd_write_cmd(uint8_t cmd)
{
    LCD->reset_SIG(LCD_RS);
    lcd_write_byte(cmd);
}

void lcd_write_data(uint8_t data)
{
    LCD->set_SIG(LCD_RS);
    lcd_write_byte(data);
}

void lcd_write_byte(uint8_t byte)
{
    #if USE_RW_PIN == ON
    LCD->reset_SIG(LCD_RW);
#endif
    lcd_write_4bit_data((byte) >> 4);
    lcd_write_4bit_data((byte)&0x0F);
#if USE_RW_PIN == ON
    //check_BUSSY_FALG
    LCD->set_data_pins_as_inputs();
    LCD->reset_SIG(LCD_RS);
    LCD->set_SIG(LCD_RW);
    while (lcd_read_byte() & BUSY_FLAG)
    {
    }
    LCD->reset_SIG(LCD_RW);
    LCD->set_data_pins_as_outputs();

#else
    LCD->delay_us(120);
#endif
}

#if USE_RW_PIN == ON
uint8_t lcd_read_byte(void)
{
    uint8_t data;
    //read 4 MSB
    data = (lcd_read_4bit_data() << 4);
    //read 4 LSB
    data |= (lcd_read_4bit_data() & 0x0F);
    return data;
}

uint8_t lcd_read_4bit_data(void)
{
    uint8_t data;
    LCD->set_SIG(LCD_E);
    data = LCD->read_data();
    LCD->reset_SIG(LCD_E);
    return data;
}
#endif

/**
 * @brief  Function that initialize LCD in 4-bit mode with or without LCD R/W Pin handling.
 * @attention LCD R/W handling should be configured in lcd_hd44780_config.h by setting USE_RW_PIN to  1 (Enable R/W Pin
 * handling) or 0 (disable R/W Pin handling).
 */
void lcd_init(void)
{
    register_LCD_IO_driver();
    LCD->init_LCD_pins();
    /**************************BASIC LCD INIT - basing on DS init procedure***************************************/
    // set all LCD signals to High for more than 15ms ->bit different then in DS base on other implementation from internet
    lcd_set_all_SIG();
    LCD->delay_us(15000);
    lcd_reset_all_SIG();
    // send 0x03 & wait more then 4,1ms
    lcd_write_4bit_data(0x03);
    LCD->delay_us(4500);
    // send 0x03 & wait more then 100us
    lcd_write_4bit_data(0x03);
    LCD->delay_us(110);
    // send 0x03 & wait more then 100us
    lcd_write_4bit_data(0x03);
    LCD->delay_us(110);
    // send 0x02 & wait more then 100us
    lcd_write_4bit_data(0x02);
    LCD->delay_us(110);
    // FUNCTION SET ->send cmd -> LCD in 4-bit mode, 2 rows, char size 5x7
    lcd_write_cmd(LCDC_FUNC | LCDC_FUNC4B | LCDC_FUNC2L | LCDC_FUNC5x7);
    // DISPLAY_ON_OFF send cmd -> enable lcd
    lcd_write_cmd(LCDC_ONOFF | LCDC_CURSOROFF | LCDC_DISPLAYON);
    // LCD clear screen
    lcd_cls();
    // ENTRY MODe SET do not shift LCD shift cursor right after placing a char
    lcd_write_cmd(LCDC_ENTRY_MODE | LCDC_ENTRYR);
    /*********************************END of BASIC LCD INIT***************************************/

    // ToDo define sepcial characters in LCD CGRAM
    
}

/**
 * @brief Function that clear the LCD screen and set the cursor on the position of first character in first line of LCD
 * screen.
 */
void lcd_cls(void)
{
    lcd_write_cmd (LCDC_CLS);
    LCD->delay_us(4900);
}

/**
 * @brief Function for defining custom user characters in CGRAM of the LCD.
 * @param CGRAM_char_index Position/addres of the character in CGRAM of the LCD where defined char should be written.
 * For the predefined example of special characters, taken values are defined in the type enum LCD_CGRAM that is defined
 * in lcd-hd44780.h
 * @param def_char Pointer to the predefined special character.
 * @note CGRAM_char_index - This Parameter can take values from 0 to 7. For the predefined example of special
 * characters, taken values are defined in the type enum LCD_CGRAM that is defined in lcd-hd44780.h
 */
void lcd_def_char(enum LCD_CGRAM CGRAM_char_index, const uint8_t *def_char)
{
    lcd_write_cmd(LCDC_SET_CGRAM | ((DEF_CHAR_ADR_MASK & CGRAM_char_index) * LCD_CGRAM_BYTES_PER_CHAR));
    for (uint8_t j = 0; j < LCD_CGRAM_BYTES_PER_CHAR; j++)
    {
        lcd_write_data(def_char[j]);
    }
    lcd_write_cmd(LCDC_SET_DDRAM);
}

void lcd_load_char_bank(const struct char_bank_struct *char_bank)
{
    lcd_def_char(0,char_bank->char_0);
    lcd_def_char(1,char_bank->char_1);
    lcd_def_char(2,char_bank->char_2);
    lcd_def_char(3,char_bank->char_3);
    lcd_def_char(4,char_bank->char_4);
    lcd_def_char(5,char_bank->char_5);
    lcd_def_char(6,char_bank->char_6);
    lcd_def_char(7,char_bank->char_7);
}

/**
 * @brief Function for print the char on the LCD screen under current position of the LCD cursor.
 * @param C char (for example '1') or it's ASCI code (0x31).
 * @note For user defined char, place CGRAM_char_index (Position/addres of the character in CGRAM of the LCD where
 * defined char was written).
 */
void lcd_char(char C)
{
    uint8_t data = (uint8_t)(C);
    lcd_write_data(data);
}
