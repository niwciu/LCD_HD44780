/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-04 20:13:23
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 10:49:44
 */

#include "lcd_hd44780_GPIO_interface.h"
#include "lcd_hd44780_config.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA_PORT PORTD
#define LCD_DATA_PORT_DIR DDRD
#define LCD_DATA_INPUT PIND

#define LCD_SIG_PORT PORTB
#define LCD_SIG_PORT_DIR DDRB

#define LCD_BCKL_PORT PORTB
#define LCD_BCKL_PORT_DIR DDRB

#define LCD_PIN_D7 (1 << PIND7)
#define LCD_PIN_D6 (1 << PIND6)
#define LCD_PIN_D5 (1 << PIND5)
#define LCD_PIN_D4 (1 << PIND4)
#define LCD_PIN_RS (1 << PINB0)
#define LCD_PIN_RW (1 << PINC1)
#define LCD_PIN_E (1 << PINB1)
#define LCD_BCKL_PIN (1 << PINB2)

#define LCD_D4_MASK 0x01
#define LCD_D5_MASK 0x02
#define LCD_D6_MASK 0x04
#define LCD_D7_MASK 0x08

static void init_LCD_data_and_SIG_pins(void);
static void init_LCD_DATA_PINS_as_outputs(void);
static void init_LCD_DATA_PINS_as_inputs(void);
static void set_LCD_DATA_PINS_state(uint8_t data);
static uint8_t get_LCD_DATA_PINS_state(void);
static void wraper_delay_us(uint32_t delay_us);
static void set_LCD_E(void);
static void reset_LCD_E(void);
static void set_LCD_RS(void);
static void reset_LCD_RS(void);
static void set_LCD_RW(void);
static void reset_LCD_RW(void);
static void set_LCD_BCKL(void);
static void reset_LCD_BCKL(void);
static void init_LCD_SIGNAL_PINS_as_outputs(void);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_data_and_SIG_pins,
    init_LCD_DATA_PINS_as_outputs,
    init_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
    wraper_delay_us,
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
    // set BCKL PIN as output
    LCD_BCKL_PORT_DIR |= LCD_BCKL_PIN;
    // enable Backlight of the LCD
    LCD_BCKL_PORT &= ~LCD_BCKL_PIN;
    init_LCD_DATA_PINS_as_outputs();
    init_LCD_SIGNAL_PINS_as_outputs();
}
static void init_LCD_DATA_PINS_as_outputs(void)
{
    // set pins as output
    LCD_DATA_PORT_DIR |= (LCD_PIN_D4 | LCD_PIN_D5 | LCD_PIN_D6 | LCD_PIN_D7);
}
static void init_LCD_DATA_PINS_as_inputs(void)
{

    // set pins as inputs
    LCD_DATA_PORT_DIR &= ~(LCD_PIN_D4 | LCD_PIN_D5 | LCD_PIN_D6 | LCD_PIN_D7);
    // enable pull-up on input pins
    LCD_DATA_PORT |= (LCD_PIN_D4 | LCD_PIN_D5 | LCD_PIN_D6 | LCD_PIN_D7);
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    if ((data & LCD_D4_MASK))
        LCD_DATA_PORT |= LCD_PIN_D4;
    else
        LCD_DATA_PORT &= ~LCD_PIN_D4;

    if ((data & LCD_D5_MASK))
        LCD_DATA_PORT |= LCD_PIN_D5;
    else
        LCD_DATA_PORT &= ~LCD_PIN_D5;

    if ((data & LCD_D6_MASK))
        LCD_DATA_PORT |= LCD_PIN_D6;
    else
        LCD_DATA_PORT &= ~LCD_PIN_D6;

    if ((data & LCD_D7_MASK))
        LCD_DATA_PORT |= LCD_PIN_D7;
    else
        LCD_DATA_PORT &= ~LCD_PIN_D7;
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    uint8_t data = 0;
    if (LCD_DATA_INPUT & LCD_PIN_D4)
        data = LCD_D4_MASK;
    if (LCD_DATA_INPUT & LCD_PIN_D5)
        data |= LCD_D5_MASK;
    if (LCD_DATA_INPUT & LCD_PIN_D6)
        data |= LCD_D6_MASK;
    if (LCD_DATA_INPUT & LCD_PIN_D7)
        data |= LCD_D7_MASK;
    return data;
}

static void wraper_delay_us(uint32_t delay_us)
{
    _delay_us((double)(delay_us));
}

static void set_LCD_E(void)
{
    LCD_SIG_PORT |= LCD_PIN_E;
}
static void reset_LCD_E(void)
{
    LCD_SIG_PORT &= ~LCD_PIN_E;
}
static void set_LCD_RS(void)
{
    LCD_SIG_PORT |= LCD_PIN_RS;
}
static void reset_LCD_RS(void)
{
    LCD_SIG_PORT &= ~LCD_PIN_RS;
}
static void set_LCD_RW(void)
{
    LCD_SIG_PORT |= LCD_PIN_RW;
}
static void reset_LCD_RW(void)
{
    LCD_SIG_PORT &= ~LCD_PIN_RW;
}
static void set_LCD_BCKL(void)
{
    LCD_BCKL_PORT |= LCD_BCKL_PIN;
}
static void reset_LCD_BCKL(void)
{
    LCD_BCKL_PORT &= ~ LCD_BCKL_PIN;
}

static void init_LCD_SIGNAL_PINS_as_outputs(void)
{
#if USE_RW_PIN == ON
    LCD_SIG_PORT_DIR |= (LCD_PIN_RS | LCD_PIN_RW | LCD_PIN_E);

#else
    LCD_SIG_PORT_DIR |= (LCD_PIN_RS | LCD_PIN_E);
#endif
}

