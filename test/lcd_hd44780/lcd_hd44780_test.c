#include "unity/fixture/unity_fixture.h"

#include "lcd_hd44780.h"
#include "mock_LCD_IO_driver.h"

uint16_t expected_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];

static void clear_expected_LCD_Port_delay_dump_data(void);

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
    TEST_ASSERT_EQUAL(0x5F,mock_get_lcd_init_state());
    #endif
}

TEST(lcd_hd44780_init, GivenLcdIniAndPinsInitWhensetallSignalsFor15msThenLcdPinStatIsCorrect)
{
    uint8_t log_no=0;
    mock_clear_LCD_Port_delay_dump_data();
    clear_expected_LCD_Port_delay_dump_data();
    lcd_init();
    //set_correct_signal_sequence_to_log
    //set E
    expected_LCD_Port_delay_dump_data[log_no][0]=mock_LCD_E;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][2]=0; // delay_log
    //set RS
    expected_LCD_Port_delay_dump_data[log_no][0]=mock_LCD_E|mock_LCD_RS;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][2]=0; // delay_log
    #if USE_RW_PIN == ON
    //set RW
    expected_LCD_Port_delay_dump_data[log_no][0]=mock_LCD_E|mock_LCD_RS|mock_LCD_RW;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][2]=0; // delay_log
    
    //delay
    expected_LCD_Port_delay_dump_data[log_no][0]=mock_LCD_E|mock_LCD_RS|mock_LCD_RW;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][2]=15000; // delay_log
    #else
    expected_LCD_Port_delay_dump_data[log_no][0]=(mock_LCD_E|mock_LCD_RS);//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][2]=15000; // delay_log
    #endif
    #if USE_RW_PIN == ON
    //reset RW
    expected_LCD_Port_delay_dump_data[log_no][0]=mock_LCD_E|mock_LCD_RS;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][2]=0; // delay_log
    #endif
    //reset RS
    expected_LCD_Port_delay_dump_data[log_no][0]=mock_LCD_E;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][2]=0; // delay_log
    //Reset E
    expected_LCD_Port_delay_dump_data[log_no][0]=0x00;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][2]=0; // delay_log
    #if USE_RW_PIN == ON
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data,mock_LCD_Port_delay_dump_data,21);
    #else
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data,mock_LCD_Port_delay_dump_data,15);
    #endif
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

static void clear_expected_LCD_Port_delay_dump_data(void)
{
    for (uint16_t i=0;i<BUF_SIZE;i++)
    {
        for(uint8_t j=0;j<LOG_DATA_AMOUNT;j++)
        {
            expected_LCD_Port_delay_dump_data[i][j]=0x00;
        }
    }
}
