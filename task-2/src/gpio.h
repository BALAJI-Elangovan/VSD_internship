#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
#include<stdio.h>
/* RCC */
#define RCC_APB2PCENR  (*(volatile uint32_t*)0x40021018)
#define IOPDEN          (1 << 5)
#define USART1_EN       (1 << 14)

/* GPIOD */
#define GPIOD_CFGLR    (*(volatile uint32_t*)0x40011400)
#define GPIOD_BSHR     (*(volatile uint32_t*)0x40011410)

/* USART1 base = 0x40010800 */
#define USART_STATR    (*(volatile uint32_t*)0x40010800)
#define USART_DATAR    (*(volatile uint32_t*)0x40010804)
#define USART_BRR      (*(volatile uint32_t*)0x40010808)
#define USART_CTLR1    (*(volatile uint32_t*)0x4001080C)

/* GPIO output mode: push-pull 50MHz = 0x3 */
#define PIN_OUTPUT_MODE(n)  (0x3 << ((n)*4))

void delay(uint32_t n);
void portD_clock_enable(void);
void gpio_cfg(uint32_t n);
void gpio_on(uint32_t n);
void gpio_off(uint32_t n);
void uart_init(void);
void uart_tx(char c);
void uart_print(char *str);

#endif /* GPIO_H */