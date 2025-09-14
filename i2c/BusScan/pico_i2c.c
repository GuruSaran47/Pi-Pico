#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico_i2c.h"


/* The variables that store the global level variables */

st_i2c_bus_characteristics gst_i2c_bus = {0x00,};

static uint8_t gsu8_devices_on_bus = 0x00u;
/*
*   Function Name: pico_i2c_scan_bus(void)
*   Description: Scans the bus and then prints the address of the devices connected to the bus.
*   Parameters: None
*   Return: None
*/

void pico_i2c_scan_bus(void)
{
    /* 
    
    This function is used to scan the i2c bus, the workflow is that:
    we use a function for writing to a slave device, the addresses of the range 0x00 to 0x7F as i2c uses the addressing of 7-Bits.
    each time we write with the function responds

    */

    for(uint8_t address = 0x08u;address<=0x77u; address++)
    {   
        uint8_t *dest_buffer = (uint8_t*)malloc(sizeof(uint8_t)*0x10u);
        /* here we check the responses of each time we call the i2c interface */
        int read_result_value = i2c_read_blocking(I2C_PORT,address,NULL,1,false);
        /* 
        if the return_value is true this means that we will get a return value equal to the len if everything is successful.
        This fundamentally means that everything was successful.

        But if you are reading something which shows that the device exists on the bus, then you get something >=0

        In the case of the NACK Error: Where the target address is not found, then we get a neagative number
        */

        if(read_result_value>=0x00)
        {
            printf("Devices of Address: 0x%x aka. %d is found.%d\n",address,address,read_result_value);
            gsu8_devices_on_bus++;
        }
        else
        {
            /* Do Nothing */
        }
        
    }
    if(gsu8_devices_on_bus == 0x00)
    {
        /* printf("-------------No devices Connected on the Bus------------\n"); */
    }
    else
    {
        printf("----------------------%d Devices Found------------------------\n",gsu8_devices_on_bus);
    }

    /* Reset the global counter. */
    gsu8_devices_on_bus = 0x00u;
}

/*
*   Function Name: pico_print_bus_parameters
*   Description: Print all the i2c parameters of the bus.
*   Parameters: None
*   Return: None
*/
void pico_print_bus_parameters(void)
{
    printf("I2C Port: %p \n", (void*)gst_i2c_bus.st_i2c_port);
    printf("SDA Pin: %u \n", gst_i2c_bus.st_u8_SDA_Pin);
    printf("SCL Pin: %u \n", gst_i2c_bus.st_u8_SCL_Pin);
    printf("Frequency: %u \n", gst_i2c_bus.st_u32_Frequency);
}

/*
*   Function Name: pico_i2c_populate_bus_parameteres
*   Description: Populate I2C port parameters to the global structure.
*   Parameters: 1-> pointer to the i2c_port, 2-> SDA pin number, 3-> SCL pin number, 4-> Frequency
*   Return: None
*/
static void pico_i2c_populate_bus_parameters(i2c_inst_t *ast_i2c_port, uint8_t *apu8_SDA_Pin, uint8_t *apu8_SCL_Pin, uint32_t *apu32_Frequecy)
{
    gst_i2c_bus.st_i2c_port = ast_i2c_port;
    gst_i2c_bus.st_u8_SDA_Pin = apu8_SDA_Pin[0u];
    gst_i2c_bus.st_u8_SCL_Pin = apu8_SCL_Pin[0u];
    gst_i2c_bus.st_u32_Frequency = apu32_Frequecy[0u];

    /* Call will be done only ones, so that the parameters are printed ones */
    pico_print_bus_parameters();
}

/*
*   Function Name: pico_i2c_init
*   Description: Initialize I2C port based on the given parameters.
*   Parameters: 1-> pointer to the i2c_port, 2-> SDA pin number, 3-> SCL pin number, 4-> Frequency
*   Return: None
*/
void pico_i2c_init(i2c_inst_t *ast_i2c_port, uint8_t au8_SDA_Pin, uint8_t au8_SCL_Pin, uint32_t au32_Frequency)
{
    i2c_init(ast_i2c_port, au32_Frequency);
    /* Set the function to the  */
    gpio_set_function(au8_SDA_Pin, GPIO_FUNC_I2C);
    gpio_set_function(au8_SCL_Pin, GPIO_FUNC_I2C);

    pico_i2c_populate_bus_parameters(ast_i2c_port, &au8_SDA_Pin, &au8_SCL_Pin, &au32_Frequency);
}

