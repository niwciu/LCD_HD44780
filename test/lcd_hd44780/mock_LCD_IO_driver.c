/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-06 22:11:49 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-06 23:12:12
 */


#include "mock_LCD_IO_driver.h"
#include "lcd_hd44780_config.h"
#include "lcd_hd44780_interface.h"
// #include <stdio.h>

void mock_init_LCD_PINS(void);
void mock_set_LCD_DATA_PINS_as_outputs(void);
void mock_set_LCD_DATA_PINS_as_inputs(void);
void mock_set_LCD_DATA_PINS_state(uint8_t data);
uint8_t mock_get_LCD_DATA_PINS_state(void);
void mock_init_LCD_SIGNAL_PINS_as_outputs(void);
void mock_LCD_set_SIG(enum lcd_sig LCD_SIG);
void mock_LCD_reset_SIG(enum lcd_sig LCD_SIG);
void mock_delay_us(uint32_t delay_us);


/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    mock_init_LCD_PINS,
    mock_set_LCD_DATA_PINS_as_outputs,
    mock_set_LCD_DATA_PINS_as_inputs,
    mock_set_LCD_DATA_PINS_state,
    mock_get_LCD_DATA_PINS_state,
    mock_init_LCD_SIGNAL_PINS_as_outputs,
    mock_LCD_set_SIG,
    mock_LCD_reset_SIG,
    mock_delay_us,
};
const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
{
    return &LCD_IO_driver;
}

/*************LCD_IO_driver_interface implementation END***************/

void mock_init_LCD_PINS(void)
{
}

void mock_set_LCD_DATA_PINS_as_outputs(void)
{
}

void mock_set_LCD_DATA_PINS_as_inputs(void)
{
}

void mock_set_LCD_DATA_PINS_state(uint8_t data)
{
}

uint8_t mock_get_LCD_DATA_PINS_state(void)
{
    return 0;
}

void mock_init_LCD_SIGNAL_PINS_as_outputs(void)
{
}

void mock_LCD_set_SIG(enum lcd_sig LCD_SIG)
{
}

void mock_LCD_reset_SIG(enum lcd_sig LCD_SIG)
{
}

void mock_delay_us(uint32_t delay_us)
{
}

uint8_t mock_get_lcd_init_state(void)
{
    return 0;
}
