#include "unity/fixture/unity_fixture.h"

#include "lcd_hd44780.h"
#include "mock_LCD_IO_driver.h"

#define SIG_PORT 0
#define DATA_PORT 1
#define DELAY 2

uint16_t next_log_no;
uint16_t expected_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];

static void clear_expected_LCD_Port_delay_dump_data(void);
static uint16_t define_expected_sequence_for_first_15_ms_delay(void);

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
    uint8_t expected_resoult=0;
    lcd_init();
    #if USE_RW_PIN == ON
    expected_resoult=((mock_LCD_RW|mock_LCD_E|mock_LCD_RS)<<4)|(mock_LCD_D4|mock_LCD_D5|mock_LCD_D6|mock_LCD_D7);
    #else
    expected_resoult=((mock_LCD_E|mock_LCD_RS)<<4)|(mock_LCD_D4|mock_LCD_D5|mock_LCD_D6|mock_LCD_D7);
    #endif
    TEST_ASSERT_EQUAL(expected_resoult,mock_get_lcd_init_state());
}
TEST(lcd_hd44780_init, WhenLcdInitThenLcdPinLow)
{
    lcd_init();
    TEST_ASSERT_EQUAL(0x00,(mock_LCD_DATA_PORT| mock_LCD_SIG_PORT));
}

TEST(lcd_hd44780_init, GivenLcdIniAndPinsInitWhensetallSignalsFor15msThenLcdPinStatIsCorrect)
{
    uint16_t expected_buf_lenght=0;

    mock_clear_LCD_Port_delay_dump_data();
    clear_expected_LCD_Port_delay_dump_data();
    lcd_init();

    next_log_no=define_expected_sequence_for_first_15_ms_delay();
    expected_buf_lenght=(next_log_no-1)*(LOG_DATA_AMOUNT);

    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_LCD_Port_delay_dump_data,mock_LCD_Port_delay_dump_data,expected_buf_lenght);

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

static uint16_t define_expected_sequence_for_first_15_ms_delay(void)
{
    uint16_t log_no=0;
    //set E
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT]=mock_LCD_E;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][DELAY]=0; // delay_log
    //set RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT]=mock_LCD_E|mock_LCD_RS;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][DELAY]=0; // delay_log
    #if USE_RW_PIN == ON
    //set RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT]=mock_LCD_E|mock_LCD_RS|mock_LCD_RW;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][1]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][DELAY]=0; // delay_log
    
    //delay
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT]=mock_LCD_E|mock_LCD_RS|mock_LCD_RW;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][DELAY]=15000; // delay_log
    #else
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT]=(mock_LCD_E|mock_LCD_RS);//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][DELAY]=15000; // delay_log
    #endif
    #if USE_RW_PIN == ON
    //reset RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT]=mock_LCD_E|mock_LCD_RS;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][DELAY]=0; // delay_log
    #endif
    //reset RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT]=mock_LCD_E;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][DELAY]=0; // delay_log
    //Reset E
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT]=0x00;//SIG_PORT_log
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT]=0x00;//Data_Port_log
    expected_LCD_Port_delay_dump_data[log_no++][DELAY]=0; // delay_log
    return log_no;
}
