/**
 * @file lcd_hd44780_interface.h
 * @author niwciu (niwciu@gmail.com)
 * @brief Header file with driver interface declaration that needs to be implemented on the driver layer side.
 * This instance eliminates dependencies between the LCD library and the specific microcontroller driver layer.
 * @version 1.0.2
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 * @defgroup LCD_HD44780_driver_interface
 * @{
 */
#ifndef _LCD_HD44780_INTERFACE_H_
#define _LCD_HD44780_INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#include <stdint.h>
    /**
     * @enum lcd_sig_e
     * @brief LCD Signal labels used as argument when calling functions LCD->set_SIG, LCD->reset_SIG from defined LCD_IO_driver_interface_struct
     */
    enum lcd_sig_e
    {
        LCD_RS,
        LCD_RW,
        LCD_E,
        LCD_BCKL,
    };

    typedef uint8_t LCD_data_port_t;
    typedef void (*init_LCD_data_and_SIG_pins_func_p)(void);
    typedef void (*set_LCD_data_pins_as_outputs_func_p)(void);
    typedef void (*set_LCD_data_pins_as_inputs_func_p)(void);
    typedef void (*set_LCD_data_port_func_p)(uint8_t data);
    typedef LCD_data_port_t (*get_LCD_data_port_func_p)(void);
    typedef void (*set_LCD_SIG_func_p)(enum lcd_sig_e LCD_SIG);
    typedef void (*reset_LCD_SIG_func_p)(enum lcd_sig_e LCD_SIG);
    typedef void (*delay_us_func_p)(uint32_t delay_us);

    /**
     * @struct LCD_IO_driver_interface_struct
     * @brief LCD I/O driver interface definition.
     * @attention This interface declaration need to be defined on driver layer side and "full fill the contract" of the defined LCD_IO_driver_interface_struct
     *
     */
    struct LCD_IO_driver_interface_struct
    {
        init_LCD_data_and_SIG_pins_func_p init_LCD_pins;
        set_LCD_data_pins_as_outputs_func_p set_data_pins_as_outputs;
        set_LCD_data_pins_as_inputs_func_p set_data_pins_as_inputs;
        set_LCD_data_port_func_p write_data;
        get_LCD_data_port_func_p read_data;
        set_LCD_SIG_func_p set_SIG;
        reset_LCD_SIG_func_p reset_SIG;
        delay_us_func_p delay_us;
    };
    // clang-format off
    /**
     * @brief Declaration of the function that return pointer to the interface structure implemented on driver layer side.
     * @attention This function need to be defined on driver layer side and must return pointer to LCD_IO_driver_interface_struct defined on dirver layer side
     * @return const struct LCD_IO_driver_interface_struct*
     */
    const struct LCD_IO_driver_interface_struct* LCD_IO_driver_interface_get(void);
    // clang-format on
/**@}*/
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _LCD_HD_44780_H_ */