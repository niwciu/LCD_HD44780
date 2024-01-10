/*
 * @Author: lukasz.niewelt
 * @Date: 2024-01-08 15:45:14
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-10 14:25:47
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
char expected_lcd_buf[LCD_Y][LCD_X];

static void define_expected_buffer_value_for_cls(void);
// static log_no_t define_expected_sequence_for_lcd_update(log_no_t start_log_no);

TEST_GROUP(lcd_hd44780_buffering);

TEST_SETUP(lcd_hd44780_buffering)
{
    /* Init before every test */
}

TEST_TEAR_DOWN(lcd_hd44780_buffering)
{
    /* Cleanup after every test */
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdInitThenLcdBufferContainSpaces)
{
    lcd_init();
    define_expected_buffer_value_for_cls();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdBufCharThenBufferEqualToExpected)
{
    lcd_init();
    lcd_buf_char('a');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = 'a';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdBufCharAandLcdBufCharBUsedThenBufferEqualToExpected)
{
    lcd_init();
    lcd_buf_char('A');
    lcd_buf_char('B');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1] = 'A';
    expected_lcd_buf[LINE_1][C2] = 'B';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufLocateFirstLineLastLetterAndLcdBufCharAThenBufferEqualToExpected)
{
    lcd_init();
    lcd_buf_locate(LINE_1, LAST_CHAR_IN_LCD_LINE_POSITION);
    lcd_buf_char('A');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][LAST_CHAR_IN_LCD_LINE_POSITION] = 'A';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf, lcd_buffer, (LCD_X * LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufLocateFirstLineLastLetterAndLcdBufCharAandLcdBufCharBThenBufferEqualToExpected)
{
    lcd_init();
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
    lcd_init();
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
    lcd_init();
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
    lcd_init();
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
    lcd_init();
    TEST_ASSERT_FALSE(LCD_UPDATE_EVENT)
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndLCD_UPDATE_EVENTflagIsTRUEWhenLcdInitThenLCD_UPDATE_EVENTflagIsFalse)
{
    lcd_init();
    LCD_UPDATE_EVENT=true;
    lcd_init();
    TEST_ASSERT_FALSE(LCD_UPDATE_EVENT)
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufCharThenLCD_UPDATE_EVENTflagIsTRUE)
{
   TEST_FAIL_MESSAGE("New Test Added") ;
}

// TEST(lcd_hd44780_buffering, )
// {
//    TEST_FAIL_MESSAGE("New Test Added") ;
// }

// TEST(lcd_hd44780_buffering, )
// {
//    TEST_FAIL_MESSAGE("New Test Added") ;
// }

// TEST(lcd_hd44780_buffering, )
// {
//    TEST_FAIL_MESSAGE("New Test Added") ;
// }

// TEST(lcd_hd44780_buffering, )
// {
//    TEST_FAIL_MESSAGE("New Test Added") ;
// }

// TEST(lcd_hd44780_buffering, )
// {
//    TEST_FAIL_MESSAGE("New Test Added") ;
// }

// TEST(lcd_hd44780_buffering, )
// {
//    TEST_FAIL_MESSAGE("New Test Added") ;
// }

// TEST(lcd_hd44780_buffering, )
// {
//    TEST_FAIL_MESSAGE("New Test Added") ;
// }
// TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndSetLcdLocateLastLineLastCharacterAndLcdBufStrTestWhenUpdateLcdScrThenSignalSequenceForUpdateLcdScrIsCorrect)
// {
//     lcd_init();
//     lcd_buf_locate(LAST_LCD_LINE, LAST_CHAR_IN_LCD_LINE_POSITION);
//     lcd_buf_str("Test");

//     define_expected_buffer_value_for_cls();

//     expected_lcd_buf[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE_POSITION] = 'T';
//     expected_lcd_buf[LINE_1][C1] = 'e';
//     expected_lcd_buf[LINE_1][C2] = 's';
//     expected_lcd_buf[LINE_1][C3] = 't';

//     clear_expected_LCD_Port_delay_dump_data();
//     mock_clear_LCD_Port_delay_dump_data();
//     next_log_no = 0;

//     next_log_no = define_expected_sequence_for_lcd_update(next_log_no);

//     expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
//     lcd_update();
//     TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
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

// static log_no_t define_expected_sequence_for_lcd_update(log_no_t start_log_no)
// {
//     char lcd_line[LCD_X + 1];
// #if ((LCD_TYPE == 2004) || (LCD_TYPE == 1604))
//     lcd_line[C1] = '\0';
//     strncpy(lcd_line, &expected_lcd_buf[LINE_1][C1], LCD_X);
//     lcd_line[LCD_X] = '\0';
//     next_log_no = define_expected_sequence_for_send_string_to_LCD(&lcd_line[0], start_log_no);
// #if USE_RW_PIN == ON
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0x00);
// #else
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0);
// #endif

//     lcd_line[C1] = '\0';
//     strncpy(lcd_line, &expected_lcd_buf[LINE_2][C1], LCD_X);
//     lcd_line[LCD_X] = '\0';
//     next_log_no = define_expected_sequence_for_send_string_to_LCD(&lcd_line[0], next_log_no);
// #if USE_RW_PIN == ON
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE3_ADR + C1), 0x00);
// #else
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE3_ADR + C1), 0);
// #endif

//     lcd_line[C1] = '\0';
//     strncpy(lcd_line, &expected_lcd_buf[LINE_3][C1], LCD_X);
//     lcd_line[LCD_X] = '\0';
//     next_log_no = define_expected_sequence_for_send_string_to_LCD(&lcd_line[0], next_log_no);
// #if USE_RW_PIN == ON
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE4_ADR + C1), 0x00);
// #else
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE4_ADR + C1), 0);
// #endif

//     lcd_line[C1] = '\0';
//     strncpy(lcd_line, &expected_lcd_buf[LINE_4][C1], LCD_X);
//     lcd_line[LCD_X] = '\0';
//     next_log_no = define_expected_sequence_for_send_string_to_LCD(&lcd_line[0], next_log_no);
// #if USE_RW_PIN == ON
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE1_ADR + C1), 0x00);
// #else
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE1_ADR + C1), 0);
// #endif
// #else // LCD_TYPE==1602
//     lcd_line[C1] = '\0';
//     strncat(lcd_line, &expected_lcd_buf[LINE_1][C1], LCD_X);
//     lcd_line[LCD_X] = '\0';
//     next_log_no = define_expected_sequence_for_send_string_to_LCD(&lcd_line[0], start_log_no);
// #if USE_RW_PIN == ON
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0x00);
// #else
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0);
// #endif

//     lcd_line[C1] = '\0';
//     strncat(lcd_line, &expected_lcd_buf[LINE_2][C1], LCD_X);
//     lcd_line[LCD_X] = '\0';
//     next_log_no = define_expected_sequence_for_send_string_to_LCD(&lcd_line[0], next_log_no);
// #if USE_RW_PIN == ON
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE2_ADR + C1), 0x00);
// #else
//     next_log_no = define_expected_sequence_for_send_cmd_to_LCD(next_log_no, (uint8_t)(LCDC_SET_DDRAM + LCD_LINE1_ADR + C1), 0);
// #endif

// #endif
//     return next_log_no;
// }

#endif