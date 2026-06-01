#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*
 * Scheduler behavior
 */

#define configUSE_PREEMPTION                    1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     1

/*
 * Clocking
 */

#define configCPU_CLOCK_HZ                      50000000
#define configSYSTICK_CLOCK_HZ                  configCPU_CLOCK_HZ
#define configTICK_RATE_HZ                      1000
#define configUSE_TICK_HOOK 0

/*
 * Tasking
 */

#define configMAX_PRIORITIES                    5
#define configMINIMAL_STACK_SIZE                128
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1

/*
 * Memory
 */

#define configTOTAL_HEAP_SIZE                   (8 * 1024)
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_MALLOC_FAILED_HOOK            0

/*
 * Synchronization
 */

#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               8

/*
 * Timers
 */

#define configUSE_TIMERS                        0

/*
 * Cortex-M interrupt priorities
 */

#define configPRIO_BITS                         3

#define configKERNEL_INTERRUPT_PRIORITY         0xE0
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    0xA0

/*
 * API inclusion
 */

#define INCLUDE_vTaskDelay                      1

/*
 * Disable optimized task selection
 * safer for current bring-up/debugging
 */

#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0

#endif
