/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-06 21:39:30
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-07 13:48:35
 */

#include "lcd_hd44780.h"

static const struct LCD_IO_driver_interface_struct *LCD = NULL;

static void register_LCD_IO_driver(void);
static void lcd_set_all_SIG(void);
static void lcd_reset_all_SIG(void);
static void lcd_write_4bit_data(uint8_t data);

/**
 * @brief  Function that initialize LCD in 4-bit mode with or without LCD R/W Pin handling.
 * @attention LCD R/W handling should be configured in lcd_hd44780_config.h by setting USE_RW_PIN to  1 (Enable R/W Pin
 * handling) or 0 (disable R/W Pin handling).
 */
void lcd_init(void)
{
    register_LCD_IO_driver();
    /**************************BASIC LCD INIT - basing on DS init procedure***************************************/
    // init I/O for LCD
    LCD->init_LCD_pins();

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
    uint8_t cmd = 0x00; //define cmd to send
    uint8_t readed_data;
    LCD->reset_SIG(LCD_RS);

#if USE_RW_PIN == ON
    LCD->reset_SIG(LCD_RW);
#endif
    lcd_write_4bit_data((cmd) >> 4);
    lcd_write_4bit_data((cmd)&0x0F);
#if USE_RW_PIN == ON
    //check_BUSSY_FALG
    LCD->set_data_pins_as_inputs();
    LCD->reset_SIG(LCD_RS);
    LCD->set_SIG(LCD_RW);
    //read 4 MSB
    LCD->set_SIG(LCD_E);
    readed_data = (LCD->read_data() << 4);
    LCD->reset_SIG(LCD_E);
    //read 4 LSB
    LCD->set_SIG(LCD_E);
    readed_data |= (LCD->read_data() & 0x0F);
    LCD->reset_SIG(LCD_E);
#else
    LCD->delay_us(120);
#endif
    LCD->reset_SIG(LCD_RW);
    LCD->set_data_pins_as_outputs();

    // DISPLAY_ON_OFF send cmd -> enable lcd

    // ENTRY MODe SET do not shift LCD shift cursor right after placing a char

    // LCD clear screen
    /*********************************END of BASIC LCD INIT***************************************/
    // define sepcial characters in LCD CGRAM
}

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
