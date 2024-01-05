# Simple cross-platform C library for LCD with HD44780 controller
- [Simple cross-platform C library for LCD with HD44780 controller](#simple-cross-platform-c-library-for-lcd-with-hd44780-controller)
  - [Hardware configuration](#hardware-configuration)
    - [Requirements](#requirements)
    - [Schematic for possible hardware configurations](#schematic-for-possible-hardware-configurations)
  - [Examples](#examples)
    - [STM32G0](#stm32g0)
      - [Requirements](#requirements-1)
      - [Hadrware connections](#hadrware-connections)
      - [How to build and run example](#how-to-build-and-run-example)
    - [AVR](#avr)
      - [Requirements](#requirements-2)
      - [Hadrware connections](#hadrware-connections-1)
      - [How to build and run example](#how-to-build-and-run-example-1)
    - [ESP8266 NONOS SDK](#esp8266-nonos-sdk)
      - [Requirements](#requirements-3)
      - [Hadrware connections](#hadrware-connections-2)
      - [How to build and run example](#how-to-build-and-run-example-2)
  - [How to use in your Project - simple case](#how-to-use-in-your-project---simple-case)
  - [How to use in your Project - advanced case](#how-to-use-in-your-project---advanced-case)
  - [How to define custom characters and custom character banks.](#how-to-define-custom-characters-and-custom-character-banks)
    - [Example of Correspondence between EPROM Address Data and Character Pattern (5 × 8 Dots)](#example-of-correspondence-between-eprom-address-data-and-character-pattern-5--8-dots)
    - [Defining special characters in code.](#defining-special-characters-in-code)
    - [Defining banks for special characters.](#defining-banks-for-special-characters)
  - [Project main folders file structure](#project-main-folders-file-structure)


## Hardware configuration
### Requirements
- LCD should be connected to uC in 4bit mode 
- LCD RW Pin can be connected to uC or GND -> user can define specific options in code.
- LCD data pins from LCD D4-D7 must be connected to the same port on uC side
- LCD signals pins that are E, RS, and optionally RW must be connected to the same port on the uC side. This port can be different then port for LCD data pins
### Schematic for possible hardware configurations
- Using RW pin of the LCD  (set **USE_RW_PIN &nbsp; ON** in lcd_hd44780_config.h)<br><br>
<img src="./doc/HW%20connection%20using%20RW.png"   height="400"><br> <br><br>
- Without using RW pin of the LCD  (set **USE_RW_PIN &nbsp; OFF** in lcd_hd44780_config.h)
<br><br>
<img src="./doc/HW%20connection%20no%20RW.png"   height="400"><br> <br>
## Examples
### STM32G0
#### Requirements
#### Hadrware connections
#### How to build and run example
### AVR
#### Requirements
#### Hadrware connections
#### How to build and run example
### ESP8266 NONOS SDK
#### Requirements
#### Hadrware connections
#### How to build and run example
## How to use in your Project - simple case
1. Copy LCD library src files (files from src folder) to your project
2. In lcd_hd44780.config.h 
   - Define specific **LCD_TYPE** and usage of **RW Pin**<br>
    &emsp; &emsp;LCD_TYPE -> set one of the predefined types:<br>
                &emsp; &emsp;&emsp; &emsp;2004 -> 4 lines 20 characters per line<br>
                &emsp; &emsp;&emsp; &emsp;1604 -> 4 lines 16 characters per line<br>
                &emsp; &emsp;&emsp; &emsp;1602 -> 2 lines 16 characters per line<br>
    &emsp; &emsp;USE_RW_PIN -> Defines HW connection between LCD and uC<br>
                &emsp; &emsp;&emsp; &emsp;ON - when RW pin is connected<br>
                &emsp; &emsp;&emsp; &emsp;OFF - when RW pin is not connected<br>


3. Define the LCD IO driver interface in your application. This interface should contain the following implementation defined in lcd_hd44780_interface.h
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
It's a basic interface that connects the library with your HW driver layer in the application without making any dependencies between them. For more details, please lock in the example folder and search for the LCD_IO_driver.c file for the specific uController that you want to use.


## How to use in your Project - advanced case
1. Copy LCD library src files (files from src folder) to your project
2. In lcd_hd44780.config.h 
   - Define specyfic **LCD_TYPE** and usage of **RW Pin**<br>
    &emsp; &emsp;LCD_TYPE -> set one of the predefined types:<br>
                &emsp; &emsp;&emsp; &emsp;2004 -> 4 lines 20 characters per line<br>
                &emsp; &emsp;&emsp; &emsp;1604 -> 4 lines 16 characters per line<br>
                &emsp; &emsp;&emsp; &emsp;1602 -> 2 lines 16 characters per line<br>
    &emsp; &emsp;USE_RW_PIN -> Defines HW connection between LCD and uC<br>
                &emsp; &emsp;&emsp; &emsp;ON - when RW pin is connected<br>
                &emsp; &emsp;&emsp; &emsp;OFF - when RW pin is not connected<br>

    - Specify which procedures from to library you would like to compile and use in your project.<br>
      To do this, Edit defines in section: <br><br>
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
3. If setting USE_DEF_CHAR_FUNCTION &nbsp; ON define special characters and character banks in lcd_hd44780_def_char.h <br> For more details about defining custom char please refer to [How to define custom characters and custom character banks.](#how-to-define-custome-charatcters-and-custom-character-banks)
4. Define the LCD IO driver interface in your application. <br> 
   This interface should contain the following implementation defined in lcd_hd44780_interface.h<br>
   <br><br>
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
    It's a basic interface that connects the library with your HW driver layer in the application without making any dependencies between them. For more details, please lock in the example folder and search for the LCD_IO_driver.c file for the specific uController that you want to use.
## How to define custom characters and custom character banks.
### Example of Correspondence between EPROM Address Data and Character Pattern (5 × 8 Dots)
<img src="./doc/font map.png" height="350"><br> <br>
<br>
### Defining special characters in code.
If the letter shown in the picture above should be defined as a special character its definition should look like this:
```C
static const uint8_t leter_b[8] = {16, 16, 22, 25, 17, 17, 30, 0};
```
### Defining banks for special characters.
HD44780 allows the user to define a maximum of 8 user characters. Therefore on character bank can contain only up to 8 characters. Nevertheless, it's possible to define a couple of special character banks with different combinations of special characters. Depending on needs one of the banks can be loaded to the CGRAM and switched to another if the information presented on the LCD requires different special characters

Below you can find a simple example of two special characters bank definitions:
1.  Definition of special characters in lcd_hd44780_def_char.h:
    ```C
    static const uint8_t Pol_e[8] = {0, 0, 14, 17, 31, 16, 14, 3};
    static const uint8_t Pol_o[8] = {2, 4, 14, 17, 17, 17, 14, 0};
    static const uint8_t Pol_s[8] = {2, 4, 14, 16, 14, 1, 30, 0};
    static const uint8_t Pol_l[8] = {12, 4, 6, 12, 4, 4, 14, 0};
    static const uint8_t Pol_c[8] = {2, 4, 14, 16, 16, 17, 14, 0};
    static const uint8_t Pol_a[8] = {0, 0, 14, 1, 15, 17, 15, 3};
    static const uint8_t Pol_n[8] = {2, 4, 22, 25, 17, 17, 17, 0};
    static const uint8_t Zn_wody[8] = {0, 0, 0, 6, 9, 2, 4, 15};
    static const uint8_t Pol_z1[8] = {4, 32, 31, 2, 4, 8, 31, 0};
    static const uint8_t Pol_z2[8] = {2, 4, 31, 2, 4, 8, 31, 0};
    ```
2. Definition of lcd_cgram_bank_1 in lcd_hd44780_def_char.h:
    ```C
    static const struct char_bank_struct lcd_cgram_bank_1 = {
        Pol_e,
        Pol_o,
        Pol_s,
        Pol_l,
        Pol_c,
        Pol_a,
        Pol_n,
        Zn_wody};
    enum LCD_CGRAM_BANK_1
    {
        pol_e,
        pol_o,
        pol_s,
        pol_l,
        pol_c,
        pol_a,
        pol_n,
        zn_wody,
    };
    ```
3. Definition of lcd_cgram_bank_2 in lcd_hd44780_def_char.h:
    ```C
    static const struct char_bank_struct lcd_cgram_bank_1 = {
        Pol_e,
        Pol_o,
        Pol_s,
        Pol_l,
        Pol_c,
        Pol_a,
        Pol_z1,
        Pol_z2};
    enum LCD_CGRAM_BANK_1
    {
        pol_e,
        pol_o,
        pol_s,
        pol_l,
        pol_c,
        pol_a,
        pol_z1,
        pol_z2,
    };
    ```
4. When special characters from bank_1 are needed to display content on an LCD screen, it's required to call in the code:
    ```C
    lcd_load_char_bank(&lcd_cgram_bank_1);
    ```
5. When special characters from bank_2 are required to display content on an LCD screen, then it's required to call in code:
    ```C
    lcd_load_char_bank(&lcd_cgram_bank_2);
    ```


## Project main folders file structure
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

