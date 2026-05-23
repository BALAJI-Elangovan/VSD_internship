#include "pwm.h"
int main(void)
{
    uint16_t duty = 0;

    pwm_init();

    PWM_Start();

    while(1)
    {
        PWM_SetDuty(duty);

        duty += 100;

        if(duty > 1000)
        {
            duty = 0;
        }

        delay_ms(500);
    }
}