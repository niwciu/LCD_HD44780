/*
 * @Author: lukasz.niewelt 
 * @Date: 2024-01-08 15:45:14 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-08 20:42:57
 */
#include "unity/fixture/unity_fixture.h"
// #include "lcd_hd44780_config.h"
#include "lcd_hd44780.h"
#include "lcd_hd44780_test_common.h"

#define LAST_CHAR_IN_LCD_LINE   (LCD_X-1)
#define LAST_LCD_LINE   (LCD_Y-1)

extern char lcd_buffer[LCD_Y][LCD_X];
char expected_lcd_buf[LCD_Y][LCD_X];

static void define_expected_buffer_value_for_cls(void)
{
    for(uint8_t line=0; line<LCD_Y; line++)
    {
        for(uint8_t collumn=0; collumn<LCD_X; collumn++)
        {
            expected_lcd_buf[line][collumn]=' ';
        }
    }
}

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
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdBufCharThenBufferEqualToExpected)
{
    lcd_init();
    lcd_buf_char('a');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1]='a';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnWhenLcdBufCharAandLcdBufCharBUsedThenBufferEqualToExpected)
{
    lcd_init();
    lcd_buf_char('A');
    lcd_buf_char('B');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1]='A';
    expected_lcd_buf[LINE_1][C2]='B';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufLocateFirstLineLastLetterAndLcdBufCharAThenBufferEqualToExpected)
{
    lcd_init();
    lcd_buf_locate(LINE_1,LAST_CHAR_IN_LCD_LINE);
    lcd_buf_char('A');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][LAST_CHAR_IN_LCD_LINE]='A';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufLocateFirstLineLastLetterAndLcdBufCharAandLcdBufCharBThenBufferEqualToExpected)
{
    lcd_init();
    lcd_buf_locate(LINE_1,LAST_CHAR_IN_LCD_LINE);
    lcd_buf_char('A');
    lcd_buf_char('B');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][LAST_CHAR_IN_LCD_LINE]='A';
    expected_lcd_buf[LINE_2][C1]='B';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufLocateLastLineLastLetterAndLcdBufCharAandLcdBufCharBThenBufferEqualToExpected)
{
    lcd_init();
    lcd_buf_locate(LAST_LCD_LINE,LAST_CHAR_IN_LCD_LINE);
    lcd_buf_char('A');
    lcd_buf_char('B');
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE]='A';
    expected_lcd_buf[LINE_1][C1]='B';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}

TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitWhenLcdBufStrTestThenLcdBufferEqualToExpectedLcdBuffer)
{
    lcd_init();
    lcd_buf_str("Test");
    define_expected_buffer_value_for_cls();
    expected_lcd_buf[LINE_1][C1]='T';
    expected_lcd_buf[LINE_1][C2]='e';
    expected_lcd_buf[LINE_1][C3]='s';
    expected_lcd_buf[LINE_1][C4]='t';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndSetLcdLocateLastLineLastCharacterWhenLcdBufStrTestThenLcdBufferEqualToExpectedLcdBuffer)
{
    lcd_init();
    lcd_buf_locate(LAST_LCD_LINE,LAST_CHAR_IN_LCD_LINE);
    lcd_buf_str("Test");
    define_expected_buffer_value_for_cls();
    
    expected_lcd_buf[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE]='T';
    expected_lcd_buf[LINE_1][C1]='e';
    expected_lcd_buf[LINE_1][C2]='s';
    expected_lcd_buf[LINE_1][C3]='t';
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_lcd_buf,lcd_buffer,(LCD_X*LCD_Y));
}
TEST(lcd_hd44780_buffering, GivenLcdBufferingOnAndLcdInitAndSetLcdLocateLastLineLastCharacterAndLcdBufStrTestWhenUpdateLcdScrThenSignalSequenceForUpdateLcdScrIsCorrect)
{
    lcd_init();
    lcd_buf_locate(LAST_LCD_LINE,LAST_CHAR_IN_LCD_LINE);
    lcd_buf_str("Test");

    define_expected_buffer_value_for_cls();
    
    expected_lcd_buf[LAST_LCD_LINE][LAST_CHAR_IN_LCD_LINE]='T';
    expected_lcd_buf[LINE_1][C1]='e';
    expected_lcd_buf[LINE_1][C2]='s';
    expected_lcd_buf[LINE_1][C3]='t';

    clear_expected_LCD_Port_delay_dump_data();
    mock_clear_LCD_Port_delay_dump_data();
    
    next_log_no = define_expected_sequence_for_send_string_to_LCD(&expected_lcd_buf[0][0]);
    expected_buf_lenght = (next_log_no) * (LOG_DATA_AMOUNT);
    lcd_buf_print();
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data, mock_LCD_Port_delay_dump_data, expected_buf_lenght);
}

