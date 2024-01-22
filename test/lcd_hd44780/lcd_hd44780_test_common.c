/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-07 16:59:56
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-10 10:13:21
 */

#include "lcd_hd44780_test_common.h"
#include "lcd_hd44780_config.h"
#include "stdio.h"

uint16_t next_log_no;
uint16_t expected_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];
uint16_t expected_buf_lenght;

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

uint8_t read_prev_LCD_DATA_PORT_state(void)
{
    return mock_LCD_DATA_PORT;
}

uint8_t read_prev_LCD_SIG_PORT_state(void)
{
    return mock_LCD_SIG_PORT;
}

log_no_t define_expected_sequence_for_lcd_backlight_disable(log_no_t start_log_no)
{
#if LCD_BCKL_PIN_EN_STATE == HIGH
    expected_LCD_Port_delay_dump_data[start_log_no][SIG_PORT] &= ~(mock_LCD_BCKL);
#else
    expected_LCD_Port_delay_dump_data[start_log_no][SIG_PORT] = (mock_LCD_BCKL);
#endif
    expected_LCD_Port_delay_dump_data[start_log_no][DATA_PORT] = 0x00;
    expected_LCD_Port_delay_dump_data[start_log_no++][DELAY] = 0;
    return start_log_no;
}

uint16_t define_expected_sequence_for_first_15_ms_delay(log_no_t log_no)
{
    uint8_t lcd_bckl_state = expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT];
    // set E
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = lcd_bckl_state | mock_LCD_E;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = 0x00;
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    // set RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = lcd_bckl_state | mock_LCD_E | mock_LCD_RS;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
#if USE_RW_PIN == ON
    // set RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = lcd_bckl_state | mock_LCD_E | mock_LCD_RS | mock_LCD_RW;
    expected_LCD_Port_delay_dump_data[log_no][1] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    // delay
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = lcd_bckl_state | mock_LCD_E | mock_LCD_RS | mock_LCD_RW;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 15000;
#else
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (lcd_bckl_state | mock_LCD_E | mock_LCD_RS);
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 15000;
#endif
#if USE_RW_PIN == ON
    // reset RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = lcd_bckl_state | mock_LCD_E | mock_LCD_RS;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
#endif
    // reset RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (lcd_bckl_state | mock_LCD_E);
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    // Reset E
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = lcd_bckl_state;
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;
    return log_no;
}

log_no_t define_expected_sequence_for_read_write_4_bit_data(log_no_t log_no, uint8_t R_W_data, uint16_t delay)
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
#if USE_RW_PIN == ON
uint16_t define_expected_sequence_for_send_cmd_to_LCD(log_no_t log_no, uint8_t cmd, uint8_t expected_readed_data)
{
    // reset RS

    if (log_no != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RS));
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    }
    else
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (read_prev_LCD_SIG_PORT_state() & (~(mock_LCD_RS)));
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = read_prev_LCD_DATA_PORT_state();
    }
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    // reset RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, cmd >> 4, 0);
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, cmd & 0x0F, 0);

    // reset_RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RS));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    // set_RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] | (mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    // read_byte that confirm that LCD is not BUSY-> 0xFF
    // read 4 MSB with from port with input value 0xFF
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, expected_readed_data >> 4, 0);
    // read 4 LSB with from port with input value 0xFF

    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, expected_readed_data & 0x0F, 0);
    // reset_RW

    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    return log_no;
}
#else
uint16_t define_expected_sequence_for_send_cmd_to_LCD(log_no_t log_no, uint8_t cmd, uint16_t additional_cmd_delay)
{
    // reset RS

    if (log_no != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RS));
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    }
    else
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (read_prev_LCD_SIG_PORT_state() & (~(mock_LCD_RS)));
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = read_prev_LCD_DATA_PORT_state();
    }
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, cmd >> 4, 0);
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, cmd & 0x0F, 0);

    // wait 120uS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 120;

    if (additional_cmd_delay != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
        expected_LCD_Port_delay_dump_data[log_no++][DELAY] = additional_cmd_delay;
    }

    return log_no;
}
#endif

#if USE_RW_PIN == ON
uint16_t define_expected_sequence_for_send_data_to_LCD(log_no_t log_no, uint8_t data, uint8_t expected_readed_data, uint16_t additional_cmd_delay)
{
    // reset RS
    if (log_no != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] | mock_LCD_RS);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    }
    else
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (read_prev_LCD_SIG_PORT_state() | mock_LCD_RS);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = read_prev_LCD_DATA_PORT_state();
    }
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    // reset RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, data >> 4, 0);
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, data & 0x0F, 0);

    // reset_RS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RS));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    // set_RW
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] | (mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    // read_byte that confirm that LCD is not BUSY-> 0xFF
    // read 4 MSB with from port with input value 0xFF
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, expected_readed_data >> 4, 0);
    // read 4 LSB with from port with input value 0xFF

    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, expected_readed_data & 0x0F, 0);
    // reset_RW

    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] & ~(mock_LCD_RW));
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    if (additional_cmd_delay != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
        expected_LCD_Port_delay_dump_data[log_no++][DELAY] = additional_cmd_delay;
    }
    // expected_readed_data++; // to avoid warnings about unused variable and not complicate the test code too much
    return log_no;
}
#else
uint16_t define_expected_sequence_for_send_data_to_LCD(log_no_t log_no, uint8_t data, uint16_t additional_cmd_delay)
{
    // reset RS
    if (log_no != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT] | mock_LCD_RS);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    }
    else
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (read_prev_LCD_SIG_PORT_state() | mock_LCD_RS);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = read_prev_LCD_DATA_PORT_state();
    }
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 0;

    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, data >> 4, 0);
    log_no = define_expected_sequence_for_read_write_4_bit_data(log_no, data & 0x0F, 0);

    // wait 120uS
    expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
    expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
    expected_LCD_Port_delay_dump_data[log_no++][DELAY] = 120;

    if (additional_cmd_delay != 0)
    {
        expected_LCD_Port_delay_dump_data[log_no][SIG_PORT] = (expected_LCD_Port_delay_dump_data[log_no - 1][SIG_PORT]);
        expected_LCD_Port_delay_dump_data[log_no][DATA_PORT] = expected_LCD_Port_delay_dump_data[log_no - 1][DATA_PORT];
        expected_LCD_Port_delay_dump_data[log_no++][DELAY] = additional_cmd_delay;
    }
    // expected_readed_data++; // to avoid warnings about unused variable and not complicate the test code too much
    return log_no;
}
#endif
#if USE_DEF_CHAR_FUNCTION == ON
uint16_t define_expect_sequence_for_lcd_def_char(log_no_t log_no, const uint8_t CGRAM_bank_x_char_index, const uint8_t *def_char)
{
    uint8_t CGRAM_start_adress = ((DEF_CHAR_ADR_MASK & CGRAM_bank_x_char_index) * LCD_CGRAM_BYTES_PER_CHAR);
    uint8_t cmd = (LCDC_SET_CGRAM | CGRAM_start_adress);
#if USE_RW_PIN == ON
    log_no = define_expected_sequence_for_send_cmd_to_LCD(log_no, cmd, 0x00);

    for (uint8_t j = 0; j < LCD_CGRAM_BYTES_PER_CHAR; j++)
    {
        log_no = define_expected_sequence_for_send_data_to_LCD(log_no, def_char[j], 0x00, 0);
    }

    log_no = define_expected_sequence_for_send_cmd_to_LCD(log_no, LCDC_SET_DDRAM, 0x00);
#else
    log_no = define_expected_sequence_for_send_cmd_to_LCD(log_no, cmd, 0);

    for (uint8_t j = 0; j < LCD_CGRAM_BYTES_PER_CHAR; j++)
    {
        log_no = define_expected_sequence_for_send_data_to_LCD(log_no, def_char[j], 0);
    }

    log_no = define_expected_sequence_for_send_cmd_to_LCD(log_no, LCDC_SET_DDRAM, 0);
#endif

    return log_no;
}
#endif
uint16_t define_expected_sequence_for_send_string_to_LCD(const char *string, uint16_t next_log)
{
    // uint16_t next_log = 0;
    register char c;
    while ((c = *(string++)))
    {
#if USE_RW_PIN == ON
        next_log = define_expected_sequence_for_send_data_to_LCD(next_log, (uint8_t)(c), 0x00, 0);
#else
        next_log = define_expected_sequence_for_send_data_to_LCD(next_log, (uint8_t)(c), 0);
#endif
    }
    return next_log;
}
