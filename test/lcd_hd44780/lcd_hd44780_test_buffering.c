/*
 * @Author: lukasz.niewelt
 * @Date: 2024-01-08 15:45:14
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-10 18:06:19
 */

#include "unity/fixture/unity_fixture.h"
// #include "lcd_hd44780_config.h"
#include "lcd_hd44780.h"
#include "lcd_hd44780_test_common.h"
#include <string.h>

#if LCD_BUFFERING == ON

#define LAST_CHAR_IN_LCD_LINE_POSITION (LCD_X - 1)
#define LAST_LCD_LINE (LCD_Y - 1)

extern char lcd_buffer[LCD_Y][LCD_X];
extern char prev_lcd_buffer[LCD_Y][LCD_X];
char expected_lcd_buf[LCD_Y][LCD_X];

static void define_expected_buffer_value_for_cls(void);
static log_no_t define_expected_sequence_for_move_to_last_character_from_first_line_whne_nothing_to_print_on_lcd(log_no_t start_log_no);
static log_no_t define_expected_sequence_for_lcd_locate_0_0(log_no_t start_log_no);

TEST_GROUP(lcd_hd44780_buffering);

TEST_SETUP(lcd_hd44780_buffering)
{
    /* Init before every test */
    lcd_init();
    clear_expected_LCD_Port_delay_dump_data();
    mock_clear_LCD_Port_delay_dump_data();
    next_log_no = 0;
    expected_buf_lenght = 0;
}

TEST_TEAR_DOWN(lcd_hd44780_buffering)
{
    /* Cleanup after every test */
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdInitThenLcdBufferContainSpaces)
{
    define_expected_buffer_value_for_cls();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdBufCharThenBufferEqualToExpected)
{
    lcd_buf_char('a');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = 'a';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdBufCharAandLcdBufCharBUsedThenBufferEqualToExpected)
{
    lcd_buf_char('A');
    lcd_buf_char('B');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = 'A';
    expected_lcd_buf[LINE_1][C2] = 'B';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufLocateFirstLineLastLetterAndLcdBufCharAThenBufferEqualToExpected)
{
    lcd_buf_locate(LINE_1, LAST_CHAR_IN_LCD_LINE_POSITION);
    lcd_buf_char('A');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][LAST_CHAR_IN_LCD_LINE_POSITION] = 'A';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufLocateFirstLineLastLetterAndLcdBufCharAandLcdBufCharBThenBufferEqualToExpected)
{
    lcd_buf_locate(LINE_1, LAST_CHAR_IN_LCD_LINE_POSITION);
    lcd_buf_char('A');
    lcd_buf_char('B');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][LAST_CHAR_IN_LCD_LINE_POSITION] = 'A';
    expected_lcd_buf[LINE_2][C1] = 'B';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufLocateLastLineLastLetterAndLcdBufCharAandLcdBufCharBThenBufferEqualToExpected)
{
    lcd_buf_locate(LAST_LCD_LINE, LAST_CHAR_IN_LCD_LINE_POSITION);
    lcd_buf_char('A');
    lcd_buf_char('B');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE_POSITION] = 'A';
    expected_lcd_buf[LINE_1][C1] = 'B';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufStrTestThenLcdBufferEqualToExpectedLcdBuffer)
{
    lcd_buf_str("Test");
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = 'T';
    expected_lcd_buf[LINE_1][C2] = 'e';
    expected_lcd_buf[LINE_1][C3] = 's';
    expected_lcd_buf[LINE_1][C4] = 't';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndSetLcdLocateLastLineLastCharacterWhenLcdBufStrTestThenLcdBufferEqualToExpectedLcdBuffer)
{
    lcd_buf_locate(LAST_LCD_LINE, LAST_CHAR_IN_LCD_LINE_POSITION);
    lcd_buf_str("Test");
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE_POSITION] = 'T';
    expected_lcd_buf[LINE_1][C1] = 'e';
    expected_lcd_buf[LINE_1][C2] = 's';
    expected_lcd_buf[LINE_1][C3] = 't';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdInitThenLCD_UPDATE_EVENTflagIsFALSE)
{
    TEST_ASSERT_FALSE(LCD_UPDATE_EVENT);
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndLCD_UPDATE_EVENTflagIsTRUEWhenLcdInitThenLCD_UPDATE_EVENTflagIsFalse)
{
    LCD_UPDATE_EVENT = true;
    lcd_init();
    TEST_ASSERT_FALSE(LCD_UPDATE_EVENT);
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufCharThenLCD_UPDATE_EVENTflagIsTRUE)
{
    lcd_buf_char('a');
    TEST_ASSERT_TRUE(LCD_UPDATE_EVENT);
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufStrThenLCD_UPDATE_EVENTflagIsTRUE)
{
    lcd_buf_str("TEST");
    TEST_ASSERT_TRUE(LCD_UPDATE_EVENT);
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufClsThenLCD_UPDATE_EVENTflagIsTRUE)
{ 
    lcd_buf_cls();
    TEST_ASSERT_TRUE(LCD_UPDATE_EVENT);
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndLCD_UPDATE_EVENTflagIsTRUEWhenLcdUpdateThenLCD_UPDATE_EVENTflagIsFALSE)
{
    LCD_UPDATE_EVENT = true;
    lcd_update();
    TEST_ASSERT_FALSE(LCD_UPDATE_EVENT);
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdInitThenLcdCurrentScreenBufferContainSpaces)
{
    define_expected_buffer_value_for_cls();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, prev_lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndLcdBufStrWhenLcdUpdateThenLcdCurrentScreenBufferIsEqualToLcdBuffer)
{
    lcd_buf_str("TEST");
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(lcd_buffer, prev_lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufStrThenLcdCurrentScreenBufferStillContainSpaces)
{
    define_expected_buffer_value_for_cls();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, prev_lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndSetLcdLocateLastLineLastCharacterAndLcdBufStrTestWhenUpdateLcdScrThenSignalSequenceForUpdateLcdScrIsCorrect)
{
    // write "est" on LCD
    next_log_no = define_expected_sequence_for_send_string_to_LCD("est", 0);
    // move cursor to lasr line last character
    next_log_no = define_expected_sequence_for_move_to_last_character_from_first_line_whne_nothing_to_print_on_lcd(next_log_no);
    // wirte "T" on LCD
    next_log_no = define_expected_sequence_for_send_string_to_LCD("T", next_log_no);
    // move cursor to begining of LCD (0,0)
    next_log_no = define_expected_sequence_for_lcd_locate_0_0(next_log_no);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_buf_locate(LAST_LCD_LINE, LAST_CHAR_IN_LCD_LINE_POSITION);
    lcd_buf_str("Test");
    lcd_update();
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

#if USE_LCD_BUF_INT == ON
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_LcdInt_24_2_right_ThenLcdBufferContainInt24AsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = '2';
    expected_lcd_buf[LINE_1][C2] = '4';
    lcd_buf_int(24,2,right);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_LcdInt_2444_2_right_ThenLcdBufferContainInt2444AsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = '2';
    expected_lcd_buf[LINE_1][C2] = '4';
    expected_lcd_buf[LINE_1][C3] = '4';
    expected_lcd_buf[LINE_1][C4] = '4';
    lcd_buf_int(2444,2,right);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_LcdInt_16_4_right_ThenLcdBufferContainInt__16AsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = ' ';
    expected_lcd_buf[LINE_1][C2] = ' ';
    expected_lcd_buf[LINE_1][C3] = '1';
    expected_lcd_buf[LINE_1][C4] = '6';
    lcd_buf_str("1234");
    lcd_buf_locate(LINE_1,C1);
    lcd_buf_int(16,4,right);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_LcdInt_61045_8_left_ThenLcdBufferContainInt61045___AsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = '6';
    expected_lcd_buf[LINE_1][C2] = '1';
    expected_lcd_buf[LINE_1][C3] = '0';
    expected_lcd_buf[LINE_1][C4] = '4';
    expected_lcd_buf[LINE_1][C5] = '5';
    expected_lcd_buf[LINE_1][C6] = ' ';
    expected_lcd_buf[LINE_1][C7] = ' ';
    expected_lcd_buf[LINE_1][C8] = ' ';
    lcd_buf_str("99999999");
    lcd_buf_locate(LINE_1,C1);
    lcd_buf_int(61045,8,left);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}
#endif
#if USE_LCD_BUF_HEX== ON
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_lcd_hex_10_1_left_ThenLcdBufferContain0xaAsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = '0';
    expected_lcd_buf[LINE_1][C2] = 'x';
    expected_lcd_buf[LINE_1][C3] = 'a';
    lcd_buf_hex(10,1,left);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_lcd_hex_255_6_right_ThenLcdBufferContain__0xFFAsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = ' ';
    expected_lcd_buf[LINE_1][C2] = ' ';
    expected_lcd_buf[LINE_1][C3] = '0';
    expected_lcd_buf[LINE_1][C4] = 'x';
    expected_lcd_buf[LINE_1][C5] = 'f';
    expected_lcd_buf[LINE_1][C6] = 'f';
    lcd_buf_str("123456");
    lcd_buf_locate(LINE_1,C1);
    lcd_buf_hex(255,6,right);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_lcd_hex_20_5_right_ThenLcdBufferContainInt_0x14AsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = ' ';
    expected_lcd_buf[LINE_1][C2] = '0';
    expected_lcd_buf[LINE_1][C3] = 'x';
    expected_lcd_buf[LINE_1][C4] = '1';
    expected_lcd_buf[LINE_1][C5] = '4';
    lcd_buf_str("12345");
    lcd_buf_locate(LINE_1,C1);
    lcd_buf_hex(20,5,right);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_lcd_hex_20_1_right_ThenLcdBufferContainInt0x14AsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = '0';
    expected_lcd_buf[LINE_1][C2] = 'x';
    expected_lcd_buf[LINE_1][C3] = '1';
    expected_lcd_buf[LINE_1][C4] = '4';
    lcd_buf_str("1234");
    lcd_buf_locate(LINE_1,C1);
    lcd_buf_hex(20,1,right);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}
#endif
#if USE_LCD_BUF_BIN == ON
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_lcd_bin_5_6_ThenLcdBufferContainInt0b0101AsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = '0';
    expected_lcd_buf[LINE_1][C2] = 'b';
    expected_lcd_buf[LINE_1][C3] = '0';
    expected_lcd_buf[LINE_1][C4] = '1';
    expected_lcd_buf[LINE_1][C5] = '0';
    expected_lcd_buf[LINE_1][C6] = '1';
    lcd_buf_str("123456");
    lcd_buf_locate(LINE_1,C1);
    lcd_buf_bin(5,6);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenUse_lcd_bin_5_1_ThenLcdBufferContainInt0b101AsString)
{
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = '0';
    expected_lcd_buf[LINE_1][C2] = 'b';
    expected_lcd_buf[LINE_1][C3] = '1';
    expected_lcd_buf[LINE_1][C4] = '0';
    expected_lcd_buf[LINE_1][C5] = '1';
    lcd_buf_str("12345");
    lcd_buf_locate(LINE_1,C1);
    lcd_buf_bin(5,1);
    lcd_update();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}
#endif








// TEST(lcd_hd44780_buffering, )
// {
//     TEST_FAIL_MESSAGE("Added test")
// }

static void define_expected_buffer_value_for_cls(void)
{
    for (uint8_t line = 0; line < LCD_Y; line++)
    {
        for (uint8_t collumn = 0; collumn < LCD_X; collumn++)
        {
            expected_lcd_buf[line][collumn] = ' ';
        }
    }
}

static log_no_t define_expected_sequence_for_move_to_last_character_from_first_line_whne_nothing_to_print_on_lcd(log_no_t start_log_no)
{
#if ((LCD_TYPE == 2004) || (LCD_TYPE == 1604))

#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(start_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0x00);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE3_ADR + C1), 0x00);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE4_ADR + C1), 0x00);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE4_ADR + LAST_CHAR_IN_LCD_LINE_POSITION), 0x00);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(start_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE3_ADR + C1), 0);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE4_ADR + C1), 0);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE4_ADR + LAST_CHAR_IN_LCD_LINE_POSITION), 0);
#endif
#elif LCD_TYPE == 1602
#if USE_RW_PIN == ON
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(start_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0x00);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + LAST_CHAR_IN_LCD_LINE_POSITION), 0x00);
#else
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(start_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0);
    next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + LAST_CHAR_IN_LCD_LINE_POSITION), 0);
#endif
#else
    ptrintf("\r\n\r\n\t define_expected_sequence_for_move_to_last_character_from_first_line_whne_nothing_to_print_on_lcd -> go to this function and specify your expected signal sequence for your LCD_TYPE");
#endif
    return next_log_no;
}

log_no_t define_expected_sequence_for_lcd_locate_0_0(log_no_t start_log_no)
{
#if USE_RW_PIN == ON
    return define_expected_sequence_for_send_cmd_to_LCD(start_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE1_ADR + C1), 0x00);
#else
    return define_expected_sequence_for_send_cmd_to_LCD(start_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE1_ADR + C1), 0);
#endif
}
#endif