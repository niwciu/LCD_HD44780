/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-07 15:51:41
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:34:48
 */
#include <stdio.h>
#include "lcd_hd44780_GPIO_interface.h"


// clang-format off
#define ON   1
#define OFF  0

/*********************************Define hardware connection in your project*******************************/
// ToDo define here name of lcd PINS and it's hardware represetation 
//  #define LCD_D4 xx
//  #define LCD_D5 xx
//  etc
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
static void _delay_us(uint32_t delay_us);
static void set_LCD_E(void);
static void reset_LCD_E(void);
static void set_LCD_RS(void);
static void reset_LCD_RS(void);
static void set_LCD_RW(void);
static void reset_LCD_RW(void);
static void set_LCD_BCKL(void);
static void reset_LCD_BCKL(void);
static void init_LCD_SIGNAL_PINS_as_outputs(void);
static void init_LCD_BCKL_PIN_as_output(void);

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
// init all GPIOs

}

static void set_LCD_DATA_PINS_as_outputs(void)
{
// configure LCD_D4, LCD_D5, LCD_D6, LCD_D7 as output

}
static void set_LCD_DATA_PINS_as_inputs(void)
{
// configure LCD_D4, LCD_D5, LCD_D6, LCD_D7 as input
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    if ((data & LCD_D4_MASK))
        //set LCD_D4 to HIGW
    else
        //Set LCD_D4 to LOW

    if ((data & LCD_D5_MASK))
        //set LCD_D5 to HIGH 
    else
        //Set LCD_D5 to LOW

    if ((data & LCD_D6_MASK))
        // Set LCD_D6 to HIGH
    else
        LCD_D6_PORT->ODR &= ~LCD_D6_OUT_PIN;
        //Set LCD_D6 to LOW

    if ((data & LCD_D7_MASK))
        //Set LCD_D7 to HIGH
    else
        //Set LCD_D7 to LOW
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    uint8_t data = 0;
    // if (LCD_D4 input port is set to HIGH)
        data = LCD_D4_MASK;
    // if (LCD_D5 input port is set to HIGH)
        data |= LCD_D5_MASK;
    // if (LCD_D6 input port is set to HIGH)
        data |= LCD_D6_MASK;
    // if (LCD_D7 input port is set to HIGH)
        data |= LCD_D7_MASK;
    return data;
}

static void set_LCD_E(void)
{
   //ToDo set GPIO PIN
}
static void reset_LCD_E(void)
{
   //ToDo reset GPIO PIN
}
static void set_LCD_RS(void)
{
   //ToDo set GPIO PIN
}
static void reset_LCD_RS(void)
{
    //ToDo reset GPIO PIN
}
static void set_LCD_RW(void)
{
    //ToDo set GPIO PIN
}
static void reset_LCD_RW(void)
{
   //ToDo reset GPIO PIN
}
static void set_LCD_BCKL(void)
{
    //ToDo set GPIO PIN
}
static void reset_LCD_BCKL(void)
{
   //ToDo reset GPIO PIN
}

static void _delay_us(uint32_t delay_us)
{
    // ToDo update or create wraper
}

static void init_LCD_SIGNAL_PINS_as_outputs(void)
{
    // Initialize LCD_E LCD_RS and optionl LCD_RW GPIOs as outputs
}

static void init_LCD_BCKL_PIN_as_output(void)
{
// Initialize LCD_BCKL GPIO as outputs
}
