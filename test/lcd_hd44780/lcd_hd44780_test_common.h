/*
 * @Author: lukasz.niewelt 
 * @Date: 2023-12-07 16:59:53 
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-07 17:05:14
 */
#include <stdint.h>
#include "mock_LCD_IO_driver.h"

#define SIG_PORT 0
#define DATA_PORT 1
#define DELAY 2

extern uint16_t next_log_no;
extern uint16_t expected_LCD_Port_delay_dump_data[BUF_SIZE][LOG_DATA_AMOUNT];

void clear_expected_LCD_Port_delay_dump_data(void);
uint16_t define_expected_sequence_for_first_15_ms_delay(void);
uint8_t define_expected_sequence_for_read_write_4_bit_data(uint8_t log_no, uint8_t R_W_data, uint16_t delay);
uint8_t define_expected_sequence_for_send_cmd_to_LCD(uint8_t log_no, uint8_t cmd,uint8_t expected_readed_data, uint16_t additional_cmd_delay);