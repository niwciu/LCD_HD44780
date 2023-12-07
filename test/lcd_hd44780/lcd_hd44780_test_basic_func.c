#include "unity/fixture/unity_fixture.h"
#include "lcd_hd44780.h"
#include "lcd_hd44780_test_common.h"

// #include "tested_module.h"

TEST_GROUP(lcd_hd44780_basic_functions);

TEST_SETUP(lcd_hd44780_basic_functions)
{
    /* Init before every test */
    lcd_init();
    clear_expected_LCD_Port_delay_dump_data();
    mock_clear_LCD_Port_delay_dump_data();
}

TEST_TEAR_DOWN(lcd_hd44780_basic_functions)
{
    /* Cleanup after every test */
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenPrintGcharaterOnLcdThenSignalSequenceForSendingCharIsCorrect)
{
    uint8_t data = (uint8_t)('G');
    uint16_t expected_buf_lenght = 0;

    next_log_no = define_expected_sequence_for_send_data_to_LCD(0, data, 0x00, 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    lcd_char('G');

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdClearScreenThenSignalSequenceForLcdClearScreenIsCorrect)
{
    uint16_t cmd = (LCDC_CLS);
    uint16_t expected_buf_lenght = 0;

    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, cmd, 0x00, 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    lcd_cls();

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

// TEST(template, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(template, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(template, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(template, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(template, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(template, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(template, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }
