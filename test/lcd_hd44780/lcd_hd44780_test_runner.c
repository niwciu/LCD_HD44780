#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(lcd_hd44780_init)
{
    /* Test cases to run */
    RUN_TEST_CASE(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsInit);
    RUN_TEST_CASE(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsLowAtFirstLog);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSetAllSignalsFor15msThenLcdPinStatIsCorrect);
   
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendFirstCmd0x03ThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendSecondCmd0x03ThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendThirdCmd0x03ThenLcdPinStateSequenceIsCorrect );
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSend4thCmd0x03ThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init,GivenLcdInitWhenSendFunctionSetCmdThenLcdPinStateSequenceIsCorrect);
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
}
