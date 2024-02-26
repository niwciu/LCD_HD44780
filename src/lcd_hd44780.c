/**
 * @file lcd_hd44780.c
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.2
 * @date 2024-02-25
 * 
 * @copyright Copyright (c) 2024

*/
#include "lcd_hd44780.h"
#include "lcd_hd44780_config.h"
#include "lcd_hd44780_driver_commands.h"
#ifdef AVR
#include "lcd_hd44780_avr_specific.h"
#endif
#include <stddef.h>
#include <stdio.h>
#include <string.h>


#define BUSY_FLAG           1 << 7
#define VAL_PREFIX_LENGHT   2U

#ifndef UNIT_TEST 
#define PRIVATE static
#else
#define PRIVATE
#endif

#if LCD_BUFFERING == ON
#define LAST_CHAR_IN_LCD_LINE (LCD_X - 1)
#define LAST_LCD_LINE (LCD_Y - 1)


typedef char lcd_pos_t;
static lcd_pos_t *lcd_buf_position_ptr;
PRIVATE char lcd_buffer[LCD_Y][LCD_X];
PRIVATE char prev_lcd_buffer[LCD_Y][LCD_X];
#endif

static const struct LCD_IO_driver_interface_struct *LCD = NULL;

bool LCD_BUFFER_UPDATE_FLAG = false;

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

#ifndef AVR
#if (USE_LCD_BIN == ON || ((LCD_BUFFERING == ON) && (LCD_USE_BUF_BIN == ON)))
static void fill_bin_value_buffer(int val, char *bin_val_buffer);
static void fill_zeros_buffer(const char *buffer, uint8_t width, char *zeros_buf);
#endif
#endif

#if LCD_BUFFERING == ON
static void check_lcd_buf_possition_ptr_overflow(void);
static void copy_lcd_buf_2_prev_lcd_buf(void);
static void update_lcd_curosr_possition(uint8_t *lcd_cursor_position, uint8_t *lcd_line, uint8_t *missed_char_counter_in_LCD_line);
static void write_lcd_buf_2_lcd(const uint8_t *lcd_cursor_position, const uint8_t *lcd_line, uint8_t *missed_char_counter_in_LCD_line, const lcd_pos_t *prev_lcd_buff_pos_ptr);
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
#ifndef AVR
#if USE_LCD_BIN == ON
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
    uint8_t buf_len = strlen(buffer);
    uint8_t total_str_width = width + VAL_PREFIX_LENGHT;
    if (buf_len < (total_str_width))
    {
        uint8_t zeros_qty = width - ((strlen(buffer) + VAL_PREFIX_LENGHT));
        for (uint8_t j = 0; j < zeros_qty; j++)
        {
            strcat(zeros_buf, "0");
        }
    }
}
#endif
#endif

#if LCD_BUFFERING == ON
static void check_lcd_buf_possition_ptr_overflow(void)
{
    lcd_buf_position_ptr++;
    if (lcd_buf_position_ptr > &lcd_buffer[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE])
    {
        lcd_buf_position_ptr = &lcd_buffer[LINE_1][C1];
    }
}
static void copy_lcd_buf_2_prev_lcd_buf(void)
{
    for (uint8_t y = 0; y < LCD_Y; y++)
    {
        for (uint8_t x = 0; x < LCD_X; x++)
        {
            prev_lcd_buffer[y][x] = lcd_buffer[y][x];
        }
    }
}
static void update_lcd_curosr_possition(uint8_t *lcd_cursor_position, uint8_t *lcd_line, uint8_t *missed_char_counter_in_LCD_line)
{
    (*lcd_cursor_position)++;
    if ((*lcd_cursor_position) >= LCD_X)
    {
        *lcd_cursor_position = 0;
        (*lcd_line)++;
        *missed_char_counter_in_LCD_line = 0;
        if (*lcd_line == LCD_Y)
        {
            *lcd_line = LINE_1;
        }
        lcd_locate(*lcd_line, *lcd_cursor_position);
    }
}

static void write_lcd_buf_2_lcd(const uint8_t *lcd_cursor_position, const uint8_t *lcd_line, uint8_t *missed_char_counter_in_LCD_line, const lcd_pos_t *prev_lcd_buff_pos_ptr)
{
    if ((*lcd_buf_position_ptr) != (*prev_lcd_buff_pos_ptr))
    {
        if (*missed_char_counter_in_LCD_line != 0)
        {
            lcd_locate(*lcd_line, *lcd_cursor_position);
            *missed_char_counter_in_LCD_line = 0;
        }
        lcd_char(*lcd_buf_position_ptr);
    }
    else
    {
        (*missed_char_counter_in_LCD_line)++;
    }
}

#endif


void lcd_init(void)
{
    register_LCD_IO_driver();
    LCD->init_LCD_pins();
    lcd_disable_backlight();
    /**************************BASIC LCD INIT - basing on DS init procedure***************************************/
    // set all LCD signals to High for more than 15ms ->bit different than in DS based on other implementations from the internet
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
    // ENTRY MODe SET do not shift the LCD shift cursor right after placing a char
    lcd_write_cmd(LCDC_ENTRY_MODE | LCDC_ENTRYR);
    /*********************************END of BASIC LCD INIT***************************************/
#if LCD_BUFFERING == ON
    // clear lcd_buffer by putting spaces inside of the buffer
    lcd_buf_cls();
    // copy lcd_buffer with spaces to prev_lcd_buffer
    copy_lcd_buf_2_prev_lcd_buf();
    // clear flag due to init procedure that reset LCD screen and buffers
    LCD_BUFFER_UPDATE_FLAG = false;
#endif
}
/**
 * @brief Function for disabling backlight od the LCD
 */
void lcd_enable_backlight(void)
{
#if LCD_BCKL_PIN_EN_STATE == HIGH
    LCD->set_SIG(LCD_BCKL);
#else
    LCD->reset_SIG(LCD_BCKL);
#endif
}

/**
 * @brief Function for enabling backlight od the LCD
 */
void lcd_disable_backlight(void)
{
#if LCD_BCKL_PIN_EN_STATE == HIGH
    LCD->reset_SIG(LCD_BCKL);
#else
    LCD->set_SIG(LCD_BCKL);
#endif
}

/**
 * @brief Function that clears the LCD screen and sets the cursor on the position of the first character in the first line of the LCD
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
 * 
 * @param CGRAM_char_index Position/address of the character in CGRAM of the LCD where defined char should be written.
 * For the predefined example of special characters, taken values are defined in the type enum LCD_CGRAM_BANK_1_e that is declared
 * in lcd-hd44780.h
 * 
 * @param def_char Pointer to the predefined special character.
 * 
 * @note CGRAM_char_index - This Parameter can take values from 0 to 7. For the predefined example of special
 * characters, taken values are defined in the type enum LCD_CGRAM that is defined in lcd_hd44780_def_char.h
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

/**
 * @brief Function that loads to LCD_CGRAM predefined characters form specific user char_bank
 * 
 * @param char_bank - pointer to selected user char bank that function should load to LCD_CGRAM. Char banks are defined in lcd_hd44780_def_char.h 
 */
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
 * @brief Function for printing the char on the LCD screen under the current position of the LCD cursor.
 * @param C char (for example '1') or its ASCI code (0x31).
 * @note For user-defined char, place CGRAM_char_index (Position/address of the character in CGRAM of the LCD where
 * defined char was written).
 */
void lcd_char(const char C)
{
    uint8_t data = (uint8_t)(C);
    lcd_write_data(data);
}

/**
 * @brief Function for printing/writing the string on the LCD screen starting from the current LCD cursor position.
 * @param str string that should be printed/written on the LCD screen
 */
void lcd_str(char *str)
{
    while ((*str)!='\0')
    {
        lcd_char(*str);
        str++;
    }
}

#if USE_LCD_INT == ON
/**
 * @brief Function for printing the integer value on the LCD screen under the current position of the LCD cursor.
 * @param val int type value to print on LCD screen
 * @param width Minimum number of characters to be printed. If the value to be printed is shorter than this number, the
 * result is padded with blank spaces. The value is not truncated even if the result is larger.
 * @param alignment This parameter can only accept values defined in ::LCD_alignment_e. If the value to be printed is shorter than the width, this parameter will specify the alignment of the
 * printed text value.
 * @attention to compile for AVR ucontrollers definition of flag AVR is required.
 */
void lcd_int(int val, uint8_t width, enum LCD_alignment_e alignment)
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
 * @brief Function for printing the integer value in hexadecimal format on the LCD screen under the current position of the LCD
 * cursor.
 * @param val int type value to print on LCD screen in hexadecimal format
 * @param width Minimum number of characters to be printed. If the value to be printed is shorter than this number, the
 * result is padded with blank spaces. The value is not truncated even if the result is larger. The width should contain
 * additional 2 characters for '0x' at the beginning of the printed value.
 * @param alignment This parameter can only accept values defined in ::LCD_alignment_e. If the value to be printed is shorter than the width, this parameter will specify the alignment of the
 * printed text value.
 * @attention to compile for AVR ucontrollers definition of flag AVR is required.
 */
void lcd_hex(int val, uint8_t width, enum LCD_alignment_e alignment)
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
 * @brief Function for printing the integer value in hexadecimal format on the LCD screen under the current position of the LCD
 * cursor.
 * @param val int type value to print on LCD screen in hexadecimal format
 * @param width Minimum number of characters to be printed. If the value to be printed is shorter than this number, the
 * result is padded with blank spaces. The value is not truncated even if the result is larger. The width should contain
 * additional 2 characters for '0x' at the beginning of the printed value.
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
 * @brief Function that moves LCD cursor to a specific position located under the x and y coordinate
 * @param y LCD row/line number. This parameter can only accept values defined in ::LCD_LINES_e.
 * @param x LCD column number. This parameter can only accept values defined in ::LCD_COLUMNS_e.
 */
void lcd_locate(enum LCD_LINES_e y, enum LCD_COLUMNS_e x)
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
 * @brief Function that moves LCD cursor to the first position at the first row of the LCD screen
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
/**
 * @brief Function that puts spaces(0x32) in the whole LCD buffer and sets the cursor on the position of the first character in the first line of the LCD
 * buffer.
 */
void lcd_buf_cls(void)
{
    for (lcd_buf_position_ptr = &lcd_buffer[LINE_1][C1]; lcd_buf_position_ptr <= &lcd_buffer[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE]; lcd_buf_position_ptr++)
    {
        *lcd_buf_position_ptr = ' ';
    }
    lcd_buf_position_ptr = &lcd_buffer[LINE_1][C1];
    LCD_BUFFER_UPDATE_FLAG = true;
}

/**
 * @brief Function for adding the char to the LCD buffer under the current position of the LCD buffer.
 * @param C char (for example '1') or its ASCI code (0x31).
 * @note For user-defined char, place LCD_CGRAM_BANK_x_e (Position/address of the character in CGRAM of the LCD where
 * defined char was written).
 */
void lcd_buf_char(const char c)
{
    *lcd_buf_position_ptr = c;
    check_lcd_buf_possition_ptr_overflow();
    LCD_BUFFER_UPDATE_FLAG = true;
}

/**
 * @brief Function that changes the current LCD buffer position pointer to a specific position located under the x and y coordinate
 * @param y LCD row/line number. This parameter can only accept values defined in ::LCD_LINES_e.
 * @param x LCD column number. This parameter can only accept values defined in ::LCD_COLUMNS_e.
 */
void lcd_buf_locate(enum LCD_LINES_e y, enum LCD_COLUMNS_e x)
{
    lcd_buf_position_ptr = &lcd_buffer[y][x];
}

/**
 * @brief Function for placing the string in the LCD buffer starts from the current LCD buffer position pointer.
 * @param str string that should be placed in the LCD buffer
 */
void lcd_buf_str(const char *str)
{
    while (*str)
    {
        *(lcd_buf_position_ptr) = *(str++);
        check_lcd_buf_possition_ptr_overflow();
    }
    LCD_BUFFER_UPDATE_FLAG = true;
}

/**
 * @brief Function that prints on the LCD screen the content of The LCD buffer.
 * The function sets also The LCD buffer position pointer to the First line's first character.
 */
void lcd_update(void)
{
    if(LCD_BUFFER_UPDATE_FLAG==true)
    {
        uint8_t lcd_cursor_position = 0;
        uint8_t lcd_line = 0;
        uint8_t missed_char_counter_in_LCD_line = 0;
        const lcd_pos_t *prev_lcd_buff_pos_ptr = &prev_lcd_buffer[LINE_1][C1];

        for (lcd_buf_position_ptr = &lcd_buffer[LINE_1][C1]; lcd_buf_position_ptr <= &lcd_buffer[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE]; lcd_buf_position_ptr++)
        {
            write_lcd_buf_2_lcd(&lcd_cursor_position, &lcd_line, &missed_char_counter_in_LCD_line, prev_lcd_buff_pos_ptr);
            update_lcd_curosr_possition(&lcd_cursor_position, &lcd_line, &missed_char_counter_in_LCD_line);
            prev_lcd_buff_pos_ptr++;
        }

        lcd_buf_position_ptr = &lcd_buffer[LINE_1][C1];
        copy_lcd_buf_2_prev_lcd_buf();
        LCD_BUFFER_UPDATE_FLAG = false;
    }
}

#if USE_LCD_BUF_INT == ON
/**
 * @brief Function for adding integer value as string to the LCD buffer under the current position of the LCD buffer pointer.
 * @param val int type value to add to LCD buffer
 * @param width Minimum number of characters to be added to LCD buffer. If the value to be added to the LCD buffer is shorter than width, the
 * result is padded with blank spaces. The value to be added to the buffer as a string is not truncated if the string length is larger than the width value.
 * @param alignment This parameter can only accept values defined in ::LCD_alignment_e. If the value to be printed is shorter than the width, this parameter will specify the alignment of the
 * printed text value.
 * @attention to compile for AVR ucontrollers, definition of flag AVR is required.
 */
void lcd_buf_int(int val, uint8_t width, enum LCD_alignment_e alignment)
{
#ifdef AVR
    lcd_buf_int_AVR(val, width, alignment);
#else
    char buffer[20]; // 19chars for 64 bit int + end char '\0'
    buffer[0] = '\0';
    if (alignment == right)
        sprintf(buffer, "%*i", width, val);
    else
        sprintf(buffer, "%-*i", width, val);
    lcd_buf_str(buffer);
#endif
}
#endif

#if USE_LCD_BUF_HEX == ON
/**
 * @brief  Function for adding integer value in hexadecimal format as a string to the LCD buffer under the current position of the LCD buffer pointer.
 * @param val  int type value to add to LCD buffer as a string in hexadecimal format
 * @param width Minimum number of characters to be added to lcd buffer. If the value to be added to the buffer is shorter than the width, the
 * result is padded with blank spaces. The value to be added to the buffer as a string is not truncated if the string length is larger than the width value. Width should contain
 * additional 2 characters for "0x" at the beginning of the value represented as a string. example: 0x01-> width=4
 * @param alignment This parameter can only accept values defined in ::LCD_alignment_e. If the value to be printed is shorter than the width, this parameter will specify the alignment of the
 * printed text value.
 * @attention to compile for AVR ucontrollers, definition of flag AVR is required.
 */
void lcd_buf_hex(int val, uint8_t width, enum LCD_alignment_e alignment)
{
#ifdef AVR
    lcd_buf_hex_AVR(val, width, alignment);
#else
    char buffer[17];
    buffer[0] = '\0';
    if (alignment == right)
        sprintf(buffer, "%#*x", width, val);
    else
        sprintf(buffer, "%-#*x", width, val);
    lcd_buf_str(buffer);
#endif
}
#endif

#if USE_LCD_BUF_BIN == ON
/**
 * @brief Function for adding to the LCD buffer the integer value in binary format as a string under the current position of the LCD buffer pointer
 * @param val int type value to be added to the LCD buffer as a string in hexadecimal format
 * @param width Minimum number of characters to be added to LCD buffer. If the value to be added to the buffer as string length is shorter than width, the
 * result is padded with blank spaces. The value to be added to the buffer as a string is not truncated if the string length represents the value in binary format length
 * is larger than the width value. The width should contain an additional 2 characters for "0b" at the beginning of the value represented as a string. example: 0b01-> width=4
 * @attention to compile for AVR ucontrollers, definition of flag AVR is required.
 */
void lcd_buf_bin(int val, uint8_t width)
{
#ifdef AVR
    lcd_buf_bin_AVR(val, width);
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
    lcd_buf_str(buffer);
#endif
}

#endif
#endif
