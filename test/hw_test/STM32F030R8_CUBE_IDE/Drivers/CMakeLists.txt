cmake_minimum_required(VERSION 3.20)

set(HAL_LL_LIB_INC
  ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F0xx/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/STM32F0xx_HAL_Driver/Inc
)

add_library(lib_hal_ll_drivers STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_exti.c
  ${CMAKE_CURRENT_SOURCE_DIR}/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_gpio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_pwr.c
  ${CMAKE_CURRENT_SOURCE_DIR}/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rcc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_utils.c
)

set_target_properties(lib_hal_ll_drivers PROPERTIES 
  OUTPUT_NAME "lib_hal_ll_drivers"
  PREFIX ""
  )

target_include_directories(lib_hal_ll_drivers PUBLIC ${HAL_LL_LIB_INC})
