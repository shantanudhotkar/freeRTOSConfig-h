#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Ensure stdint is only used by the compiler, not the assembler */
#ifndef __ASSEMBLER__
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

/*=============================================================================
 * HARDWARE — STM32F401CCU6 (Cortex-M4F, 84 MHz, 64 KB SRAM, 256 KB Flash)
 *===========================================================================*/
#define configCPU_CLOCK_HZ              ( ( uint32_t ) SystemCoreClock )

/*=============================================================================
 * SCHEDULER
 *===========================================================================*/
#define configUSE_PREEMPTION                        1
#define configUSE_TIME_SLICING                      1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION     1   /* Use CM4 CLZ instruction */
#define configUSE_TICKLESS_IDLE                     0

/*=============================================================================
 * TICK & PRIORITIES
 *===========================================================================*/
#define configTICK_RATE_HZ                          ( ( TickType_t ) 1000 )  /* 1 ms */
#define configMAX_PRIORITIES                        7U
#define configMINIMAL_STACK_SIZE                    ( ( uint16_t ) 128 )     /* words = 512 bytes */
#define configMAX_TASK_NAME_LEN                     16U
#define configTICK_TYPE_WIDTH_IN_BITS               TICK_TYPE_WIDTH_32_BITS
#define configIDLE_SHOULD_YIELD                     1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES       1U

/*=============================================================================
 * HEAP — heap_4.c
 * F401CCU6 = 64 KB SRAM. Reserve ~10 KB for stack + globals.
 *===========================================================================*/
#define configTOTAL_HEAP_SIZE                       ( ( size_t ) ( 20 * 1024 ) )
#define configSUPPORT_DYNAMIC_ALLOCATION            1
#define configSUPPORT_STATIC_ALLOCATION             0
#define configAPPLICATION_ALLOCATED_HEAP            0

/*=============================================================================
 * SOFTWARE TIMERS
 *===========================================================================*/
#define configUSE_TIMERS                            1
#define configTIMER_TASK_PRIORITY                   ( configMAX_PRIORITIES - 1U )
#define configTIMER_TASK_STACK_DEPTH                256U
#define configTIMER_QUEUE_LENGTH                    10U

/*=============================================================================
 * CORTEX-M4 INTERRUPT PRIORITY
 *
 * STM32F401 uses 4 priority bits → 16 levels (0 = highest, 15 = lowest).
 * FreeRTOS kernel runs at the LOWEST priority  → level 15 → register = 0xF0
 * Syscall barrier (FromISR safe level)         → level  5 → register = 0x50
 *
 * ⚠ Any ISR that calls a FreeRTOS API (FromISR variant) MUST have its
 *   NVIC priority set to 5 or HIGHER (numerically ≥ 5, NOT lower).
 *===========================================================================*/
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY     5

#define configKERNEL_INTERRUPT_PRIORITY     \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - 4 ) )          /* 0xF0 */

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - 4 ) )     /* 0x50 */

/* Alias required by some FreeRTOS versions */
#define configMAX_API_CALL_INTERRUPT_PRIORITY   configMAX_SYSCALL_INTERRUPT_PRIORITY

/*=============================================================================
 * HOOKS & SAFETY (enable all for development, tune for production)
 *===========================================================================*/
#define configUSE_IDLE_HOOK                         0
#define configUSE_TICK_HOOK                         0
#define configUSE_MALLOC_FAILED_HOOK                1   /* Trap heap exhaustion */
#define configUSE_DAEMON_TASK_STARTUP_HOOK          0
#define configCHECK_FOR_STACK_OVERFLOW              2   /* Method 2 = watermark pattern */

/* Hard assert — traps immediately on failure, set breakpoint here */
#define configASSERT( x )   \
    if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/*=============================================================================
 * MUTEXES, SEMAPHORES, QUEUES
 *===========================================================================*/
#define configUSE_MUTEXES                           1
#define configUSE_RECURSIVE_MUTEXES                 1
#define configUSE_COUNTING_SEMAPHORES               1
#define configUSE_QUEUE_SETS                        0
#define configQUEUE_REGISTRY_SIZE                   8U
#define configUSE_TASK_NOTIFICATIONS                1

/*=============================================================================
 * TRACE / STATS (disable in production to save flash/RAM)
 *===========================================================================*/
#define configUSE_TRACE_FACILITY                    1
#define configGENERATE_RUN_TIME_STATS               0
#define configUSE_STATS_FORMATTING_FUNCTIONS        0

/*=============================================================================
 * OPTIONAL FEATURES
 *===========================================================================*/
#define configUSE_NEWLIB_REENTRANT                  0
#define configENABLE_BACKWARD_COMPATIBILITY         0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS     0
#define configSTACK_DEPTH_TYPE                      uint16_t
#define configMESSAGE_BUFFER_LENGTH_TYPE            size_t

/*=============================================================================
 * INCLUDE (selectively enable FreeRTOS API functions)
 *===========================================================================*/
#define INCLUDE_vTaskDelay                          1
#define INCLUDE_vTaskDelayUntil                     1
#define INCLUDE_vTaskDelete                         1
#define INCLUDE_vTaskSuspend                        1
#define INCLUDE_xTaskGetCurrentTaskHandle           1
#define INCLUDE_xTaskGetSchedulerState              1
#define INCLUDE_xTaskGetIdleTaskHandle              1
#define INCLUDE_uxTaskGetStackHighWaterMark         1  /* needs configCHECK_FOR_STACK_OVERFLOW */
#define INCLUDE_uxTaskPriorityGet                   1
#define INCLUDE_vTaskPrioritySet                    1
#define INCLUDE_eTaskGetState                       1
#define INCLUDE_xTaskAbortDelay                     1
#define INCLUDE_xTaskResumeFromISR                  1
#define INCLUDE_xTimerPendFunctionCall              1
#define INCLUDE_xSemaphoreGetMutexHolder            1


#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
