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

#include "lcd_hd44780_GPIO_interface.h"
#include "main.h"
#include "tim_delay.h"
#include <stdio.h>
#include "stm32f030x8.h"

LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

static void init_LCD_data_and_SIG_pins(void);
static void set_LCD_DATA_PINS_as_outputs(void);
static void set_LCD_DATA_PINS_as_inputs(void);
static void set_LCD_DATA_PINS_state(uint8_t data);
static uint8_t get_LCD_DATA_PINS_state(void);
static void mock_set_LCD_E(void);
static void mock_reset_LCD_E(void);
static void mock_set_LCD_RS(void);
static void mock_reset_LCD_RS(void);
static void mock_set_LCD_RW(void);
static void mock_reset_LCD_RW(void);
static void mock_set_LCD_BCKL(void);
static void mock_reset_LCD_BCKL(void);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_data_and_SIG_pins,
    set_LCD_DATA_PINS_as_outputs,
    set_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
    _delay_us,
    mock_set_LCD_E,
    mock_reset_LCD_E,
    mock_set_LCD_RS,
    mock_reset_LCD_RS,
    mock_set_LCD_RW,
    mock_reset_LCD_RW,
    mock_set_LCD_BCKL,
    mock_reset_LCD_BCKL,
};
const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
{
    return &LCD_IO_driver;
}

/*************LCD_IO_driver_interface implementation END***************/

static void init_LCD_data_and_SIG_pins(void)
{
    // enable BCKL of the LCD
    LL_GPIO_SetOutputPin(LCD_BCKL_GPIO_Port, LCD_BCKL_Pin);
    // enable CLK -> for this setup it's done by CUBE_IDE when generatig project files from it
    // set_LCD_DATA_PINS_as_outputs -> for this setup it's done by CUBE_IDE when generatig project files from it
    // init_LCD_SIGNAL_PINS_as_outputs -> for this setup it's done by CUBE_IDE when generatig project files from it
}

static void set_LCD_DATA_PINS_as_outputs(void)
{
    GPIO_InitStruct.Pin = LCD_D7_Pin | LCD_D6_Pin | LCD_D5_Pin | LCD_D4_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(LCD_DATA_PORT, &GPIO_InitStruct);
}
static void set_LCD_DATA_PINS_as_inputs(void)
{
    GPIO_InitStruct.Pin = LCD_D7_Pin | LCD_D6_Pin | LCD_D5_Pin | LCD_D4_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(LCD_DATA_PORT, &GPIO_InitStruct);
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    if ((data & LCD_D4_MASK))
        LL_GPIO_SetOutputPin(LCD_DATA_PORT, LCD_D4_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_DATA_PORT, LCD_D4_Pin);

    if ((data & LCD_D5_MASK))
        LL_GPIO_SetOutputPin(LCD_DATA_PORT, LCD_D5_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_DATA_PORT, LCD_D5_Pin);

    if ((data & LCD_D6_MASK))
        LL_GPIO_SetOutputPin(LCD_DATA_PORT, LCD_D6_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_DATA_PORT, LCD_D6_Pin);
    if ((data & LCD_D7_MASK))
        LL_GPIO_SetOutputPin(LCD_DATA_PORT, LCD_D7_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_DATA_PORT, LCD_D7_Pin);
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    uint8_t data = 0;
    if (LL_GPIO_IsInputPinSet(LCD_DATA_PORT, LCD_D4_Pin))
        data = LCD_D4_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_DATA_PORT, LCD_D5_Pin))
        data |= LCD_D5_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_DATA_PORT, LCD_D6_Pin))
        data |= LCD_D6_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_DATA_PORT, LCD_D7_Pin))
        data |= LCD_D7_MASK;
    return data;
}

static void mock_set_LCD_E(void)
{
    LL_GPIO_SetOutputPin(LCD_SIG_PORT, LCD_E_Pin);
}
static void mock_reset_LCD_E(void)
{
    LL_GPIO_ResetOutputPin(LCD_SIG_PORT, LCD_E_Pin);
}
static void mock_set_LCD_RS(void)
{
    LL_GPIO_SetOutputPin(LCD_SIG_PORT, LCD_RS_Pin);
}
static void mock_reset_LCD_RS(void)
{
    LL_GPIO_ResetOutputPin(LCD_SIG_PORT, LCD_RS_Pin);
}
static void mock_set_LCD_RW(void)
{
    LL_GPIO_SetOutputPin(LCD_SIG_PORT, LCD_RW_Pin);
}
static void mock_reset_LCD_RW(void)
{
    LL_GPIO_ResetOutputPin(LCD_SIG_PORT, LCD_RW_Pin);
}
static void mock_set_LCD_BCKL(void)
{
    LL_GPIO_SetOutputPin(LCD_BCKL_GPIO_Port, LCD_BCKL_Pin);
}
static void mock_reset_LCD_BCKL(void)
{
    LL_GPIO_ResetOutputPin(LCD_BCKL_GPIO_Port, LCD_BCKL_Pin);
}


