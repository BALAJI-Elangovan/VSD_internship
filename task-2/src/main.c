
#include "gpio.h"

int main(void)

{
       //Clock enable
    portD_clock_enable();
    // Configure PD6 as output push-pull
    gpio_cfg(6);
  
    while(1)
    {
       gpio_on(6); //GPIOD pin 6 On
        delay(1000); // 100 ms delay
       gpio_off(6);//GPIOD pin 6 Off
        delay(1000);// 100 ms delay
     }
}