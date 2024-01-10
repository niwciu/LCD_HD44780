/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-06 21:39:30
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-10 14:00:21
 */

#include "lcd_hd44780.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char lcd_pos_t;
// clang-format off
#define BUSY_FLAG           1 << 7
#define VAL_PREFIX_LENGHT   2U

// LCD driver commands
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

#ifndef UNIT_TEST
#define PRIVATE static
#else
#define PRIVATE
#endif

#if LCD_BUFFERING == ON

#define LAST_CHAR_IN_LCD_LINE   (LCD_X-1)
#define LAST_LCD_LINE   (LCD_Y-1)

PRIVATE char lcd_buffer[LCD_Y][LCD_X];

// static uint8_t lcd_buf_X=0;
// static uint8_t lcd_buf_Y=0;
static lcd_pos_t *lcd_buf_position_ptr;
#endif

static const struct LCD_IO_driver_interface_struct *LCD = NULL;
bool LCD_UPDATE_EVENT = false;

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
#ifdef AVR
static void lcd_put_spaces(uint8_t empty_spaces);
static void lcd_int_AVR(int val, uint8_t width, enum alignment alignment);
static void lcd_hex_AVR(int val, uint8_t width, enum alignment alignment);
static void lcd_bin_AVR(int val, uint8_t width);
#else
static void fill_bin_value_buffer(int val, char *bin_val_buffer);
static void fill_zeros_buffer(const char *buffer, uint8_t width, char *zeros_buf);
#endif
#if LCD_BUFFERING==ON
static void check_lcd_buf_possition_ptr_overflow(void);
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
    lcd_write_4bit_data((byte) & 0x0F);
#if USE_RW_PIN == ON
    // check_BUSSY_FALG
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
    // read 4 MSB
    data = (lcd_read_4bit_data() << 4);
    // read 4 LSB
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
#ifdef AVR
static void lcd_put_spaces(uint8_t empty_spaces)
{
    for (uint8_t i = 0; i < empty_spaces; i++)
    {
        lcd_char(' ');
    }
}

void lcd_int_AVR(int val, uint8_t width, enum alignment alignment)
{
    uint8_t buf_lenght = 0;
    char buffer[20]; // 19chars for 64 bit int + end char '\0'
    buffer[0] = '\0';
    itoa(val, buffer, 10);
    buf_lenght = strlen(buffer);
    if (buf_lenght >= (width))
    {
        lcd_str(buffer);
    }
    else
    {
        uint8_t empty_spaces_qty = width - buf_lenght;
        if (alignment == right)
        {
            lcd_put_spaces(empty_spaces_qty);
            lcd_str(buffer);
        }
        else
        {
            lcd_str(buffer);
            lcd_put_spaces(empty_spaces_qty);
        }
    }
}

void lcd_hex_AVR(int val, uint8_t width, enum alignment alignment)
{
    char buffer[17];
    buffer[0] = '\0';
    itoa(val, buffer, 16);
    static const char *prefix = {"0x"};
    if (width <= (strlen(buffer) + VAL_PREFIX_LENGHT))
    {
        lcd_str(prefix);
        lcd_str(buffer);
    }
    else
    {
        uint8_t empty_spaces_qty = width - (VAL_PREFIX_LENGHT + strlen(buffer));

        if (alignment == right)
        {
            lcd_put_spaces(empty_spaces_qty);
            lcd_str(prefix);
            lcd_str(buffer);
        }
        else
        {
            lcd_str(prefix);
            lcd_str(buffer);
            lcd_put_spaces(empty_spaces_qty);
        }
    }
}

void lcd_bin_AVR(int val, uint8_t width)
{
    char buffer[35]; // 0b 0000 0000 0000 0000 0000 0000 0000 0000
    static const char *prefix = {"0b"};
    buffer[0] = '\0';

    itoa(val, buffer, 2);
    // if (buf_lenght < (width - VAL_PREFIX_LENGHT))
    if (width <= (strlen(buffer) + VAL_PREFIX_LENGHT))
    {
        lcd_str(prefix);
        lcd_str(buffer);
    }
    else
    {
        uint8_t zeros_qty = (width - (VAL_PREFIX_LENGHT + strlen(buffer)));
        lcd_str(prefix);
        for (uint8_t i = 0; i < zeros_qty; i++)
        {
            lcd_char('0');
        }
        lcd_str(buffer);
    }
}
#else

static void fill_bin_value_buffer(int val, char *bin_val_buffer)
{
    uint32_t bit_mask = 0x80000000;
    while (bit_mask != 0)
    {
        if ((bit_mask & val) != 0)
        {
            strcat(bin_val_buffer, "1");
        }
        else
        {
            if (strlen(bin_val_buffer) != 0)
            {
                strcat(bin_val_buffer, "0");
            }
        }
        bit_mask = bit_mask >> 1;
    }
}

static void fill_zeros_buffer(const char *buffer, uint8_t width, char *zeros_buf)
{
    if (strlen(buffer) < (width + VAL_PREFIX_LENGHT))
    {
        uint8_t zeros_qty = width - ((strlen(buffer) + VAL_PREFIX_LENGHT));
        for (uint8_t t = 0; t < zeros_qty; t++)
        {
            strcat(zeros_buf, "0");
        }
    }
}
#endif

#if LCD_BUFFERING==ON
static void check_lcd_buf_possition_ptr_overflow(void)
{
    if(++lcd_buf_position_ptr>&lcd_buffer[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE])
    {
        lcd_buf_position_ptr=&lcd_buffer[LINE_1][C1];
    }
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

    // ToDo define sepcial characters in LCD CGRAM if needed

    // init LCD buffer if LCD_BUFFERING is ON in lcdhd44780_config.h
#if LCD_BUFFERING == ON
    lcd_buf_cls();
#endif
  
}

/**
 * @brief Function that clear the LCD screen and set the cursor on the position of first character in first line of LCD
 * screen.
 */
void lcd_cls(void)
{
    lcd_write_cmd(LCDC_CLS);
#if USE_RW_PIN == OFF
    LCD->delay_us(4900);
#endif
}

#if USE_DEF_CHAR_FUNCTION == ON
/**
 * @brief Function for defining custom user characters in CGRAM of the LCD.
 * @param CGRAM_char_index Position/addres of the character in CGRAM of the LCD where defined char should be written.
 * For the predefined example of special characters, taken values are defined in the type enum LCD_CGRAM that is defined
 * in lcd-hd44780.h
 * @param def_char Pointer to the predefined special character.
 * @note CGRAM_char_index - This Parameter can take values from 0 to 7. For the predefined example of special
 * characters, taken values are defined in the type enum LCD_CGRAM that is defined in lcd-hd44780.h
 */
void lcd_def_char(const uint8_t CGRAM_bank_x_char_adr, const uint8_t *def_char)
{
    lcd_write_cmd(LCDC_SET_CGRAM | ((DEF_CHAR_ADR_MASK & CGRAM_bank_x_char_adr) * LCD_CGRAM_BYTES_PER_CHAR));
    for (uint8_t j = 0; j < LCD_CGRAM_BYTES_PER_CHAR; j++)
    {
        lcd_write_data(def_char[j]);
    }
    lcd_write_cmd(LCDC_SET_DDRAM);
}

void lcd_load_char_bank(const struct char_bank_struct *char_bank)
{
    lcd_def_char(0, char_bank->char_0);
    lcd_def_char(1, char_bank->char_1);
    lcd_def_char(2, char_bank->char_2);
    lcd_def_char(3, char_bank->char_3);
    lcd_def_char(4, char_bank->char_4);
    lcd_def_char(5, char_bank->char_5);
    lcd_def_char(6, char_bank->char_6);
    lcd_def_char(7, char_bank->char_7);
}
#endif

/**
 * @brief Function for print the char on the LCD screen under current position of the LCD cursor.
 * @param C char (for example '1') or it's ASCI code (0x31).
 * @note For user defined char, place CGRAM_char_index (Position/addres of the character in CGRAM of the LCD where
 * defined char was written).
 */
void lcd_char(const char C)
{
    uint8_t data = (uint8_t)(C);
    lcd_write_data(data);
}

/**
 * @brief Function for printing/writing string on LCD screen. Writing the string on LCD screen start from current LCD
 * cursor position.
 * @param str string that should be printed/written on the LCD screen
 */
void lcd_str(const char *str)
{
    register char znak;
    while ((znak = *(str++)))
    {
        lcd_write_data((uint8_t)(znak));
    }
}

#if USE_LCD_INT == ON
/**
 * @brief Function for print the integer value on the LCD screen under current position of the LCD cursor.
 * @param val int type value to print on LCD screen
 * @param width Minimum number of characters to be printed. If the value to be printed is shorter than this number, the
 * result is padded with blank spaces. The value is not truncated even if the result is larger.
 * @param alignment If the value to be printed is shorter than width, this parmaeter will specify aligment of the
 * printed tekst value. This parameter can be set to "left" or "right"
 * @attention to compile for AVR ucontrollers definition of flag AVR is required.
 */
void lcd_int(int val, uint8_t width, enum alignment alignment)
{
#ifdef AVR
    lcd_int_AVR(val, width, alignment);
#else
    char buffer[20]; // 19chars for 64 bit int + end char '\0'
    buffer[0] = '\0';
    if (alignment == right)
        sprintf(buffer, "%*i", width, val);
    else
        sprintf(buffer, "%-*i", width, val);
    lcd_str(buffer);
#endif
}
#endif

#if USE_LCD_HEX == ON
/**
 * @brief Function for print the integer value in hexadecimal format on the LCD screen under current position of the LCD
 * cursor.
 * @param val int type value to print on LCD screen in hexadecimal format
 * @param width Minimum number of characters to be printed. If the value to be printed is shorter than this number, the
 * result is padded with blank spaces. The value is not truncated even if the result is larger. Width should contain
 * additional 2 characters for '0x' at the begining of the printed value.
 * @param alignment If the value to be printed is shorter than width, this parmaeter will specify aligment of the
 * printed tekst value. This parameter can be set to "left" or "right"
 * @attention to compile for AVR ucontrollers definition of flag AVR is required.
 */
void lcd_hex(int val, uint8_t width, enum alignment alignment)
{
#ifdef AVR
    lcd_hex_AVR(val, width, alignment);
#else
    char buffer[17];
    buffer[0] = '\0';
    if (alignment == right)
        sprintf(buffer, "%#*x", width, val);
    else
        sprintf(buffer, "%-#*x", width, val);
    lcd_str(buffer);
#endif
}
#endif

#if USE_LCD_BIN == ON
/**
 * @brief Function for print the integer value in hexadecimal format on the LCD screen under current position of the LCD
 * cursor.
 * @param val int type value to print on LCD screen in hexadecimal format
 * @param width Minimum number of characters to be printed. If the value to be printed is shorter than this number, the
 * result is padded with blank spaces. The value is not truncated even if the result is larger. Width should contain
 * additional 2 characters for '0x' at the begining of the printed value.
 * @attention to compile for AVR ucontrollers definition of flag AVR is required.
 */
void lcd_bin(int val, uint8_t width)
{
#ifdef AVR
    lcd_bin_AVR(val, width);
#else
    char buffer[35];
    char bin_val_buffer[35];
    char zeros_buf[35];
    buffer[0] = '\0';
    bin_val_buffer[0] = '\0';
    zeros_buf[0] = '\0';

    fill_bin_value_buffer(val, bin_val_buffer);
    fill_zeros_buffer(bin_val_buffer, width, zeros_buf);
    strcat(buffer, "0b");
    strcat(buffer, zeros_buf);
    strcat(buffer, bin_val_buffer);
    lcd_str(buffer);
#endif
}

#endif

/**
 * @brief Function that move LCD cursor to specific posiotion located under x and y coordinate
 * @param y LCD row/line number. Defined enum value LINE_1, LINE_2,... etc.
 * @param x LCD column number. Defined enum value C1, C2, C3,... etc.
 */
void lcd_locate(enum LCD_LINES y, enum LCD_COLUMNS x)
{
    switch (y)
    {
    case 0:
        y = LCD_LINE1_ADR;
        break;

#if (LCD_Y > 1)
    case 1:
        y = LCD_LINE2_ADR;
        break;
#endif
#if (LCD_Y > 2)
    case 2:
        y = LCD_LINE3_ADR;
        break;
#endif
#if (LCD_Y > 3)
    case 3:
        y = LCD_LINE4_ADR;
        break;
#endif
    default:
        break;
    }
    lcd_write_cmd((uint8_t)(LCDC_SET_DDRAM + y + x));
}
#if USE_LCD_CURSOR_HOME == ON
/**
 * @brief Function that move lcd cursor to the first posision at first row of LCD screen
 */
void lcd_home(void)
{
    lcd_write_cmd(LCDC_CLS | LCDC_HOME);
#if USE_RW_PIN == OFF
    LCD->delay_us(4900);
#endif
}
#endif

#if USE_LCD_CURSOR_ON == ON
/**
 * @brief Function that activates the visibility of the LCD cursor.
 */
void lcd_cursor_on(void)
{
    lcd_write_cmd(LCDC_ONOFF | LCDC_DISPLAYON | LCDC_CURSORON);
}
#endif

#if USE_LCD_CURSOR_OFF == ON
/**
 * @brief Function that deactivates the visibility and blinking of the LCD cursor.
 */
void lcd_cursor_off(void)
{
    lcd_write_cmd(LCDC_ONOFF | LCDC_DISPLAYON);
}
#endif
#if USE_LCD_BLINKING_CURSOR_ON == ON
/**
 * @brief Function that activates the visibility and blinking of the LCD cursor.
 */
void lcd_blinking_cursor_on(void)
{
    lcd_write_cmd(LCDC_ONOFF | LCDC_DISPLAYON | LCDC_CURSORON | LCDC_BLINKON);
}
#endif

#if LCD_BUFFERING == ON
void lcd_buf_cls(void)
{
    for(lcd_buf_position_ptr=&lcd_buffer[LINE_1][C1]; lcd_buf_position_ptr<=&lcd_buffer[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE]; lcd_buf_position_ptr++)
    {
            *lcd_buf_position_ptr=' ';
    }
    lcd_buf_position_ptr=&lcd_buffer[LINE_1][C1];
}

void lcd_buf_char(const char c)
{
    *lcd_buf_position_ptr=c;
    check_lcd_buf_possition_ptr_overflow();
}

void lcd_buf_locate(enum LCD_LINES y, enum LCD_COLUMNS x)
{
    lcd_buf_position_ptr=&lcd_buffer[y][x];
}

void lcd_buf_str(const char *str)
{
    while (*str)
    {
        *(lcd_buf_position_ptr)=*(str++);
        check_lcd_buf_possition_ptr_overflow();
    }
}

void lcd_update(void)
{
    static uint8_t lcd_cursor_position=0;
    static uint8_t lcd_line=0;
    
    for(lcd_buf_position_ptr=&lcd_buffer[LINE_1][C1]; lcd_buf_position_ptr<=&lcd_buffer[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE]; lcd_buf_position_ptr++)
    {
        lcd_char(*lcd_buf_position_ptr);
        if((++lcd_cursor_position)>=LCD_X)
        {
            lcd_cursor_position=0;
            lcd_line++;
            if(lcd_line==LCD_Y)
            {
                lcd_line=LINE_1;
            } 
            lcd_locate(lcd_line,lcd_cursor_position);
            
        }
    }
    lcd_buf_position_ptr=&lcd_buffer[LINE_1][C1];
}
#endif
  
