/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-07 16:59:56 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-07 17:33:21
 */

#include "lcd_hd44780_test_common.h"


uint16_t next_log_no;
uint16_t expected_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];

void clear_expected_LCD_Port_delay_dump_data(void)
{
    for (uint16_t i = 0; i < BUF_SIZE; i++)
    {
        for (uint8_t j = 0; j < LOG_DATA_AMOUNT; j++)
        {
            expected_LCD_Port_delay_dump_data[i][j] = 0x00;
        }
    }
}

uint16_t define_expected_sequence_for_first_15_ms_delay(void)
{
    uint16_t log_no = 0;
    // set E
    
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = mock_LCD_E;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = 0x00;
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    // set RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = mock_LCD_E | mock_LCD_RS;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
#if USE_RW_PIN == ON
    // set RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = mock_LCD_E | mock_LCD_RS | mock_LCD_RW;
    expected_LCD_Port_delay_dump_data[log_no][1] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    // delay
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = mock_LCD_E | mock_LCD_RS | mock_LCD_RW;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 15000;
#else
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (mock_LCD_E | mock_LCD_RS);
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 15000;
#endif
#if USE_RW_PIN == ON
    // reset RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = mock_LCD_E | mock_LCD_RS;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
#endif
    // reset RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = mock_LCD_E;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    // Reset E
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = 0x00;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    return log_no;
}

uint8_t define_expected_sequence_for_read_write_4_bit_data(uint8_t log_no, uint8_t R_W_data, uint16_t delay)
{
    // setE
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] | mock_LCD_E;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    // write or read data on/from Port
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT];
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = R_W_data; // set second 0x03 init command
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    // Reset E
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_E));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    // delay 4500us
    if (delay != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT];
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
        expected_LCD_Port_delay_dump_data[log_no++][DELAY] = delay;
    }

    return log_no;
}

uint8_t define_expected_sequence_for_send_cmd_to_LCD(uint8_t log_no, uint8_t cmd,uint8_t expected_readed_data, uint16_t additional_cmd_delay)
{
    //reset RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RS));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
#if USE_RW_PIN == ON
    //reset RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
#endif
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, cmd >> 4, 0);
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, cmd & 0x0F, 0);
#if USE_RW_PIN == ON
    //reset_RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RS));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    //set_RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] | (mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    //read_byte that confirm that LCD is not BUSY-> 0xFF
    //read 4 MSB with from port with input value 0xFF
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, expected_readed_data >> 4, 0);
    //read 4 LSB with from port with input value 0xFF

    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, expected_readed_data & 0x0F, 0);
    //reset_RW

    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

#else
    //wait 120uS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 120;
#endif
    if (additional_cmd_delay != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
        expected_LCD_Port_delay_dump_data[log_no++][DELAY] = additional_cmd_delay;
    }
    expected_readed_data++; //to avoid warnings about unused variable and not complicate the test code too much
    return log_no;
}

uint8_t define_expected_sequence_for_send_data_to_LCD(uint8_t log_no, uint8_t data,uint8_t expected_readed_data, uint16_t additional_cmd_delay)
{
    //reset RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RS));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
#if USE_RW_PIN == ON
    //reset RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
#endif
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, data >> 4, 0);
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, data & 0x0F, 0);
#if USE_RW_PIN == ON
    //reset_RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RS));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    //set_RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] | (mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    //read_byte that confirm that LCD is not BUSY-> 0xFF
    //read 4 MSB with from port with input value 0xFF
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, expected_readed_data >> 4, 0);
    //read 4 LSB with from port with input value 0xFF

    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, expected_readed_data & 0x0F, 0);
    //reset_RW

    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

#else
    //wait 120uS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 120;
#endif
    if (additional_cmd_delay != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
        expected_LCD_Port_delay_dump_data[log_no++][DELAY] = additional_cmd_delay;
    }
    expected_readed_data++; //to avoid warnings about unused variable and not complicate the test code too much
    return log_no;
}

