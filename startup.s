.syntax unified
.cpu cortex-m3
.thumb

.global _estack
.global Reset_Handler
.global Default_Handler
.global HardFault_Handler

.extern main

.extern xPortPendSVHandler
.extern xPortSysTickHandler
.extern vPortSVCHandler

/*
 * Alias FreeRTOS handlers directly.
 * IMPORTANT:
 * These are symbol aliases only.
 * No executable trampoline code is emitted.
 */

.set PendSV_Handler, xPortPendSVHandler
.set SysTick_Handler, xPortSysTickHandler
.set SVC_Handler, vPortSVCHandler

/*
 * Vector table
 */

.section .isr_vector, "a", %progbits

.word _estack
.word Reset_Handler
.word Default_Handler     /* NMI */
.word HardFault_Handler   /* HardFault */
.word Default_Handler     /* MemManage */
.word Default_Handler     /* BusFault */
.word Default_Handler     /* UsageFault */
.word 0
.word 0
.word 0
.word 0
.word SVC_Handler
.word Default_Handler     /* DebugMon */
.word 0
.word PendSV_Handler
.word SysTick_Handler

/*
 * Reset handler
 */

.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    bl main

reset_loop:
    b reset_loop

/*
 * Default interrupt handler
 */

.section .text.Default_Handler
.type Default_Handler, %function

Default_Handler:
default_loop:
    b default_loop

/*
 * HardFault handler
 */

.section .text.HardFault_Handler
.type HardFault_Handler, %function

HardFault_Handler:
hardfault_loop:
    b hardfault_loop
