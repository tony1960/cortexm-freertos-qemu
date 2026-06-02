#define SysTick_Handler xPortSysTickHandler
#define PendSV_Handler xPortPendSVHandler
#define SVC_Handler vPortSVCHandler

#include "FreeRTOS.h"
#include "task.h"

#include "uart.h"

void worker_task(void *params)
{
    (void)params;

    while (1) {

        uart_puts("Worker running\n");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    uart_init();

    uart_puts("Starting simple task demo\n");

    xTaskCreate(
        worker_task,
        "Worker",
        256,
        0,
        2,
        0
    );

    vTaskStartScheduler();

    while (1) {
    }
}

void *memset(void *s, int c, unsigned int n)
{
    unsigned char *p = s;

    while (n--) {
        *p++ = (unsigned char)c;
    }

    return s;
}

void *memcpy(void *dest, const void *src, unsigned int n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;

    while (n--) {
        *d++ = *s++;
    }

    return dest;
}
