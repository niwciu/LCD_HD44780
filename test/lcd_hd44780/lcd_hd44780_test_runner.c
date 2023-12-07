#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(lcd_hd44780_init)
{
    /* Test cases to run */
    RUN_TEST_CASE(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsInit);
    RUN_TEST_CASE(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsLowAtFirstLog);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSetAllSignalsFor15msThenLcdPinStatIsCorrect)
   
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendFirst0x03ThenLcdPinStateSequenceIsCorrect)
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendSecond0x03ThenLcdPinStateSequenceIsCorrect)
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
}
