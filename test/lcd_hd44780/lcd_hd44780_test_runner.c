#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(lcd_hd44780_init)
{
    /* Test cases to run */
    RUN_TEST_CASE(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsInit);
    RUN_TEST_CASE(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsLowAtFirstLog);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSetAllSignalsFor15msThenLcdPinStatIsCorrect);

    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendFirstCmd0x03ThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendSecondCmd0x03ThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendThirdCmd0x03ThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSend4thCmd0x03ThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendFunctionSetCmdThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendDisplaySettingsCmdThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendDisplayClearScrCmdThenLcdPinStateSequenceIsCorrect)
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendDisplayEntryModeCmdThenLcdPinStateSequenceIsCorrect)
    // RUN_TEST_CASE(lcd_hd44780_init, )
    // RUN_TEST_CASE(lcd_hd44780_init, )
}

TEST_GROUP_RUNNER(lcd_hd44780_basic_functions)
{
    /* Test cases to run */
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenPrintGcharaterOnLcdThenSignalSequenceForSendingCharIsCorrect )
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdClearScreenThenSignalSequenceForLcdClearScreenIsCorrect)
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdDefCharPol_eCalledThenSignalSequenceForLcdDefCharIsCorrect)
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenDefineSepcialCharactersFromBank1ThenSignalSequenceIsCorrect)
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, )
}


