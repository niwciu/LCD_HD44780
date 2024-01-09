/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-07 16:59:53
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2024-01-09 18:23:43
 */
#include <stdint.h>
#include "mock_LCD_IO_driver.h"
#include "lcd_hd44780.h"

#define SIG_PORT 0
#define DATA_PORT 1
#define DELAY 2

extern uint16_t next_log_no;
extern uint16_t expected_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];
extern uint16_t expected_buf_lenght;

void clear_expected_LCD_Port_delay_dump_data(void);
uint8_t read_prev_LCD_DATA_PORT_state(void);
uint8_t read_prev_LCD_SIG_PORT_state(void);
uint16_t define_expected_sequence_for_first_15_ms_delay(void);
uint16_t define_expected_sequence_for_read_write_4_bit_data(uint16_t log_no, uint8_t R_W_data, uint16_t delay);
#if USE_RW_PIN == ON
uint16_t define_expected_sequence_for_send_cmd_to_LCD(uint16_t log_no, uint8_t cmd, uint8_t expected_readed_data);
uint16_t define_expected_sequence_for_send_data_to_LCD(uint16_t log_no, uint8_t data, uint8_t expected_readed_data, uint16_t additional_cmd_delay);
#else
uint16_t define_expected_sequence_for_send_cmd_to_LCD(uint16_t log_no, uint8_t cmd, uint16_t additional_cmd_delay);
uint16_t define_expected_sequence_for_send_data_to_LCD(uint16_t log_no, uint8_t data, uint16_t additional_cmd_delay);
#endif

uint16_t define_expect_sequence_for_lcd_def_char(uint16_t log_no, const uint8_t CGRAM_bank_x_char_index, const uint8_t *def_char);
uint16_t define_expected_sequence_for_send_string_to_LCD(const char *string, uint16_t next_log);