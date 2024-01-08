/*
 * @Author: lukasz.niewelt 
 * @Date: 2024-01-08 15:45:14 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-08 17:22:42
 */
#include "unity/fixture/unity_fixture.h"
// #include "lcd_hd44780_config.h"
#include "lcd_hd44780.h"

extern char lcd_buffer[LCD_Y][LCD_X];
char expected_lcd_buf[LCD_Y][LCD_X];

static void define_expected_buffer_value_for_cls(void)
{
    for(uint8_t line=0; line<LCD_Y; line++)
    {
        for(uint8_t collumn=0; collumn<LCD_X; collumn++)
        {
            expected_lcd_buf[line][collumn]=' ';
        }
    }
}

TEST_GROUP(lcd_hd44780_buffering);

TEST_SETUP(lcd_hd44780_buffering)
{
    /* Init before every test */
}

TEST_TEAR_DOWN(lcd_hd44780_buffering)
{
    /* Cleanup after every test */
}



TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdInitThenLcdBufferContainSpaces)
{
    lcd_init();
    define_expected_buffer_value_for_cls();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}

// TEST(lcd_hd44780_buffering, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }
// TEST(lcd_hd44780_buffering, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }
// TEST(lcd_hd44780_buffering, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }
// TEST(lcd_hd44780_buffering, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

