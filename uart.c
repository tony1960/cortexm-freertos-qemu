#include "uart.h"

/* System control */
#define SYSCTL_RCGC1_R      (*((volatile uint32_t *)0x400FE104))
#define SYSCTL_RCGC2_R      (*((volatile uint32_t *)0x400FE108))

/* GPIOA */
#define GPIO_PORTA_AFSEL_R  (*((volatile uint32_t *)0x40004420))
#define GPIO_PORTA_DEN_R    (*((volatile uint32_t *)0x4000451C))
#define GPIO_PORTA_PCTL_R   (*((volatile uint32_t *)0x4000452C))
#define GPIO_PORTA_AMSEL_R  (*((volatile uint32_t *)0x40004528))

/* UART0 */
#define UART0_DR_R          (*((volatile uint32_t *)0x4000C000))
#define UART0_FR_R          (*((volatile uint32_t *)0x4000C018))
#define UART0_IBRD_R        (*((volatile uint32_t *)0x4000C024))
#define UART0_FBRD_R        (*((volatile uint32_t *)0x4000C028))
#define UART0_LCRH_R        (*((volatile uint32_t *)0x4000C02C))
#define UART0_CTL_R         (*((volatile uint32_t *)0x4000C030))

/* Flag register bits */
#define UART_FR_TXFF        (1U << 5)   /* TX FIFO full */
#define UART_FR_RXFE        (1U << 4)   /* RX FIFO empty */

/* Control bits */
#define UART_CTL_UARTEN     (1U << 0)
#define UART_CTL_TXE        (1U << 8)
#define UART_CTL_RXE        (1U << 9)

/* Line control */
#define UART_LCRH_WLEN_8    (0x3U << 5)
#define UART_LCRH_FEN       (1U << 4)
void uart_isr(void)
{
    /* unused for this SPI test */
}
void uart_init(void)
{
    /* Enable UART0 and GPIOA clocks */
    SYSCTL_RCGC1_R |= (1U << 0);   /* UART0 */
    SYSCTL_RCGC2_R |= (1U << 0);   /* GPIOA */
    (void)SYSCTL_RCGC2_R;

    /* Disable UART before config */
    UART0_CTL_R = 0;

    /*
     * Baud rate setup
     * These values work well in QEMU for 115200-ish behavior
     */
    UART0_IBRD_R = 4;
    UART0_FBRD_R = 22;

    /* 8-bit, no parity, FIFO enabled */
    UART0_LCRH_R = UART_LCRH_WLEN_8 | UART_LCRH_FEN;

    /* Configure PA0 (RX), PA1 (TX) */
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_DEN_R   |= 0x03;
    GPIO_PORTA_AMSEL_R &= ~0x03;

    GPIO_PORTA_PCTL_R &= ~0x000000FF;
    GPIO_PORTA_PCTL_R |=  0x00000011;

    /* Enable UART */
    UART0_CTL_R = UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;
}

void uart_putc(char c)
{
    while (UART0_FR_R & UART_FR_TXFF) {
    }

    UART0_DR_R = (uint32_t)c;
}

void uart_puts(const char *s)
{
    while (*s) {
        if (*s == '\n') {
            uart_putc('\r');
        }
        uart_putc(*s++);
    }
}

char uart_getc(void)
{
    while (UART0_FR_R & UART_FR_RXFE) {
    }

    return (char)(UART0_DR_R & 0xFF);
}
