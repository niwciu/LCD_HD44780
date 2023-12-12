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
    next_log_no = 0;
    expected_buf_lenght = 0;
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
#if USE_DEF_CHAR_FUNCTION == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdDefCharPol_eCalledThenSignalSequenceForLcdDefCharIsCorrect)
{
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, pol_e, Pol_e);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_def_char(pol_e, Pol_e);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenDefineSepcialCharactersFromBank1ThenSignalSequenceIsCorrect)
{
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, pol_e, Pol_e);
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, pol_o, Pol_o);
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, pol_s, Pol_s);
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, pol_l, Pol_l);
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, pol_c, Pol_c);
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, pol_a, Pol_a);
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, pol_n, Pol_n);
    next_log_no = define_expect_sequence_for_lcd_def_char(next_log_no, zn_wody, Zn_wody);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_load_char_bank(&lcd_cgram_bank_1);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif
#if USE_LCD_CURSOR_HOME == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdHomeThenSignalSequenceIsCorrect)
{
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_CLS | LCDC_HOME), 0x00, 4900);
    lcd_home();
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif

#if USE_LCD_CURSOR_ON == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdCursorOnThenSignalSequenceIsCorrect)
{
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON | LCDC_CURSORON), 0x00, 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_cursor_on();
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif

#if USE_LCD_CURSOR_OFF == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdCursorOffThenSignalSequenceIsCorrect)
{
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON), 0x00, 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_cursor_off();
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif

#if USE_LCD_BLINKING_CURSOR_ON == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdBlinkingCursorOnThenSignalSequenceIsCorrect)
{
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON | LCDC_CURSORON | LCDC_BLINKON), 0x00, 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_blinking_cursor_on();
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdLocateThenSignalSequenceIsCorrect)
{
    uint8_t line_no_2_adr = 0x40;
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (uint8_t)(LCDC_SET_DDRAM + line_no_2_adr + C5), 0x00, 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_locate(LINE_2, C5);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdStrThenSignalSequenceIsCorrect)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("TEst");
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_str("TEst");
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdLocateAndSetAllLinesLocationThenSignalSequenceIsCorrect)
{
    uint8_t line_no_1_adr = 0x00;
    uint8_t line_no_2_adr = 0x40;
    #if LCD_TYPE==2004
    uint8_t line_no_3_adr = 0x14;
    uint8_t line_no_4_adr = 0x54;
    #elif LCD_TYTPE==1604
    uint8_t line_no_3_adr = 0x10;
    uint8_t line_no_4_adr = 0x50;
    #endif
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (uint8_t)(LCDC_SET_DDRAM + line_no_1_adr + C5), 0x00, 0);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + line_no_2_adr + C4), 0x00, 0);
    #if ((LCD_TYPE==2004)||(LCD_TYTPE==1604))
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + line_no_3_adr + C3), 0x00, 0);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + line_no_4_adr + C6), 0x00, 0);
    #endif
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_locate(LINE_1, C5);
    lcd_locate(LINE_2, C4);
    lcd_locate(LINE_3, C3);
    lcd_locate(LINE_4, C6);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_24_2_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString)
{   
    next_log_no = define_expected_sequence_for_send_string_to_LCD("24");
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_int(24,2,right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_16_4_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString)
{   
    next_log_no = define_expected_sequence_for_send_string_to_LCD("  16");
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_int(16,4,right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_61045_8_left_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString)
{   
    next_log_no = define_expected_sequence_for_send_string_to_LCD("61045   ");
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_int(61045,8,left);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}


TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_10_1_left_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("0xa");
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_hex(10,1,left);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_255_6_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("  0xff");
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_hex(255,6,right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_20_5_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("  0xff");
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_hex(20,5,right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}


// TEST(lcd_hd44780_basic_functions, )
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_basic_functions, )
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_basic_functions, )
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }
