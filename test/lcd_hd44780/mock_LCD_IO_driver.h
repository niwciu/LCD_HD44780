/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-06 22:11:42
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-02-23 18:46:38
 */
#include "lcd_hd44780_driver_commands.h"
#include <stdint.h>

// clang-format off
#define BUF_SIZE            2000
#define LOG_DATA_AMOUNT     3

#define mock_LCD_D4         1 << 0
#define mock_LCD_D5         1 << 1
#define mock_LCD_D6         1 << 2
#define mock_LCD_D7         1 << 3

#define mock_LCD_E          1 << 2
#define mock_LCD_RS         1 << 0
#define mock_LCD_RW         1 << 1
#define mock_LCD_BCKL       1 << 3 

// clang-format on

enum lcd_bckl_status
{
    LCD_BCKL_ON,
    LCD_BCKL_OFF
};

extern uint8_t mock_LCD_DATA_PORT;
extern uint8_t mock_LCD_SIG_PORT;
extern uint8_t mock_LCD_DATA_PORT_DIRECTION;
extern uint8_t mock_LCD_SIG_PORT_DIRECTION;

extern uint16_t mock_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];

uint8_t mock_get_lcd_init_state(void);
void mock_clear_LCD_Port_delay_dump_data(void);
enum lcd_bckl_status mock_read_LCD_backlight_status(void);
