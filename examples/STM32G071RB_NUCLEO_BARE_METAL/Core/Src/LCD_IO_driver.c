/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-07 15:51:41 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:34:48
 */

#define LCD_D4_MASK 0x01
#define LCD_D5_MASK 0x02
#define LCD_D6_MASK 0x04
#define LCD_D7_MASK 0x08

// #include "lcd_hd44780_config.h"
#include <stdio.h>
#include "lcd_hd44780_interface.h"
#include "main.h"
#include "tim_delay.h"

static void init_LCD_data_and_SIG_pins(void);
static void set_LCD_DATA_PINS_as_outputs(void);
static void set_LCD_DATA_PINS_as_inputs(void);
static void set_LCD_DATA_PINS_state(uint8_t data);
static uint8_t get_LCD_DATA_PINS_state(void);
static void init_LCD_SIGNAL_PINS_as_outputs(void);
static void LCD_set_SIG(enum lcd_sig LCD_SIG);
static void LCD_reset_SIG(enum lcd_sig LCD_SIG);

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
    // //enable BCKL of the LCD
    // LL_GPIO_SetOutputPin(LCD_BCKL_GPIO_Port, LCD_BCKL_Pin);
    // //enable CLK -> for this setup it's done by CUBE_IDE when generatig project files from it
    // //set_LCD_DATA_PINS_as_outputs -> for this setup it's done by CUBE_IDE when generatig project files from it
    // //init_LCD_SIGNAL_PINS_as_outputs -> for this setup it's done by CUBE_IDE when generatig project files from it
}

static void set_LCD_DATA_PINS_as_outputs(void)
{
    // GPIO_InitStruct.Pin = LCD_D7_Pin | LCD_D6_Pin | LCD_D5_Pin | LCD_D4_Pin;
    // GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    // GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    // GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    // GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    // LL_GPIO_Init(LCD_DATA_PORT, &GPIO_InitStruct);
}
static void set_LCD_DATA_PINS_as_inputs(void)
{
    // GPIO_InitStruct.Pin = LCD_D7_Pin | LCD_D6_Pin | LCD_D5_Pin | LCD_D4_Pin;
    // GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    // GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    // LL_GPIO_Init(LCD_DATA_PORT, &GPIO_InitStruct);
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    // if ((data & LCD_D4_MASK))
    //     // LL_GPIO_SetOutputPin(LCD_DATA_PORT, LCD_D4_Pin);
    // else
    //     // LL_GPIO_ResetOutputPin(LCD_DATA_PORT, LCD_D4_Pin);

    // if ((data & LCD_D5_MASK))
    //     // LL_GPIO_SetOutputPin(LCD_DATA_PORT, LCD_D5_Pin);
    // else
    //     // LL_GPIO_ResetOutputPin(LCD_DATA_PORT, LCD_D5_Pin);

    // if ((data & LCD_D6_MASK))
    //     // LL_GPIO_SetOutputPin(LCD_DATA_PORT, LCD_D6_Pin);
    // else
    //     // LL_GPIO_ResetOutputPin(LCD_DATA_PORT, LCD_D6_Pin);
    // if ((data & LCD_D7_MASK))
    //     // LL_GPIO_SetOutputPin(LCD_DATA_PORT, LCD_D7_Pin);
    // else
    //     // LL_GPIO_ResetOutputPin(LCD_DATA_PORT, LCD_D7_Pin);
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    uint8_t data = 0;
    // if (LL_GPIO_IsInputPinSet(LCD_DATA_PORT, LCD_D4_Pin))
    //     // data = LCD_D4_MASK;
    // if (LL_GPIO_IsInputPinSet(LCD_DATA_PORT, LCD_D5_Pin))
    //     // data |= LCD_D5_MASK;
    // if (LL_GPIO_IsInputPinSet(LCD_DATA_PORT, LCD_D6_Pin))
    //     // data |= LCD_D6_MASK;
    // if (LL_GPIO_IsInputPinSet(LCD_DATA_PORT, LCD_D7_Pin))
    //     // data |= LCD_D7_MASK;
    return data;
}

static void init_LCD_SIGNAL_PINS_as_outputs(void)
{
#if USE_RW_PIN == 1
    // GPIO_InitStruct.Pin = LCD_RS_Pin | LCD_E_Pin | LCD_RW_Pin;
    // GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    // GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    // GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    // GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    // LL_GPIO_Init(LCD_SIG_PORT, &GPIO_InitStruct);

#else
    // GPIO_InitStruct.Pin = LCD_RS_Pin | LCD_E_Pin;
    // GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    // GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    // GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    // GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    // LL_GPIO_Init(LCD_SIG_PORT, &GPIO_InitStruct);
#endif
}

static void LCD_set_SIG(enum lcd_sig LCD_SIG)
{
    switch (LCD_SIG)
    {
    case LCD_RS:
        // LL_GPIO_SetOutputPin(LCD_SIG_PORT, LCD_RS_Pin);
        break;
    case LCD_E:
        // LL_GPIO_SetOutputPin(LCD_SIG_PORT, LCD_E_Pin);
        break;
    case LCD_RW:
        // LL_GPIO_SetOutputPin(LCD_SIG_PORT, LCD_RW_Pin);
        break;
    default:
        break;
    }
}

static void LCD_reset_SIG(enum lcd_sig LCD_SIG)
{
    switch (LCD_SIG)
    {
    case LCD_RS:
        // LL_GPIO_ResetOutputPin(LCD_SIG_PORT, LCD_RS_Pin);
        break;
    case LCD_E:
        // LL_GPIO_ResetOutputPin(LCD_SIG_PORT, LCD_E_Pin);
        break;
    case LCD_RW:
        // LL_GPIO_ResetOutputPin(LCD_SIG_PORT, LCD_RW_Pin);
        break;
    default:
        break;
    }
}
