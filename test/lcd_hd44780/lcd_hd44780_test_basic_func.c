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
    next_log_no=0;
    expected_buf_lenght=0;
}

TEST_TEAR_DOWN(lcd_hd44780_basic_functions)
{
    /* Cleanup after every test */
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenPrintGcharaterOnLcdThenSignalSequenceForSendingCharIsCorrect)
{
    uint8_t data = (uint8_t)('G');

    next_log_no = define_expected_sequence_for_send_data_to_LCD(0, data, 0x00, 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    lcd_char('G');

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdClearScreenThenSignalSequenceForLcdClearScreenIsCorrect)
{
    uint8_t cmd = (LCDC_CLS);

    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, cmd, 0x00, 4900);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    lcd_cls();

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdDefCharCalledThenSignalSequenceForLcdDefCharIsCorrect )
{
    static const uint8_t Pol_e[8] = {32, 32, 14, 17, 31, 16, 14, 3};
    uint8_t CGRAM_start_adress=((0x07 & 0) * 8);
    uint8_t cmd=(LCDC_SET_CGRAM |CGRAM_start_adress);
    next_log_no=define_expected_sequence_for_send_cmd_to_LCD(next_log_no,cmd,0x00, 0);
    for (uint8_t j = 0; j < 8; j++)
    {
        //lcd_write_data(Pol_e[j]);
        next_log_no=define_expected_sequence_for_send_data_to_LCD(next_log_no,Pol_e[j],0x00, 0);
    }
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no,LCDC_SET_DDRAM,0x00, 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    lcd_def_char(0,Pol_e);

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

// TEST(lcd_hd44780_basic_functions, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_basic_functions, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_basic_functions, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_basic_functions, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_basic_functions, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_basic_functions, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }
