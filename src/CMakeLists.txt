cmake_minimum_required(VERSION 3.20)

add_library(lib_lcd_hd44780 STATIC
  ./lcd_hd44780_avr_specific.c  
  ./lcd_hd44780.c    
)

# set_target_properties(lib_lcd_hd44780 PROPERTIES OUTPUT_NAME "lib_lcd_hd44780")
set_target_properties(lib_lcd_hd44780 PROPERTIES 
  OUTPUT_NAME "lib_lcd_hd44780"
  PREFIX ""
  )

target_include_directories(lib_lcd_hd44780 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
