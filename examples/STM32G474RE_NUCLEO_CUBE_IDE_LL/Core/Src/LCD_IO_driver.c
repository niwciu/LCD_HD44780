/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-07 15:51:41
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:34:48
 */

#define LCD_DATA_PORTB LCD_D4_GPIO_Port
#define LCD_SIG_PORT LCD_RS_GPIO_Port

#define LCD_D4_MASK 0x01
#define LCD_D5_MASK 0x02
#define LCD_D6_MASK 0x04
#define LCD_D7_MASK 0x08

#define ON 1
#define OFF 0

// #include "lcd_hd44780_config.h"
#include "lcd_hd44780_GPIO_interface.h"
#include "main.h"
#include "tim_delay.h"
#include "stm32g474xx.h"
#include <stdio.h>

LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

static void init_LCD_data_and_SIG_pins(void);
static void set_LCD_DATA_PINS_as_outputs(void);
static void set_LCD_DATA_PINS_as_inputs(void);
static void set_LCD_DATA_PINS_state(uint8_t data);
static uint8_t get_LCD_DATA_PINS_state(void);
static void set_LCD_E(void);
static void reset_LCD_E(void);
static void set_LCD_RS(void);
static void reset_LCD_RS(void);
static void set_LCD_RW(void);
static void reset_LCD_RW(void);
static void set_LCD_BCKL(void);
static void reset_LCD_BCKL(void);
// static void init_LCD_SIGNAL_PINS_as_outputs(void);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_data_and_SIG_pins,
    set_LCD_DATA_PINS_as_outputs,
    set_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
    _delay_us,
    set_LCD_E,
    reset_LCD_E,
    set_LCD_RS,
    reset_LCD_RS,
    set_LCD_RW,
    reset_LCD_RW,
    set_LCD_BCKL,
    reset_LCD_BCKL,
};
const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
{
    return &LCD_IO_driver;
}

/*************LCD_IO_driver_interface implementation END***************/

static void init_LCD_data_and_SIG_pins(void)
{
    // all pins are initialized in CubeIDE code
}

static void set_LCD_DATA_PINS_as_outputs(void)
{

    GPIO_InitStruct.Pin = LCD_D6_Pin | LCD_D5_Pin | LCD_D4_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(LCD_DATA_PORTB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_D7_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(LCD_D7_GPIO_Port, &GPIO_InitStruct);
}
static void set_LCD_DATA_PINS_as_inputs(void)
{
    GPIO_InitStruct.Pin = LCD_D6_Pin | LCD_D5_Pin | LCD_D4_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(LCD_DATA_PORTB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_D7_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(LCD_D7_GPIO_Port, &GPIO_InitStruct);
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    if ((data & LCD_D4_MASK))
        LL_GPIO_SetOutputPin(LCD_D4_GPIO_Port, LCD_D4_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_D4_GPIO_Port, LCD_D4_Pin);

    if ((data & LCD_D5_MASK))
        LL_GPIO_SetOutputPin(LCD_D5_GPIO_Port, LCD_D5_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_D5_GPIO_Port, LCD_D5_Pin);

    if ((data & LCD_D6_MASK))
        LL_GPIO_SetOutputPin(LCD_D6_GPIO_Port, LCD_D6_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_D6_GPIO_Port, LCD_D6_Pin);
    if ((data & LCD_D7_MASK))
        LL_GPIO_SetOutputPin(LCD_D7_GPIO_Port, LCD_D7_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_D7_GPIO_Port, LCD_D7_Pin);
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    uint8_t data = 0;
    if (LL_GPIO_IsInputPinSet(LCD_D4_GPIO_Port, LCD_D4_Pin))
        data = LCD_D4_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_D5_GPIO_Port, LCD_D5_Pin))
        data |= LCD_D5_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_D6_GPIO_Port, LCD_D6_Pin))
        data |= LCD_D6_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_D7_GPIO_Port, LCD_D7_Pin))
        data |= LCD_D7_MASK;
    return data;
}

static void set_LCD_E(void)
{
    LL_GPIO_SetOutputPin(LCD_E_GPIO_Port, LCD_E_Pin);
}
static void reset_LCD_E(void)
{
    LL_GPIO_ResetOutputPin(LCD_E_GPIO_Port, LCD_E_Pin);
}
static void set_LCD_RS(void)
{
    LL_GPIO_SetOutputPin(LCD_RS_GPIO_Port, LCD_RS_Pin);
}
static void reset_LCD_RS(void)
{
    LL_GPIO_ResetOutputPin(LCD_RS_GPIO_Port, LCD_RS_Pin);
}
static void set_LCD_RW(void)
{
    // LL_GPIO_SetOutputPin(LCD_RW_GPIO_Port, LCD_RW_Pin);
}
static void reset_LCD_RW(void)
{
    // LL_GPIO_ResetOutputPin(LCD_RW_GPIO_Port, LCD_RW_Pin);
}
static void set_LCD_BCKL(void)
{
    LL_GPIO_SetOutputPin(LCD_BCKL_GPIO_Port, LCD_BCKL_Pin);
}
static void reset_LCD_BCKL(void)
{
    LL_GPIO_ResetOutputPin(LCD_BCKL_GPIO_Port, LCD_BCKL_Pin);
}

//CUBE IDE initiize all outputs and inputs
// static void init_LCD_SIGNAL_PINS_as_outputs(void)
// {
// #if USE_RW_PIN == ON
//     GPIO_InitStruct.Pin = LCD_RW_Pin;
//     GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//     GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//     GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//     GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//     LL_GPIO_Init(LCD_RW_GPIO_Port, &GPIO_InitStruct);
// #endif
//     GPIO_InitStruct.Pin = LCD_RS_Pin;
//     GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//     GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//     GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//     GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//     LL_GPIO_Init(LCD_RS_GPIO_Port, &GPIO_InitStruct);

//     GPIO_InitStruct.Pin = LCD_E_Pin;
//     GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//     GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//     GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//     GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//     LL_GPIO_Init(LCD_E_GPIO_Port, &GPIO_InitStruct);
// }
