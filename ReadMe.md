# Simple cross-platform C library for LCD with HD44780 controller
## Hardware configuration
### Reguirements
- LCD should be connected to uC in 4bit mode 
- LCD RW Pin can be connected to uC or to GND -> user can define specyfic option in code.
- LCD data pins from LCD D4-D7 must be connected to the same port on uC side
- LCD signals pins E,RS and optionaly RW must be connected to the sam port on uC side. This port can be different then port for LCD data pins
### Schematic of possible Hardware configurations

## Examples
### Requirements to run the example on STM32G0
### How to run STM32G0 example
### Requirements to run the example on AVR
### How to run Example example
### Requirements to run the example on ESP8266 NONOS SDK
### How to run ESP8266 NONOS SDK
## How to use in your Project - simple case
1. Copy LCD src files to your project
2. In lcd_hd44780.config.h 
   - Define specyfic **LCD_TYPE** and usage of **RW Pin**<br>
    &emsp; &emsp;LCD_TYPE -> set one of the predefined types:<br>
                &emsp; &emsp;&emsp; &emsp;2004 -> 4 lines 20 characters per line<br>
                &emsp; &emsp;&emsp; &emsp;1604 -> 4 lines 16 characters per line<br>
                &emsp; &emsp;&emsp; &emsp;1602 -> 2 lines 16 characters per line<br>
    &emsp; &emsp;USE_RW_PIN -> Defines HW connection between LCD and uC<br>
                &emsp; &emsp;&emsp; &emsp;ON - when RW pin is connected<br>
                &emsp; &emsp;&emsp; &emsp;OFF - when RW pin is not connected<br>


3. Define LCD IO driver interface in you application. This interface should contain fallowing inplementation defined in lcd_hd44780_interface.h
```C 
   /************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_data_and_SIG_pins,
    set_LCD_DATA_PINS_as_outputs,
    set_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
    init_LCD_SIGNAL_PINS_as_outputs,
    LCD_set_SIG,
    LCD_reset_SIG,
    _delay_us,
};
const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
{
    return &LCD_IO_driver;
}

```
It's a basic interfafce that connect library with your hw driver layer in application withiut making any depedencies between them. For more details, please lock at the example folder and search for LCD_IO_driver.c file for specific uController that you want to use.


## How to use in your Project - advance case
1. Copy LCD src files to your project
2. In lcd_hd44780.config.h 
   - Define specyfic **LCD_TYPE** and usage of **RW Pin**<br>
    &emsp; &emsp;LCD_TYPE -> set one of the predefined types:<br>
                &emsp; &emsp;&emsp; &emsp;2004 -> 4 lines 20 characters per line<br>
                &emsp; &emsp;&emsp; &emsp;1604 -> 4 lines 16 characters per line<br>
                &emsp; &emsp;&emsp; &emsp;1602 -> 2 lines 16 characters per line<br>
    &emsp; &emsp;USE_RW_PIN -> Defines HW connection between LCD and uC<br>
                &emsp; &emsp;&emsp; &emsp;ON - when RW pin is connected<br>
                &emsp; &emsp;&emsp; &emsp;OFF - when RW pin is not connected<br>

    - Specify which procedures form to library you would like to compile and use in you project.<br>
    To do this, Edit defines in secction: <br><br>
    ```C
    /********************************  LCD LIBRARY COMPILATION SETTINGS ************************
    *      Setting USE_(procedure name) to:
    *          ON  - add specific procedure to complilation
    *          OFF - exclude specific procedure from complitaion
    ********************************************************************************************/
   #define USE_DEF_CHAR_FUNCTION           ON
    #define USE_LCD_INT                     ON
    #define USE_LCD_HEX                     ON
    #define USE_LCD_BIN                     ON

    #define USE_LCD_CURSOR_HOME             ON
    #define USE_LCD_CURSOR_ON               ON
    #define USE_LCD_CURSOR_OFF              ON
    #define USE_LCD_BLINKING_CURSOR_ON      ON
    ...
    ```
    <br>
3. Define LCD IO driver interface in you application.<br>
   This interface should contain fallowing inplementation defined in lcd_hd44780_interface.h<br><br>
    ```C 
   /************LCD_IO_driver_interface implementation START**************/
    static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
        init_LCD_data_and_SIG_pins,
        set_LCD_DATA_PINS_as_outputs,
        set_LCD_DATA_PINS_as_inputs,
        set_LCD_DATA_PINS_state,
        get_LCD_DATA_PINS_state,
        init_LCD_SIGNAL_PINS_as_outputs,
        LCD_set_SIG,
        LCD_reset_SIG,
        _delay_us,
    };
    const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
    {
        return &LCD_IO_driver;
    }
    ```
    <br>
    It's a basic interfafce that connect library with your hardware driver layer in application without making any depedencies between them. For more details, please lock at the example folder and search for LCD_IO_driver.c file for specific uController that you want to use.

## Project file structure
Main folder structure
```bash 
LCD_HD44780
├───.github
├───.vscode
├───doc
├───hw
│   ├───ATMEGA328P_ARDUINO_UNO_R3
│   ├───config
│   ├───STM32F030R8
│   ├───STM32F091RB
│   └───STM32G070RB
├───reports
│   ├───Code_Coverage
│   └───Cyclomatic_Complexity
├───src
└───test
    ├───hw_test
    │   ├───ATMEGA328P_ARDUINO_UNO_R3
    │   └───STM32F030R8_CUBE_IDE
    ├───lcd_hd44780
    ├───template                
    └───unity
```
Folder description:
- .github -> Folder with githubactions .yml scripts
- .vscode -> folder with vscode example settings for luch.json and tasks.json
- doc -> folder for any documentations needes or created in the project
- hw -> folder with example hardware implementations contain ready to compile examples for different uC
- test -> folder where all tests are written. Folder contain fallowing subfolders:
  - hw_test -> folder with configurations/setups for specyfic ucontrollers to make integration tests
  - lcd_hd44780 -> folder where all unit tests for lcd_hd44780 module are keept
  - template -> empty setup for uint test (copy, paste, rename, edit for new module unit testing) 
  - unity -> unity framework

