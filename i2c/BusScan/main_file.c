#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "gpio_used.h"
#include "Maze_Solver.h"
#include "pico_i2c.h"


int main()
{
    stdio_init_all();

    /* Initialize the i2c Bus */
    pico_i2c_init(I2C_PORT, I2C_BUS1_SDA_PIN, I2C_BUS1_SCL_PIN, I2C_BUS1_FREQ);

    /* Initialize the pins that are being used for all ops including i2c */
    gpio_init(PIN_GPIO_25);

    gpio_set_dir(PIN_GPIO_15,GPIO_OUT);
    gpio_set_dir(PIN_GPIO_25,GPIO_OUT);
    gpio_set_dir(PIN_GPIO_01,GPIO_OUT);
    while (true) {
        /* Gave a dummy output to a Led just to track if the bus scan has completed or not */
        gpio_put(PIN_GPIO_15,1);
        /* The main function call for scanning the bus */
        pico_i2c_scan_bus();
        /*  gpio_put(PIN_GPIO_25, 1); */
        gpio_put(PIN_GPIO_15,0);
        /* Wait 1-second before trying again, as this helps you in reading the message written to the UART Monitor, avoids constant message at console. */
        sleep_ms(1000);
        /*  gpio_put(PIN_GPIO_25, 0); */
    }
}
