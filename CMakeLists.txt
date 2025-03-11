cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(picolcd)

pico_sdk_init()

add_executable(picolcd
	PicoLCD.c
	LCD_Driver.c
)

target_link_libraries(picolcd pico_stdlib pico_rand hardware_spi hardware_pwm)

pico_add_extra_outputs(picolcd)
