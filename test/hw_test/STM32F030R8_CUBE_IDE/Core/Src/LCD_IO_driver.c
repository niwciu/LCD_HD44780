/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-07 15:51:41 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-07 15:52:54
 */


// #include "lcd_hd44780_config.h"
#include "lcd_hd44780_interface.h"


static void init_LCD_DATA_PINS_as_outputs(void);
static void init_LCD_DATA_PINS_as_inputs(void);
static void set_LCD_DATA_PINS_state(uint8_t data);
static uint8_t get_LCD_DATA_PINS_state(void);
static void init_LCD_SIGNAL_PINS_as_outputs(void);
static void LCD_set_SIG(enum lcd_sig LCD_SIG);
static void LCD_reset_SIG(enum lcd_sig LCD_SIG);
static void delay_us(uint32_t delay_us);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_DATA_PINS_as_outputs,
    init_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
    init_LCD_SIGNAL_PINS_as_outputs,
    LCD_set_SIG,
    LCD_reset_SIG,
    delay_us,
};
const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
{
    return &LCD_IO_driver;
}

/*************LCD_IO_driver_interface implementation END***************/

static void init_LCD_DATA_PINS_as_outputs(void)
{

}
static void init_LCD_DATA_PINS_as_inputs(void)
{

}

static void set_LCD_DATA_PINS_state(uint8_t data)
{

}

static uint8_t get_LCD_DATA_PINS_state(void)
{

}

static void init_LCD_SIGNAL_PINS_as_outputs(void)
{

}

static void LCD_set_SIG(enum lcd_sig LCD_SIG)
{

}

static void LCD_reset_SIG(enum lcd_sig LCD_SIG)
{

}

static void delay_us(uint32_t delay)
{
    
}
