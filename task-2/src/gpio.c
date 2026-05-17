#include "gpio.h"

void delay(uint32_t n)
{
    for(volatile uint32_t i = 0; i < n * 1000; i++);
}

void portD_clock_enable(void)
{
    RCC_APB2PCENR |= IOPDEN;
}

void gpio_cfg(uint32_t n)
{
    GPIOD_CFGLR &= ~(0xF << (n * 4));
    GPIOD_CFGLR |= PIN_OUTPUT_MODE(n);
}

void gpio_on(uint32_t n)
{
    GPIOD_BSHR = (1 << n);
}

void gpio_off(uint32_t n)
{
    GPIOD_BSHR = (1 << (n + 16));
}

void uart_init(void)
{
    /* 1. Enable GPIOD + USART1 clocks */
    RCC_APB2PCENR |= IOPDEN | USART1_EN;

    /* 2. PD5 = AF push-pull 50MHz (bits 23:20 = 0b1011) */
    GPIOD_CFGLR &= ~(0x0F << 20);
    GPIOD_CFGLR |=  (0x0B << 20);

    /* 3. Baud rate: 48MHz / 115200 = 417 */
    USART_BRR = 417;

    /* 4. Clear CTLR1, then enable TX + USART */
    USART_CTLR1 = 0;
    USART_CTLR1 |= (1 << 3);   /* TE: transmitter enable */
    USART_CTLR1 |= (1 << 13);  /* UE: USART enable */
}

void uart_tx(char c)
{
    /* Wait until TXE (bit 7) is set = data register empty */
    while (!(USART_STATR & (1 << 7)));
    USART_DATAR = c;
}

void uart_print(char *str)
{
    while (*str)
    {
        uart_tx(*str++);
    }
}