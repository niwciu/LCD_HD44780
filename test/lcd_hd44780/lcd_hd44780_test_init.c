#include "unity/fixture/unity_fixture.h"

#include "lcd_hd44780.h"
// #include "mock_LCD_IO_driver.h"
#include "lcd_hd44780_test_common.h"

TEST_GROUP(lcd_hd44780_init);

TEST_SETUP(lcd_hd44780_init)
{
    /* Init before every test */
}

TEST_TEAR_DOWN(lcd_hd44780_init)
{
    /* Cleanup after every test */
}
TEST(lcd_hd44780_init, WhenLcdInitThenLcdDataSignalBcklPinsInit)
{
    uint8_t expected_resoult = 0;
    lcd_init();
#if USE_RW_PIN == ON
    expected_resoult =
        ((mock_LCD_RW | mock_LCD_E | mock_LCD_RS) << 4) | (mock_LCD_D4 | mock_LCD_D5 | mock_LCD_D6 | mock_LCD_D7);
#else
    expected_resoult = ((mock_LCD_E | mock_LCD_RS) << 4) | (mock_LCD_D4 | mock_LCD_D5 | mock_LCD_D6 | mock_LCD_D7);
#endif
    TEST_ASSERT_EQUAL(expected_resoult, mock_get_lcd_init_state());
}
TEST(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsLowAtFirstLog)
{
    lcd_init();
    TEST_ASSERT_EQUAL(0x00, mock_LCD_Port_delay_dump_data[0][DATA_PORT]);
}

TEST(lcd_hd44780_init, GivenLcdInitWhenSetAllSignalsFor15msThenLcdPinStatIsCorrect)
{
    expected_buf_lenght = 0;

    mock_clear_LCD_Port_delay_dump_data();
    clear_expected_LCD_Port_delay_dump_data();
    lcd_init();

    next_log_no = define_expected_sequence_for_first_15_ms_delay();
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_init, GivenLcdInitWhenSendFirstCmd0x03ThenLcdPinStateSequenceIsCorrect)
{
    // set expected log sequence for sending cmd 0x03 at init
    next_log_no = define_expected_sequence_for_read_write_4_bit_data(next_log_no, 0x03, 4500);

    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_init, GivenLcdInitWhenSendSecondCmd0x03ThenLcdPinStateSequenceIsCorrect)
{
    // set expected log sequence for sending second cmd 0x03 at init of LCD
    next_log_no = define_expected_sequence_for_read_write_4_bit_data(next_log_no, 0x03, 110);

    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_init, GivenLcdInitWhenSendThirdCmd0x03ThenLcdPinStateSequenceIsCorrect)
{
    // set expected log sequence for sending third cmd 0x03 at init of LCD
    next_log_no = define_expected_sequence_for_read_write_4_bit_data(next_log_no, 0x03, 110);

    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_init, GivenLcdInitWhenSend4thCmd0x03ThenLcdPinStateSequenceIsCorrect)
{
    // set expected log sequence for sending 4'thcmd 0x02 at init of LCD
    next_log_no = define_expected_sequence_for_read_write_4_bit_data(next_log_no, 0x02, 110);

    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
TEST(lcd_hd44780_init, GivenLcdInitWhenSendFunctionSetCmdThenLcdPinStateSequenceIsCorrect)
{
    uint8_t cmd = (LCDC_FUNC | LCDC_FUNC4B | LCDC_FUNC2L | LCDC_FUNC5x7);
    // set expeted log sequence when sending cmd to LCD

#if USE_RW_PIN == ON
    uint8_t expected_data_from_LCD = 0;
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, cmd, expected_data_from_LCD);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, cmd, 0);
#endif
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_init, GivenLcdInitWhenSendDisplaySettingsCmdThenLcdPinStateSequenceIsCorrect)
{
    uint8_t cmd = (LCDC_ONOFF | LCDC_CURSOROFF | LCDC_DISPLAYON);

    // set expeted log sequence when sending cmd to LCD
#if USE_RW_PIN == ON
    uint8_t expected_data_from_LCD = 0;
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, cmd, expected_data_from_LCD);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, cmd, 0);
#endif
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_init, GivenLcdInitWhenSendDisplayClearScrCmdThenLcdPinStateSequenceIsCorrect)
{
    uint8_t cmd = (LCDC_CLS);
#if USE_RW_PIN == ON
    uint8_t expected_data_from_LCD = 0;
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, cmd, expected_data_from_LCD);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, cmd, 4900);
#endif

    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_init, GivenLcdInitWhenSendDisplayEntryModeCmdThenLcdPinStateSequenceIsCorrect)
{
    uint8_t cmd = (LCDC_ENTRY_MODE | LCDC_ENTRYR);
#if USE_RW_PIN == ON
    uint8_t expected_data_from_LCD = 0;
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, cmd, expected_data_from_LCD);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, cmd, 0);
#endif

    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
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
