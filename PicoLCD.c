#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/rand.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "LCD_Driver.h"

#define LCD_BRIGHTNESS 20

int main() {
    stdio_init_all();

    // init SPI at 8mhz
    spi_init(spi_default, 8 * 1000 * 1000);

    // TX + SCK
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI));

    // CS
    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    bi_decl(bi_1pin_with_name(PICO_DEFAULT_SPI_CSN_PIN, "SPI CS"));

    // DC + RST
    gpio_init(DEV_DC_PIN);
    gpio_init(DEV_RST_PIN);
    gpio_set_dir(DEV_DC_PIN, GPIO_OUT);
    gpio_set_dir(DEV_RST_PIN, GPIO_OUT);

    // BL
    gpio_set_function(DEV_BL_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(DEV_BL_PIN);
    pwm_set_wrap(slice_num, 255);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(DEV_BL_PIN), LCD_BRIGHTNESS);
    pwm_set_enabled(slice_num, true);

    //Init the LCD
    LCD_Init();

    while (1) {
        uint16_t random = (uint16_t)(get_rand_32() & 0xFFFF);
        LCD_Clear(random);
        sleep_ms(1000);
    }
}