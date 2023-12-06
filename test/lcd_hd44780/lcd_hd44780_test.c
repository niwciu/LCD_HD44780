#include "unity/fixture/unity_fixture.h"

#include "lcd_hd44780.h"
#include "mock_LCD_IO_driver.h"

uint16_t expected_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];

TEST_GROUP(lcd_hd44780_init);

TEST_SETUP(lcd_hd44780_init)
{
    /* Init before every test */
    }

TEST_TEAR_DOWN(lcd_hd44780_init)
{
    /* Cleanup after every test */
}
TEST(lcd_hd44780_init, WhenLcdInitThenLcdDataPinsInit)
{
    lcd_init();
    #if USE_RW_PIN == ON
    TEST_ASSERT_EQUAL(0x7F,mock_get_lcd_init_state());
    #else
    TEST_ASSERT_EQUAL(0x3F,mock_get_lcd_init_state());
    #endif
}

TEST(lcd_hd44780_init, GivenLcdIniAndPinsInitWhensetallSignalsFor15msThenLcdPinStatIsCorrect)
{
    //set_correct_signal_sequence_to_log
    //set E
    expected_LCD_Port_delay_dump_data[0][0]=mock_LCD_E;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[0][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[0][2]=0; // delay_log
    //set RS
    expected_LCD_Port_delay_dump_data[1][0]=mock_LCD_E|mock_LCD_RS;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[1][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[1][2]=0; // delay_log
    //set RW
    expected_LCD_Port_delay_dump_data[2][0]=mock_LCD_E|mock_LCD_RS|mock_LCD_RW;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[2][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[2][2]=0; // delay_log
    //delay
    expected_LCD_Port_delay_dump_data[3][0]=mock_LCD_E|mock_LCD_RS|mock_LCD_RW;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[3][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[3][2]=15000; // delay_log
    //reset RW
    expected_LCD_Port_delay_dump_data[4][0]=mock_LCD_E|mock_LCD_RS;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[4][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[4][2]=0; // delay_log
    //reset RS
    expected_LCD_Port_delay_dump_data[5][0]=mock_LCD_E;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[5][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[5][2]=0; // delay_log
    //Reset E
    expected_LCD_Port_delay_dump_data[6][0]=0x00;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[6][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[6][2]=0; // delay_log
    
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data,mock_LCD_Port_delay_dump_data,21);
}
//po init wyjscia w stanie niskim

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

// TEST(lcd_hd44780_init, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(lcd_hd44780_init, FirstTest)
// {
//     TEST_FAIL_MESSAGE("Implement your test!");
// }