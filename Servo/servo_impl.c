#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "servo.h"

int main()
{   
    stdio_init_all();
    uint8_t servo_pin = 28;
    uint8_t direction = 0; /* Your Angle */
    while(true){
        direction++;
        set_servo(servo_pin,direction);
        direction = (direction>=180)?0:direction;
        printf("%d\n",direction);
        sleep_ms(200);
    }        
}
