/*
 * @Author: lukasz.niewelt 
 * @Date: 2024-01-08 15:45:14 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-08 16:00:56
 */
#include "unity/fixture/unity_fixture.h"


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
    TEST_FAIL_MESSAGE("Implement your test!");
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
