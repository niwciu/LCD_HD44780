#include "unity/fixture/unity_fixture.h"

#include "lcd_hd44780.h"
#include "mock_LCD_IO_driver.h"

TEST_GROUP(lcd_hd44780_init);

TEST_SETUP(lcd_hd44780_init)
{
    /* Init before every test */
    }

TEST_TEAR_DOWN(lcd_hd44780_init)
{
    /* Cleanup after every test */
}
TEST(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsInit)
{
    lcd_init();
    #if USE_RW_PIN == ON
    TEST_ASSERT_EQUAL(0x7F,mock_get_lcd_init_state());
    #else
    TEST_ASSERT_EQUAL(0x3F,mock_get_lcd_init_state());
    #endif
}

TEST(lcd_hd44780_init, GivenLcdIniAndPinsInitWhensetallSignalsFor15msThenLcdPinStatIsCorrect)
{
    //set_correct_signal_sequence_to_log
    TEST_FAIL_MESSAGE("Implement your test!");
}

// TEST(lcd_hd44780_init, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_init, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_init, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_init, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_init, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }