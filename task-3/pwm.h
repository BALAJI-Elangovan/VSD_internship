#ifndef PWM_H
#define pWM_H
#include<stdint.h>
void pwm_init(void);
void pwm_duty(uint16_t duty);
void pwm_start(void);
void pwm_stop(void);
#endif