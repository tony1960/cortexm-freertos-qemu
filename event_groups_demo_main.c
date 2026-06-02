#define SysTick_Handler xPortSysTickHandler
#define PendSV_Handler xPortPendSVHandler
#define SVC_Handler vPortSVCHandler

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "uart.h"

#define GPS_READY   (1 << 0)
#define IMU_READY   (1 << 1)
#define RADIO_READY (1 << 2)

EventGroupHandle_t system_events;

void startup_task(void *params)
{
    (void)params;

    uart_puts("Waiting for subsystems...\n");

    xEventGroupWaitBits(
        system_events,
        GPS_READY | IMU_READY | RADIO_READY,
        pdFALSE,     /* don't clear bits */
        pdTRUE,      /* wait for ALL bits */
        portMAX_DELAY
    );

    uart_puts("All subsystems ready!\n");

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void init_task(void *params)
{
    (void)params;

    vTaskDelay(pdMS_TO_TICKS(1000));
    uart_puts("GPS ready\n");
    xEventGroupSetBits(system_events, GPS_READY);

    vTaskDelay(pdMS_TO_TICKS(1000));
    uart_puts("IMU ready\n");
    xEventGroupSetBits(system_events, IMU_READY);

    vTaskDelay(pdMS_TO_TICKS(1000));
    uart_puts("RADIO ready\n");
    xEventGroupSetBits(system_events, RADIO_READY);

    while (1) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    }
    //vTaskDelete(NULL);
}

int main(void)
{
    uart_init();

    uart_puts("Event Group demo\n");

    system_events = xEventGroupCreate();

    xTaskCreate(
        startup_task,
        "Startup",
        256,
        0,
        2,
        0
    );

    xTaskCreate(
        init_task,
        "Init",
        256,
        0,
        1,
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
