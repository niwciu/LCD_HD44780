/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-07 15:51:41
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:34:48
 */
#include <stdio.h>
#include "stm32g070xx.h"
#include "lcd_hd44780_GPIO_interface.h"
#include "main.h"
#include "tim_delay.h"

// clang-format off
#define ON   1
#define OFF  0

#define LCD_D7_PORT         GPIOA
#define LCD_D6_PORT         GPIOB
#define LCD_D5_PORT         GPIOB
#define LCD_D4_PORT         GPIOB
#define LCD_RS_PORT         GPIOA
#define LCD_E_PORT          GPIOC
#define LCD_BCKL_PORT       GPIOB
#define LCD_RW_PORT         GPIOC


#define LCD_D7_PORT_CLK_EN      RCC_IOPENR_GPIOAEN
#define LCD_D6_PORT_CLK_EN      RCC_IOPENR_GPIOBEN
#define LCD_D5_PORT_CLK_EN      RCC_IOPENR_GPIOBEN
#define LCD_D4_PORT_CLK_EN      RCC_IOPENR_GPIOBEN
#define LCD_RS_PORT_CLK_EN      RCC_IOPENR_GPIOAEN
#define LCD_E_PORT_CLK_EN       RCC_IOPENR_GPIOCEN
#define LCD_BCKL_PORT_CLK_EN    RCC_IOPENR_GPIOBEN
#define LCD_RW_PORT_CLK_EN      RCC_IOPENR_GPIOCEN

#define LCD_D7_OUT_PIN      GPIO_ODR_OD8
#define LCD_D6_OUT_PIN      GPIO_ODR_OD14
#define LCD_D5_OUT_PIN      GPIO_ODR_OD4
#define LCD_D4_OUT_PIN      GPIO_ODR_OD5
#define LCD_RS_OUT_PIN      GPIO_ODR_OD9
#define LCD_E_OUT_PIN       GPIO_ODR_OD7
#define LCD_BCKL_OUT_PIN    GPIO_ODR_OD0
#define LCD_RW_OUT_PIN      GPIO_ODR_OD7

#define LCD_D7_IN_PIN       GPIO_IDR_ID8
#define LCD_D6_IN_PIN       GPIO_IDR_ID14
#define LCD_D5_IN_PIN       GPIO_IDR_ID4
#define LCD_D4_IN_PIN       GPIO_IDR_ID5

#define MODER_LCD_D7_0      GPIO_MODER_MODE8_0
#define MODER_LCD_D7_Msk    GPIO_MODER_MODE8_Msk
#define MODER_LCD_D6_0      GPIO_MODER_MODE14_0
#define MODER_LCD_D6_Msk    GPIO_MODER_MODE14_Msk
#define MODER_LCD_D5_0      GPIO_MODER_MODE4_0
#define MODER_LCD_D5_Msk    GPIO_MODER_MODE4_Msk
#define MODER_LCD_D4_0      GPIO_MODER_MODE5_0
#define MODER_LCD_D4_Msk    GPIO_MODER_MODE5_Msk
#define MODER_LCD_RS_0      GPIO_MODER_MODE9_0
#define MODER_LCD_RS_Msk    GPIO_MODER_MODE9_Msk
#define MODER_LCD_E_0       GPIO_MODER_MODE7_0
#define MODER_LCD_E_Msk     GPIO_MODER_MODE7_Msk
#define MODER_LCD_BCKL_0    GPIO_MODER_MODE0_0
#define MODER_LCD_BCKL_Msk  GPIO_MODER_MODE0_Msk
#define MODER_LCD_RW_0      GPIO_MODER_MODE7_0
#define MODER_LCD_RW_Msk    GPIO_MODER_MODE7_Msk


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
    RCC -> IOPENR |= LCD_D7_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D6_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D5_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D4_PORT_CLK_EN;
    
    set_LCD_DATA_PINS_as_outputs();
    init_LCD_SIGNAL_PINS_as_outputs();
    init_LCD_BCKL_PIN_as_output();
    //disable LCD backlight on init
    LCD_BCKL_PORT->ODR &= ~LCD_BCKL_OUT_PIN;

}

static void set_LCD_DATA_PINS_as_outputs(void)
{
    LCD_D7_PORT->MODER &=(~MODER_LCD_D7_Msk);
    LCD_D7_PORT->MODER |= MODER_LCD_D7_0;

    LCD_D6_PORT->MODER &=(~MODER_LCD_D6_Msk);
    LCD_D6_PORT->MODER |= MODER_LCD_D6_0;

    LCD_D5_PORT->MODER &=(~MODER_LCD_D5_Msk);
    LCD_D5_PORT->MODER |= MODER_LCD_D5_0;

    LCD_D4_PORT->MODER &=(~MODER_LCD_D4_Msk);
    LCD_D4_PORT->MODER |= MODER_LCD_D4_0;

}
static void set_LCD_DATA_PINS_as_inputs(void)
{
    LCD_D7_PORT->MODER &=(~MODER_LCD_D7_Msk);

    LCD_D6_PORT->MODER &=(~MODER_LCD_D6_Msk);

    LCD_D5_PORT->MODER &=(~MODER_LCD_D5_Msk);

    LCD_D4_PORT->MODER &=(~MODER_LCD_D4_Msk);
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    if ((data & LCD_D4_MASK))
        LCD_D4_PORT->ODR |= LCD_D4_OUT_PIN;
    else
        LCD_D4_PORT->ODR &= ~LCD_D4_OUT_PIN;

    if ((data & LCD_D5_MASK))
        LCD_D5_PORT->ODR |= LCD_D5_OUT_PIN;
    else
        LCD_D5_PORT->ODR &= ~LCD_D5_OUT_PIN;

    if ((data & LCD_D6_MASK))
        LCD_D6_PORT->ODR |= LCD_D6_OUT_PIN;
    else
        LCD_D6_PORT->ODR &= ~LCD_D6_OUT_PIN;

    if ((data & LCD_D7_MASK))
        LCD_D7_PORT->ODR |= LCD_D7_OUT_PIN;
    else
        LCD_D7_PORT->ODR &= ~LCD_D7_OUT_PIN;
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    uint8_t data = 0;
    if (((LCD_D4_PORT->IDR) & LCD_D4_IN_PIN) == LCD_D4_IN_PIN)
        data = LCD_D4_MASK;
    if (((LCD_D5_PORT->IDR) & LCD_D5_IN_PIN) == LCD_D5_IN_PIN)
        data |= LCD_D5_MASK;
    if (((LCD_D6_PORT->IDR) & LCD_D6_IN_PIN) == LCD_D6_IN_PIN)
        data |= LCD_D6_MASK;
    if (((LCD_D7_PORT->IDR) & LCD_D7_IN_PIN) == LCD_D7_IN_PIN)
        data |= LCD_D7_MASK;
    return data;
}

static void set_LCD_E(void)
{
    LCD_E_PORT->ODR |= LCD_E_OUT_PIN;
}
static void reset_LCD_E(void)
{
    LCD_E_PORT->ODR &= ~LCD_E_OUT_PIN;
}
static void set_LCD_RS(void)
{
    LCD_RS_PORT->ODR |= LCD_RS_OUT_PIN;
}
static void reset_LCD_RS(void)
{
    LCD_RS_PORT->ODR &= ~LCD_RS_OUT_PIN;
}
static void set_LCD_RW(void)
{
    LCD_RW_PORT->ODR |= LCD_RW_OUT_PIN;
}
static void reset_LCD_RW(void)
{
    LCD_RW_PORT->ODR &= ~LCD_RW_OUT_PIN;
}
static void set_LCD_BCKL(void)
{
    LCD_BCKL_PORT->ODR |= LCD_BCKL_OUT_PIN;
}
static void reset_LCD_BCKL(void)
{
    LCD_BCKL_PORT->ODR &= ~LCD_BCKL_OUT_PIN;
}

static void init_LCD_SIGNAL_PINS_as_outputs(void)
{
    RCC -> IOPENR |= LCD_RS_PORT_CLK_EN;
    LCD_RS_PORT->MODER &=(~MODER_LCD_RS_Msk);
    LCD_RS_PORT->MODER |= MODER_LCD_RS_0;

    RCC -> IOPENR |= LCD_E_PORT_CLK_EN;
    LCD_E_PORT->MODER &=(~MODER_LCD_E_Msk);
    LCD_E_PORT->MODER |= MODER_LCD_E_0;

#if USE_RW_PIN == 1
    RCC -> IOPENR |= LCD_RW_PORT_CLK_EN;
    LCD_RW_PORT->MODER &=(~MODER_LCD_RW_Msk);
    LCD_RW_PORT->MODER |= MODER_LCD_RW_0;
#endif
}

static void init_LCD_BCKL_PIN_as_output(void)
{
    RCC -> IOPENR |= LCD_BCKL_PORT_CLK_EN;
    LCD_BCKL_PORT->MODER &=(~MODER_LCD_BCKL_Msk);
    LCD_BCKL_PORT->MODER |= MODER_LCD_BCKL_0;
}
