/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-06 22:11:49
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-07 13:34:24
 */

#include "mock_LCD_IO_driver.h"
#include "lcd_hd44780_config.h"
#include "lcd_hd44780_interface.h"

uint8_t mock_LCD_DATA_PORT = 0;
uint8_t mock_LCD_SIG_PORT = 0;
uint8_t mock_LCD_DATA_PORT_DIRECTION = 0;
uint8_t mock_LCD_SIG_PORT_DIRECTION = 0;

uint16_t mock_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];
uint16_t dump_reg_pointer=0;

static void mock_init_LCD_PINS(void);
static void mock_set_LCD_DATA_PORT_as_outputs(void);
static void mock_set_LCD_DATA_PORT_as_inputs(void);
static void mock_set_LCD_DATA_PORT_state(uint8_t data);
static uint8_t mock_get_LCD_DATA_PORT_state(void);
static void mock_init_LCD_SIGNAL_PINS_as_outputs(void);
static void mock_LCD_set_SIG(enum lcd_sig LCD_SIG);
static void mock_LCD_reset_SIG(enum lcd_sig LCD_SIG);
static uint8_t mock_get_pinmask(enum lcd_sig *LCD_SIG);
static void mock_delay_us(uint32_t delay_us);
static void mock_dump_LCD_SIG_DATA_DELAY_state(uint32_t delay_us);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    mock_init_LCD_PINS,
    mock_set_LCD_DATA_PORT_as_outputs,
    mock_set_LCD_DATA_PORT_as_inputs,
    mock_set_LCD_DATA_PORT_state,
    mock_get_LCD_DATA_PORT_state,
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

static void mock_init_LCD_PINS(void)
{
    mock_LCD_DATA_PORT=0x00;
    mock_LCD_SIG_PORT=0x00;
    mock_init_LCD_SIGNAL_PINS_as_outputs();
    mock_set_LCD_DATA_PORT_as_outputs();
}

static void mock_set_LCD_DATA_PORT_as_outputs(void)
{
    mock_LCD_DATA_PORT_DIRECTION = mock_LCD_D4 | mock_LCD_D5 | mock_LCD_D6 | mock_LCD_D7;
}

static void mock_set_LCD_DATA_PORT_as_inputs(void)
{
    // mock_LCD_DATA_PORT_DIRECTION &= ~(mock_LCD_D4 | mock_LCD_D5 | mock_LCD_D6 | mock_LCD_D7);
}

static void mock_set_LCD_DATA_PORT_state(uint8_t data)
{
    mock_LCD_DATA_PORT=data;
    mock_dump_LCD_SIG_DATA_DELAY_state(0);
}

static uint8_t mock_get_LCD_DATA_PORT_state(void)
{
    mock_LCD_DATA_PORT=0x00;
    mock_dump_LCD_SIG_DATA_DELAY_state(0);
    return mock_LCD_DATA_PORT;
}

static void mock_init_LCD_SIGNAL_PINS_as_outputs(void)
{
#if USE_RW_PIN == ON
    mock_LCD_SIG_PORT_DIRECTION = mock_LCD_E | mock_LCD_RS | mock_LCD_RW;
    ;
#else
    mock_LCD_SIG_PORT_DIRECTION = mock_LCD_E | mock_LCD_RS;
#endif
}

static void mock_LCD_set_SIG(enum lcd_sig LCD_SIG)
{
    mock_LCD_SIG_PORT|=mock_get_pinmask(&LCD_SIG);
    mock_dump_LCD_SIG_DATA_DELAY_state(0);
}

static void mock_LCD_reset_SIG(enum lcd_sig LCD_SIG)
{
    mock_LCD_SIG_PORT&=~(mock_get_pinmask(&LCD_SIG));
    mock_dump_LCD_SIG_DATA_DELAY_state(0);
}
static uint8_t mock_get_pinmask(enum lcd_sig *LCD_SIG)
{
    uint8_t Pin_Mask=0;
    switch (*LCD_SIG)
    {
    case LCD_E:
        Pin_Mask=mock_LCD_E;
        break;
    case LCD_RW:
        Pin_Mask=mock_LCD_RW;
        break;
    case LCD_RS:
        Pin_Mask=mock_LCD_RS;
        break;
    default:
        break;
    }
   return Pin_Mask; 
}

static void mock_delay_us(uint32_t delay_us)
{
    mock_dump_LCD_SIG_DATA_DELAY_state(delay_us);
    while (delay_us--);
}

static void mock_dump_LCD_SIG_DATA_DELAY_state(uint32_t delay_us)
{
    mock_LCD_Port_delay_dump_data[dump_reg_pointer][0] = mock_LCD_SIG_PORT;
    mock_LCD_Port_delay_dump_data[dump_reg_pointer][1] = mock_LCD_DATA_PORT;
    mock_LCD_Port_delay_dump_data[dump_reg_pointer][2] = delay_us;
    if (++dump_reg_pointer > BUF_SIZE - 1)
        dump_reg_pointer = 0;
}

uint8_t mock_get_lcd_init_state(void)
{
    return (mock_LCD_SIG_PORT_DIRECTION << 4) | (mock_LCD_DATA_PORT_DIRECTION);
}
void mock_clear_LCD_Port_delay_dump_data(void)
{
    for(uint16_t i=0;i<BUF_SIZE;i++)
    {
        for(uint8_t j=0;j<LOG_DATA_AMOUNT;j++)
        {
            mock_LCD_Port_delay_dump_data[i][j]=0xFF;
        }
    }
    dump_reg_pointer=0;
}