#include "unity/fixture/unity_fixture.h"
#include "lcd_hd44780_config.h"

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
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendDisplayClearScrCmdThenLcdPinStateSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_init, GivenLcdInitWhenSendDisplayEntryModeCmdThenLcdPinStateSequenceIsCorrect);
    // RUN_TEST_CASE(lcd_hd44780_init, )
}

TEST_GROUP_RUNNER(lcd_hd44780_basic_functions)
{
    /* Test cases to run */
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenPrintGcharaterOnLcdThenSignalSequenceForSendingCharIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdClearScreenThenSignalSequenceForLcdClearScreenIsCorrect);
#if USE_DEF_CHAR_FUNCTION == ON
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdDefCharPol_eCalledThenSignalSequenceForLcdDefCharIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenDefineSepcialCharactersFromBank1ThenSignalSequenceIsCorrect);
#endif
#if USE_LCD_CURSOR_HOME == ON
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdHomeThenSignalSequenceIsCorrect);
#endif
#if USE_LCD_CURSOR_ON == ON
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdCursorOnThenSignalSequenceIsCorrect);
#endif
#if USE_LCD_CURSOR_OFF == ON
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdCursorOffThenSignalSequenceIsCorrect);
#endif
#if USE_LCD_BLINKING_CURSOR_ON == ON
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdBlinkingCursorOnThenSignalSequenceIsCorrect);
#endif
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdLocateThenSignalSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdStrThenSignalSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdLocateAndSetAllLinesLocationThenSignalSequenceIsCorrect);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_24_2_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_2444_2_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_16_4_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_61045_8_left_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_10_1_left_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_255_6_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_20_5_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_20_1_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_bin_5_6_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig);
    RUN_TEST_CASE(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_bin_5_1_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig);
    // RUN_TEST_CASE(lcd_hd44780_basic_functions, );
}

TEST_GROUP_RUNNER(lcd_hd44780_buffering)
{
    /* Test cases to run */

    RUN_TEST_CASE(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdInitThenLcdBufferContainSpaces);
    RUN_TEST_CASE(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdBufCharThenBufferEqualToExpected);
    RUN_TEST_CASE(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdBufCharAandLcdBufCharBUsedThenBufferEqualToExpected)
    // RUN_TEST_CASE(lcd_hd44780_buffering, )
    // RUN_TEST_CASE(lcd_hd44780_buffering, )
    // RUN_TEST_CASE(lcd_hd44780_buffering, )
    // RUN_TEST_CASE(lcd_hd44780_buffering, )
    // RUN_TEST_CASE(lcd_hd44780_buffering, )
    // RUN_TEST_CASE(lcd_hd44780_buffering, )
}