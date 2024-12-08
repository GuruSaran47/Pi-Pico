
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#ifdef DEBUG
#include  <stdio.h>
#endif

/*

*/
static uint16_t pwm_to_angle(uint16_t pwm){
    int ret_angle = 0;
    ret_angle = ((pwm * 9)/95) - (900/19);
    uint16_t actual_ret = ret_angle;
#ifdef DEBUG
    printf("%u\n",actual_ret);
#endif
    return actual_ret;
}

static uint16_t angle_to_pwm(int angle){
    uint16_t ret_pwm = 0;
    int pwm = 0;
    pwm = ((angle*95)/9)+500;
    ret_pwm = pwm;
#ifdef DEBUG
    printf("%u\n",ret_pwm);
#endif
    return ret_pwm;
}

static void set_millis(int servo_pin, float millis){
    uint16_t level = (millis/20000.f)*39062.f;
    pwm_set_gpio_level(servo_pin,level);
}

void set_servo(int servo_pin,int angle){
    gpio_set_function(servo_pin,GPIO_FUNC_PWM);
    uint8_t slice_num = pwm_gpio_to_slice_num(servo_pin);
    pwm_config conf = pwm_get_default_config();

    pwm_config_set_clkdiv(&conf,64.f);
    pwm_config_set_wrap(&conf,39062.f);

    pwm_init(slice_num,&conf,true);

    set_millis(servo_pin,angle_to_pwm(angle));
}

