/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-06 22:11:42 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-07 20:06:32
 */
#include <stdint.h>
#define BUF_SIZE 1000
#define LOG_DATA_AMOUNT 3

#define mock_LCD_D4 1 << 0
#define mock_LCD_D5 1 << 1
#define mock_LCD_D6 1 << 2
#define mock_LCD_D7 1 << 3
#define mock_LCD_E 1 << 2
#define mock_LCD_RS 1 << 0
#define mock_LCD_RW 1 << 1

// clang-format off
#define LCDC_CLS            0x01
#define LCDC_HOME           0x02
/********************************/
#define LCDC_ENTRY_MODE     0x04
    #define LCDC_ENTRYR     0x02
    #define LCDC_ENTRYL     0x00
    #define LCDC_MOVE       0x01
/********************************/
#define LCDC_ONOFF          0x08
    #define LCDC_DISPLAYON  0x04
    #define LCDC_CURSORON   0x02
    #define LCDC_CURSOROFF  0x00
    #define LCDC_BLINKON    0x01
/********************************/
#define LCDC_SHIFT          0x10
    #define LCDC_SHIFTDISP  0x08
    #define LCDC_SHIFTR     0x04
    #define LCDC_SHIFTL     0x00
/********************************/
#define LCDC_FUNC           0x20
    #define LCDC_FUNC8B     0x10
    #define LCDC_FUNC4B     0x00
    #define LCDC_FUNC2L     0x08
    #define LCDC_FUNC1L     0x00
    #define LCDC_FUNC5x10   0x04
    #define LCDC_FUNC5x7    0x00
/********************************/
#define LCDC_SET_CGRAM      0x40
#define LCDC_SET_DDRAM      0x80
// clang-format on

extern uint8_t mock_LCD_DATA_PORT;
extern uint8_t mock_LCD_SIG_PORT;
extern uint8_t mock_LCD_DATA_PORT_DIRECTION;
extern uint8_t mock_LCD_SIG_PORT_DIRECTION;

extern uint16_t mock_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];

uint8_t mock_get_lcd_init_state(void);
void mock_clear_LCD_Port_delay_dump_data(void);

