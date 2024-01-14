/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-07 15:51:41
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:34:48
 */
#include <stdio.h>
#include "stm32g070xx.h"
#include "lcd_hd44780_interface.h"
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
#if USE_RW_PIN == ON
#define LCD_RW_PORT          GPIOC
#endif


#define LCD_D7_PORT_CLK_EN  RCC_IOPENR_GPIOAEN
#define LCD_D6_PORT_CLK_EN  RCC_IOPENR_GPIOBEN
#define LCD_D5_PORT_CLK_EN  RCC_IOPENR_GPIOBEN
#define LCD_D4_PORT_CLK_EN  RCC_IOPENR_GPIOBEN
#define LCD_RS_PORT_CLK_EN  RCC_IOPENR_GPIOAEN
#define LCD_E_PORT_CLK_EN  RCC_IOPENR_GPIOCEN
#if USE_RW_PIN == ON
#define LCD_RW_PORT_CLK_EN  RCC_IOPENR_GPIOCEN
#endif

#define LCD_D7_OUT_PIN      GPIO_ODR_OD8
#define LCD_D6_OUT_PIN      GPIO_ODR_OD14
#define LCD_D5_OUT_PIN      GPIO_ODR_OD4
#define LCD_D4_OUT_PIN      GPIO_ODR_OD5
#define LCD_RS_OUT_PIN      GPIO_ODR_OD9
#define LCD_E_OUT_PIN       GPIO_ODR_OD7
#if USE_RW_PIN == ON
#define LCD_E_OUT_PIN       GPIO_ODR_OD7
#endif

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
#define MODER_LCD_E_0      GPIO_MODER_MODE7_0
#define MODER_LCD_E_Msk    GPIO_MODER_MODE7_Msk
#if USE_RW_PIN == ON
#define MODER_LCD_RW_0      GPIO_MODER_MODE7_0
#define MODER_LCD_RW_Msk    GPIO_MODER_MODE7_Msk
#endif

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
static void init_LCD_SIGNAL_PINS_as_outputs(void);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_data_and_SIG_pins,
    set_LCD_DATA_PINS_as_outputs,
    set_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
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
    RCC -> IOPENR |= LCD_D7_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D6_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D5_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D4_PORT_CLK_EN;
    set_LCD_DATA_PINS_as_outputs();
    init_LCD_SIGNAL_PINS_as_outputs();
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

static void LCD_set_SIG(enum lcd_sig LCD_SIG)
{
    switch (LCD_SIG)
    {
    case LCD_RS:
        LCD_RS_PORT->ODR |= LCD_RS_OUT_PIN;
        break;
    case LCD_E:
        LCD_E_PORT->ODR |= LCD_E_OUT_PIN;
        break;
#if USE_RW_PIN == ON
    case LCD_RW:
        LCD_RW_PORT->ODR |= LCD_RW_OUT_PIN;
        break;
#endif
    default:
        break;
    }
}

static void LCD_reset_SIG(enum lcd_sig LCD_SIG)
{
    switch (LCD_SIG)
    {
    case LCD_RS:
        LCD_RS_PORT->ODR &= ~LCD_RS_OUT_PIN;
        break;
    case LCD_E:
        LCD_E_PORT->ODR &= ~LCD_E_OUT_PIN;
        break;
#if USE_RW_PIN == 1
    case LCD_RW:
        LCD_RW_PORT->ODR &= ~LCD_Rw_OUT_PIN;
        break;
#endif
    default:
        break;
    }
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
