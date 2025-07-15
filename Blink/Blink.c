#include <stdio.h>
#include "pico/stdlib.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 500
#endif

#define LED_PIN_22 22
#define LED_BOARD 25

// Perform initialisation
void pico_led_init(void) {
    gpio_init(LED_PIN_22);
    gpio_set_dir(LED_PIN_22, GPIO_OUT);
    gpio_init(LED_BOARD);
    gpio_set_dir(LED_BOARD, GPIO_OUT);
}

// Turn the led on or off
void pico_set_led(bool led_on) {
    gpio_put(LED_PIN_22, led_on);
    gpio_put(LED_BOARD, led_on);
}

int main() {
    pico_led_init();
    
    while (true) {
        pico_set_led(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led(false);
        sleep_ms(LED_DELAY_MS);
    }
}
