/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-07 15:51:41
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:34:48
 */
#include <stdio.h>
#include "lcd_hd44780_interface.h"
#include "lcd_hd44780_config.h"
#include "user_interface.h"
#include "ets_sys.h"
#include "osapi.h"
// #include "..\gpio.h"


// clang-format off
#define ON   1
#define OFF  0

/*********************************Define hardware connection in your project*******************************/
// ToDo define here name of lcd PINS and it's hardware represetation 
#define LCD_D5_MUX      PERIPHS_IO_MUX_MTDI_U
#define LCD_D5_PIN      BIT12
#define LCD_D5_FUNC     FUNC_GPIO12

#define LCD_D6_MUX      PERIPHS_IO_MUX_MTCK_U
#define LCD_D6_PIN      BIT13
#define LCD_D6_FUNC     FUNC_GPIO13

#define LCD_D4_MUX      PERIPHS_IO_MUX_MTMS_U
#define LCD_D4_PIN      BIT14
#define LCD_D4_FUNC     FUNC_GPIO14

#define LCD_D7_MUX      PERIPHS_IO_MUX_MTDO_U
#define LCD_D7_PIN      BIT15
#define LCD_D7_FUNC     FUNC_GPIO15

#define LCD_BCKL_MUX     PERIPHS_IO_MUX_GPIO4_U 
#define LCD_BCKL_PIN     BIT4
#define LCD_BCKL_FUNC    FUNC_GPIO4

#define LCD_E_MUX       PERIPHS_IO_MUX_U0TXD_U
#define LCD_E_PIN       BIT1
#define LCD_E_FUNC      FUNC_GPIO1

#define LCD_RS_MUX      PERIPHS_IO_MUX_U0RXD_U
#define LCD_RS_PIN      BIT3
#define LCD_RS_FUNC     FUNC_GPIO3

/****************************END OFF define hardware connection in your application***********************/

#define LCD_D4_MASK         0x01
#define LCD_D5_MASK         0x02
#define LCD_D6_MASK         0x04
#define LCD_D7_MASK         0x08
// clang-format on

static void init_LCD_data_and_SIG_pins(void);
static void set_LCD_DATA_PINS_as_outputs(void);
static void set_LCD_DATA_PINS_as_inputs(void);
static void set_LCD_DATA_PINS_state(uint8_t data);
static uint8_t get_LCD_DATA_PINS_state(void);
static void LCD_set_SIG(enum lcd_sig LCD_SIG);
static void LCD_reset_SIG(enum lcd_sig LCD_SIG);
static void wraper_delay_us(uint32_t delay_us);
// static void init_LCD_SIGNAL_PINS_as_outputs(void);
// static void init_LCD_BCKL_PIN_as_output(void);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_data_and_SIG_pins,
    set_LCD_DATA_PINS_as_outputs,
    set_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
    LCD_set_SIG,
    LCD_reset_SIG,
    wraper_delay_us,
};
const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
{
    return &LCD_IO_driver;
}

/*************LCD_IO_driver_interface implementation END***************/

static void init_LCD_data_and_SIG_pins(void)
{
    PIN_FUNC_SELECT(LCD_RS_MUX,LCD_RS_FUNC);
    PIN_FUNC_SELECT(LCD_E_MUX,LCD_E_FUNC);
    PIN_FUNC_SELECT(LCD_D4_MUX,LCD_D4_FUNC);
    PIN_FUNC_SELECT(LCD_D5_MUX,LCD_D5_FUNC);
    PIN_FUNC_SELECT(LCD_D6_MUX,LCD_D6_FUNC);
    PIN_FUNC_SELECT(LCD_D7_MUX,LCD_D7_FUNC);
    PIN_FUNC_SELECT(LCD_BCKL_MUX,LCD_BCKL_FUNC);
    gpio_output_set(0,
                    LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN|LCD_RS_PIN|LCD_E_PIN|LCD_BCKL_PIN,
                    LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN|LCD_RS_PIN|LCD_E_PIN|LCD_BCKL_PIN,
                    0);

}

static void set_LCD_DATA_PINS_as_outputs(void)
{
// configure LCD_D4, LCD_D5, LCD_D6, LCD_D7 as output
    gpio_output_set(
                    0,
                    LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN,
                    LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN,
                    0);

}
static void set_LCD_DATA_PINS_as_inputs(void)
{
// configure LCD_D4, LCD_D5, LCD_D6, LCD_D7 as input
    gpio_output_set(
                    0,
                    0,
                    0,
                    LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN);
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    if ((data & LCD_D4_MASK))
        //Set LCD_D4 to HIGH
        gpio_output_set(LCD_D4_PIN,0,LCD_D4_PIN, 0);
    else
        //Set LCD_D4 to LOW
        gpio_output_set(0,LCD_D4_PIN,LCD_D4_PIN, 0);

    if ((data & LCD_D5_MASK))
        //set LCD_D5 to HIGH 
        gpio_output_set(LCD_D5_PIN,0,LCD_D5_PIN, 0);
    else
        //Set LCD_D5 to LOW
        gpio_output_set(0,LCD_D5_PIN,LCD_D5_PIN, 0);

    if ((data & LCD_D6_MASK))
        // Set LCD_D6 to HIGH
        gpio_output_set(LCD_D6_PIN,0,LCD_D6_PIN, 0);
    else
        //Set LCD_D6 to LOW
        gpio_output_set(0,LCD_D6_PIN,LCD_D6_PIN, 0);
    if ((data & LCD_D7_MASK))
        //Set LCD_D7 to HIGH
        gpio_output_set(LCD_D7_PIN,0,LCD_D7_PIN, 0);
    else
        //Set LCD_D7 to LOW
        gpio_output_set(0,LCD_D7_PIN,LCD_D7_PIN, 0);
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    // uint8_t data = 0;
    // // if (LCD_D4 input port is set to HIGH)
    //     data = LCD_D4_MASK;
    // // if (LCD_D5 input port is set to HIGH)
    //     data |= LCD_D5_MASK;
    // // if (LCD_D6 input port is set to HIGH)
    //     data |= LCD_D6_MASK;
    // // if (LCD_D7 input port is set to HIGH)
    //     data |= LCD_D7_MASK;
    // return data;
}

static void LCD_set_SIG(enum lcd_sig LCD_SIG)
{
    switch (LCD_SIG)
    {
    case LCD_RS:
        // Set LCD_RS to High
        gpio_output_set(LCD_RS_PIN,0,LCD_RS_PIN, 0);
        break;
    case LCD_E:
        // Set LCD_E to High
        gpio_output_set(LCD_E_PIN,0,LCD_E_PIN, 0);
        break;
#if USE_RW_PIN == ON
    case LCD_RW:
        // Set LCD_RW to High
        gpio_output_set(LCD_RW_PIN,0,LCD_RW_PIN, 0);
        break;
#endif
    case LCD_BCKL:
        // Set LCD_BCKL to High
        gpio_output_set(LCD_BCKL_PIN,0,LCD_BCKL_PIN, 0);
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
        // Set LCD_RS to LOW
        gpio_output_set(0,LCD_RS_PIN,LCD_RS_PIN, 0);
        break;
    case LCD_E:
       // Set LCD_E to LOW
       gpio_output_set(0,LCD_E_PIN,LCD_E_PIN, 0);
        break;
#if USE_RW_PIN == 1
    case LCD_RW:
        // Set LCD_RW to LOW
        gpio_output_set(0,LCD_RW_PIN,LCD_RW_PIN, 0);
        break;
#endif
    case LCD_BCKL:
        // Set LCD_BCKL to LOW
        gpio_output_set(0,LCD_BCKL_PIN,LCD_BCKL_PIN,0);
        break;
    default:
        break;
    }
}

static void wraper_delay_us(uint32_t delay_us)
{
    // ToDo update wraper
    os_delay_us((uint16_t)(delay_us));
}

// static void init_LCD_SIGNAL_PINS_as_outputs(void)
// {
//     // Initialize LCD_E LCD_RS and optionl LCD_RW GPIOs as outputs
// }

// static void init_LCD_BCKL_PIN_as_output(void)
// {
// // Initialize LCD_BCKL GPIO as outputs
// }
