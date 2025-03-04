
# LCD HD44780 lib - simple cross-platform C library
![lcd_hd44780_header](https://github.com/user-attachments/assets/34ef4a66-2f08-4057-8b54-51be6f783df2)

![GitHub License](https://img.shields.io/github/license/niwciu/LCD_HD44780) 
![GitHub top language](https://img.shields.io/github/languages/top/niwciu/LCD_HD44780)
![GitHub Release](https://img.shields.io/github/v/release/niwciu/LCD_HD44780)
![GitHub branch check runs](https://img.shields.io/github/check-runs/niwciu/LCD_HD44780/main)
![CI Pipeline](https://github.com/niwciu/LCD_HD44780/actions/workflows/CI_Pipeline.yml/badge.svg)
<!-- <img src='https://coveralls.io/repos/github/niwciu/LCD_HD44780/badge.svg?branch=feature/code_coverage_page_deploy' alt='Coverage Status' /></a> -->

[**HD44780 Custom Character Generator**](https://github.com/niwciu/HD44780_CHAR_GENERATOR) - a web tool that allows graphical design of custom characters, combine those characters in char banks and automatic generation of C code for this library.

<b><a href='https://niwciu.github.io/LCD_HD44780/reports/CCR/lcd_hd44780_report.html'>Library GCOVR Report</a></b>  
<b><a href='https://niwciu.github.io/LCD_HD44780/reports/CCM/lcd_hd44780.html'>Library Code Complexity Report</a></b>  <br><br>
<b><a href='https://niwciu.github.io/LCD_HD44780/doc/LCD_HD44780_lib_doc/html/index.html'>Code Documentation </a></b>  


## Features


- Works with LCD connected in 4-bit mode, 
- One-direction or bi-direction communication with LCD (predefined time slots or LCD RW pin usage)
- Easy to port on different microcontrollers
- Contain examples of porting to STM32, AVR, ESP8266
- Allows to display strings/chars directly on LCD
- Allows to put strings/chars in buffer and refresh LCD periodically with buffer content
- Allows to define custom chars (more than 8) as well as custom char banks where different combinations of custom characters can be easily loaded to LCD CGRAM
- Provide additional application for designing custom characters and generating C code ready to use with this library (copy-paste). [**HD44780 Custom Character Generator**](https://github.com/niwciu/HD44780_CHAR_GENERATOR)   
- Contain functions for displaying on LCD int values as a string representing:
  - int format 
  - hex format 
  - bin format
- The library has currently predefined following LCD types:
  - 1 line 8 characters (801)
  - 2 line 8 characters (802)
  - 2 lines 16 characters (1602)
  - 2 lines 20 characters (2002)
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

<div align="center">

***

![myEmbeddedWayBanerWhiteSmaller](https://github.com/user-attachments/assets/f4825882-e285-4e02-a75c-68fc86ff5716)
***
</div>