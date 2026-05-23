#include "pwm.h"
#define pwm_period 1000
// RCC APB2 address
#define RCC_APB2PCENR    (*(volatile uint32_t*)0x40021018) 
//GPIOD address
#define GPIOD_CFGLR      (*(volatile uint32_t*)0x40011400) 
//TIM1 reg_address
#define TIM1_CTLR1       (*(volatile uint32_t*)0x40012C00) // Control register 1
#define TIM1_CTLR2       (*(volatile uint32_t*)0x40012C04) // Control register 2 
#define TIM1_SMCFGR      (*(volatile uint32_t*)0x40012C08) // Slave mode control register 
#define TIM1_DMAINTENR   (*(volatile uint32_t*)0x40012C0C) // DMA/interrupt enable register 
#define TIM1_INTFR       (*(volatile uint32_t*)0x40012C10) // Interrupt status register 
#define TIM1_SWEVGR      (*(volatile uint32_t*)0x40012C14) // Event generation register
#define TIM1_CHCTLR1     (*(volatile uint32_t*)0x40012C18) // Compare/capture control register 1 
#define TIM1_CHCTLR2     (*(volatile uint32_t*)0x40012C1C) // Compare/capture control register 2 
#define TIM1_CCER        (*(volatile uint32_t*)0x40012C20) // Compare/capture enable register 
#define TIM1_CNT         (*(volatile uint32_t*)0x40012C24) // Counters
#define TIM1_PSC         (*(volatile uint32_t*)0x40012C28) // Counting clock prescaler
#define TIM1_ATRLR       (*(volatile uint32_t*)0x40012C2C) // Auto-reload value register
#define TIM1_RPTCR       (*(volatile uint32_t*)0x40012C30) // Recurring count value register
#define TIM1_CH1CVR      (*(volatile uint32_t*)0x40012C34) // Compare/capture register 1 
#define TIM1_CH2CVR      (*(volatile uint32_t*)0x40012C38) // Compare/capture register 2
#define TIM1_CH3CVR      (*(volatile uint32_t*)0x40012C3C) // Compare/capture register 3
#define TIM1_CH4CVR      (*(volatile uint32_t*)0x40012C40) // Compare/capture register 4 
#define TIM1_BDTR        (*(volatile uint32_t*)0x40012C44) // Brake and deadband registers 
#define TIM1_DMACFGR     (*(volatile uint32_t*)0x40012C48) // DMA control register 
#define TIM1_DMAADR      (*(volatile uint32_t*)0x40012C4C) // DMA address register for continuous mode 

//PWM configuration

#define PWM_PERIOD       1000


void pwm_init()
{
    //Enabling Clock
    RCC_APB2PCENR |= (1<<5);//Enabling GPIOD
    RCC_APB2PCENR |= (1<<11);//Enabling USART1 

    //Enabling Alternate Function I/P
    GPIOD_CFGLR &= ~(0xF << 8);
    GPIOD_CFGLR |=  (0xB << 8);//PD2 as Alternate Function Push-Pull Output

    //Timer1 Configuration
    TIM1_PSC = (48000000 / 1000000) - 1;
    TIM1_ATRLR = PWM_PERIOD-1;
    TIM1_CNT = 0;
    TIM1_CHCTLR1 &= ~(0XFF);
    TIM1_CHCTLR1 |=  (6<<4);//Compare capture mode enable
    TIM1_CHCTLR1 |=  (1<<3);//Enabling preload register

    //Enabling Channel1
    TIM1_CCER |= (1 << 0);//enabling channel 1

    //initial Duty Cycle
    TIM1_CH1CVR = 0;

    //Main O/P Enable
    TIM1_BDTR |= (1<<15);

    //Auto reload register
    TIM1_CTLR1 |= (1<<7);

}

void PWM_SetDuty(uint16_t duty)
{
    if(duty > PWM_PERIOD)
        duty = PWM_PERIOD;

    TIM1_CH1CVR = duty;
}

void PWM_Start(void)
{
    TIM1_CTLR1 |= (1 << 0);
}

void PWM_Stop(void)
{
    TIM1_CTLR1 &= ~(1 << 0);
}

void delay_ms(uint32_t ms)
{
    volatile uint32_t i;

    while(ms--)
    {
        for(i = 0; i < 8000; i++);
    }
}