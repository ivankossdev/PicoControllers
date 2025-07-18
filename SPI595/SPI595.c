#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17 // 12 | ST_CP | Storage Registet input
#define PIN_SCK  18 // 11 | SH_CP | Clock
#define PIN_MOSI 19 // 14 | DS    | Data pin

void spi_send_byte(spi_inst_t *spi, uint8_t data) {
    gpio_put(PIN_CS, 0); // Начать передачу
    spi_write_blocking(spi, &data, 1); // Отправить байт
    gpio_put(PIN_CS, 1); // Завершить передачу
}

int main()
{
    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi
    

    while (true) {
        spi_send_byte(SPI_PORT, 0x0f);
        sleep_ms(500);
        spi_send_byte(SPI_PORT, 0xf0);
        sleep_ms(500);
    }
}
