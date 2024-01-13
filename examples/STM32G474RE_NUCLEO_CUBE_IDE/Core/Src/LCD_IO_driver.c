/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-07 15:51:41 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:34:48
 */

#define LCD_DATA_PORT LCD_D7_GPIO_Port
#define LCD_SIG_PORT LCD_RS_GPIO_Port

#define LCD_D4_MASK 0x01
#define LCD_D5_MASK 0x02
#define LCD_D6_MASK 0x04
#define LCD_D7_MASK 0x08

// #include "lcd_hd44780_config.h"
#include "lcd_hd44780_interface.h"
#include "main.h"
// #include "tim_delay.h"
#include <stdio.h>

LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

static void init_LCD_data_and_SIG_pins(void);
static void set_LCD_DATA_PINS_as_outputs(void);
static void set_LCD_DATA_PINS_as_inputs(void);
static void set_LCD_DATA_PINS_state(uint8_t data);
static uint8_t get_LCD_DATA_PINS_state(void);
static void init_LCD_SIGNAL_PINS_as_outputs(void);
static void LCD_set_SIG(enum lcd_sig LCD_SIG);
static void LCD_reset_SIG(enum lcd_sig LCD_SIG);
static void _delay_us(uint32_t delay_ms);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_data_and_SIG_pins,
    set_LCD_DATA_PINS_as_outputs,
    set_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
    init_LCD_SIGNAL_PINS_as_outputs,
    LCD_set_SIG,
    LCD_reset_SIG,
    _delay_us,
};
const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
{
    return &LCD_IO_driver;
}

/*************LCD_IO_driver_interface implementation END***************/

static void init_LCD_data_and_SIG_pins(void)
{

}

static void set_LCD_DATA_PINS_as_outputs(void)
{

}
static void set_LCD_DATA_PINS_as_inputs(void)
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
static void _delay_us (uint32_t delay_ms)
{

}
