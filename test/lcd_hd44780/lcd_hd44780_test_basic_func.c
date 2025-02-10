/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-03 16:59:56
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-10 17:30:47
 */
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
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_data_to_LCD(0, data, 0x00, 0);
#else
    next_log_no = define_expected_sequence_for_send_data_to_LCD(0, data, 0);
#endif
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);

    lcd_char('G');

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenLcdClearScreenThenSignalSequenceForLcdClearScreenIsCorrect)
{
    uint8_t cmd = (LCDC_CLS);
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, cmd, 0x00);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, cmd, 4900);
#endif

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
    lcd_load_char_bank(&lcd_cgram_bank_1,lcd_bank_1_special_chars_map);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif
#if USE_LCD_CURSOR_HOME == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdHomeThenSignalSequenceIsCorrect)
{
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_CLS | LCDC_HOME), 0x00);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_CLS | LCDC_HOME), 4900);
#endif
    lcd_home();
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif

#if USE_LCD_CURSOR_ON == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdCursorOnThenSignalSequenceIsCorrect)
{
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON | LCDC_CURSORON), 0x00);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON | LCDC_CURSORON), 0);
#endif
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_cursor_on();
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif

#if USE_LCD_CURSOR_OFF == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdCursorOffThenSignalSequenceIsCorrect)
{
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON), 0x00);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON), 0);
#endif
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_cursor_off();
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif

#if USE_LCD_BLINKING_CURSOR_ON == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdBlinkingCursorOnThenSignalSequenceIsCorrect)
{
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON | LCDC_CURSORON | LCDC_BLINKON), 0x00);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (LCDC_ONOFF | LCDC_DISPLAYON | LCDC_CURSORON | LCDC_BLINKON), 0);
#endif
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_blinking_cursor_on();
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdLocateThenSignalSequenceIsCorrect)
{
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C5), 0x00);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C5), 0);
#endif

    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_locate(LINE_2, C5);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdStrThenSignalSequenceIsCorrect)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("TEst", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_str("TEst");
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUseLcdLocateAndSetAllLinesLocationThenSignalSequenceIsCorrect)
{
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE1_ADR + C5), 0x00);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C4), 0x00);
#if ((LCD_TYPE == 2004) || (LCD_TYTPE == 1604))
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE3_ADR + C3), 0x00);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE4_ADR + C6), 0x00);
#endif
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(0, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE1_ADR + C5), 0);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C4), 0);
#if ((LCD_TYPE == 2004) || (LCD_TYTPE == 1604))
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE3_ADR + C3), 0);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE4_ADR + C6), 0);
#endif
#endif

    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_locate(LINE_1, C5);
    lcd_locate(LINE_2, C4);
#if ((LCD_TYPE == 1604) || (LCD_TYPE == 2004))
    lcd_locate(LINE_3, C3);
    lcd_locate(LINE_4, C6);
#endif
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#if USE_LCD_INT == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_24_2_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("24", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_int(24, 2, right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_2444_2_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("2444", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_int(2444, 2, right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_16_4_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("  16", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_int(16, 4, right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_LcdInt_61045_8_left_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueAsString)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("61045   ", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_int(61045, 8, left);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif
#if USE_LCD_HEX == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_10_1_left_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("0xa", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_hex(10, 1, left);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_255_6_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("  0xff", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_hex(255, 6, right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_20_5_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD(" 0x14", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_hex(20, 5, right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_hex_20_1_right_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("0x14", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_hex(20, 1, right);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif
#if USE_LCD_BIN == ON
TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_bin_5_6_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("0b0101", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_bin(5, 6);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitWhenUse_lcd_bin_5_1_ThenSignalSequenceForSendigIsEqualToLcdStrWithValueInHexAsStrig)
{
    next_log_no = define_expected_sequence_for_send_string_to_LCD("0b101", 0);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_bin(5, 1);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}
#endif
TEST(lcd_hd44780_basic_functions, GivenLCDInitWhenUseEnableLcdBackLighThenBacklightPinIsEnabled)
{
    lcd_enable_backlight();
    TEST_ASSERT_EQUAL(LCD_BCKL_ON, mock_read_LCD_backlight_status());
}

TEST(lcd_hd44780_basic_functions, GivenLcdInitAndBacklightPinIsHighWhenLcdBacklightOffThenBacklightPinIsDisabled)
{
    lcd_enable_backlight();
    lcd_disable_backlight();
    TEST_ASSERT_EQUAL(LCD_BCKL_OFF, mock_read_LCD_backlight_status());
}

// TEST(lcd_hd44780_basic_functions, )
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }
