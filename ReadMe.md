
![IMG_20240806_184040](https://github.com/user-attachments/assets/e4d0a212-e7fc-4d60-82d5-acb44ff15912)

# LCD HD44780 lib - simple cross-platform C library
![GitHub License](https://img.shields.io/github/license/niwciu/LCD_HD44780)  
![GitHub top language](https://img.shields.io/github/languages/top/niwciu/LCD_HD44780)
![GitHub Release](https://img.shields.io/github/v/release/niwciu/LCD_HD44780)  
![GitHub branch check runs](https://img.shields.io/github/check-runs/niwciu/LCD_HD44780/main)  
![Unit Tests](https://github.com/niwciu/LCD_HD44780/actions/workflows/run_lcd_hd44780_test.yml/badge.svg)
![cppCheck](https://github.com/niwciu/LCD_HD44780/actions/workflows/run_cppcheck.yml/badge.svg)
![clang-format](https://github.com/niwciu/LCD_HD44780/actions/workflows/clang-format_check.yml/badge.svg)
![code complexity](https://github.com/niwciu/LCD_HD44780/actions/workflows/run_lizard_lib_check.yml/badge.svg) 

## Features

- Works with LCD connected in 4-bit mode, 
- One-direction or bi-direction communication with LCD (predefined time slots or LCD RW pin usage)
- Easy to port on different microcontrollers
- Contain examples of porting to STM32, AVR, ESP8266
- Allows to display strings/chars directly on LCD
- Allows to put strings/chars in buffer and refresh LCD periodically with buffer content
- Allows to define custom chars (more than 8) as well as custom char banks where different combinations of custom characters can be easily loaded to LCD CGRAM
- Contain functions for displaying on LCD int values as a string representing:
  - int format 
  - hex format 
  - bin format
- The library has currently predefined following LCD types:
  - 2 lines 16 characters (1602)
  - 4 lines 16 characters (1604)
  - 4 lines 20 characters (2004)
- Allows to configure and compile only functionality that will be needed in the project
- Allows to control LCD backlight
## Examples
The library contains examples of usage with different platforms (STM32, AVR, ESP8266). 

Besides ready-to-compile and run demo applications, you will find templates and examples of driver interface files in the library, which should speed up your design process. 

For more information about the examples, please refer to the [LCD_HD44780 wiki](https://github.com/niwciu/LCD_HD44780/wiki)
## Other information
For information such:
- detail description,
- hardware requirements,
- library configuration, 
- library usage, 
- examples description and usage
- collaboration in the project,

please refer to [LCD_HD44780 wiki](https://github.com/niwciu/LCD_HD44780/wiki)

***

![myEmbeddedWayBanerWhiteSmaller](https://github.com/user-attachments/assets/f4825882-e285-4e02-a75c-68fc86ff5716)
***