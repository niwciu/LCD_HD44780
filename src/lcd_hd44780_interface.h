/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-06 21:38:59
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-06 22:31:49
 */

#ifndef _LCD_HD44780_INTERFACE_H_
#define _LCD_HD44780_INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#include <stdint.h>
    enum lcd_sig
    {
        LCD_RS,
        LCD_RW,
        LCD_E,
    };

    typedef void (*init_LCD_data_and_SIG_pins_func_p)(void);
    typedef void (*set_LCD_data_pins_as_outputs_func_p)(void);
    typedef void (*set_LCD_data_pins_as_inputs_func_p)(void);
    typedef void (*set_LCD_data_port_func_p)(uint8_t data);
    typedef uint8_t (*get_LCD_data_port_func_p)(void);
    typedef void (*init_LCD_SIG_func_p)(void);
    typedef void (*set_LCD_SIG_func_p)(enum lcd_sig LCD_SIG);
    typedef void (*reset_LCD_SIG_func_p)(enum lcd_sig LCD_SIG);
    typedef void (*delay_us_func_p)(uint32_t delay_us);

    struct LCD_IO_driver_interface_struct
    {
        init_LCD_data_and_SIG_pins_func_p init_LCD_pins;
        set_LCD_data_pins_as_outputs_func_p set_data_pins_as_outputs;
        set_LCD_data_pins_as_inputs_func_p init_data_pins_as_inputs;
        set_LCD_data_port_func_p write_data;
        get_LCD_data_port_func_p read_data;
        init_LCD_SIG_func_p init_SIG;
        set_LCD_SIG_func_p set_SIG;
        reset_LCD_SIG_func_p reset_SIG;
        delay_us_func_p delay_us;
    };
    // clang-format off
    const struct LCD_IO_driver_interface_struct* LCD_IO_driver_interface_get(void);
    // clang-format on

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD_44780_H_ */