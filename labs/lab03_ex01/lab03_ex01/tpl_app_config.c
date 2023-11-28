/**
 * @file tpl_app_config.c
 *
 * @section desc File description
 *
 * OS data structure generated from application RM_scheduler
 * Automatically generated by goil on Www Mmm dd hh:mm:ss yyyy
 * from root OIL file lab03_ex01.oil
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include <stdbool.h>
#include <stdint.h>

#include "tpl_app_config.h"

#include "tpl_os_internal_types.h"
#include "tpl_machine.h"
#include "tpl_os_interrupt.h"
#include "tpl_os_interrupt_kernel.h"
#include "tpl_os_alarm_kernel.h"
#include "tpl_os_alarm.h"
#include "tpl_os_resource_kernel.h"
#include "tpl_os_resource.h"
#include "tpl_os_event_kernel.h"
#include "tpl_os_event.h"
#include "tpl_os_action.h"
#include "tpl_os_kernel.h"
#include "tpl_os_definitions.h"


/*=============================================================================
 * Application Modes tables for tasks, alarms and schedule tables
 * Application Modes masks are as follow:
 * stdAppmode = 1
 */

CONST(tpl_application_mode, OS_CONST) stdAppmode = 0; /* mask = 1 */
CONST(tpl_application_mode, OS_CONST) OSDEFAULTAPPMODE = 0;
CONST(tpl_appmode_mask, OS_CONST) tpl_task_app_mode[TASK_COUNT] = {
  1 /* task TaskC : stdAppmode */ ,
  1 /* task TaskB : stdAppmode */ ,
  1 /* task TaskA : stdAppmode */ 
};

CONST(tpl_appmode_mask, OS_CONST) tpl_alarm_app_mode[ALARM_COUNT] = {
  1 /* alarm alarmA : stdAppmode */ ,
  1 /* alarm alarmB : stdAppmode */ ,
  1 /* alarm alarmC : stdAppmode */ 
};

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of processes IDs
 */

/* Task TaskC identifier */
#define TaskC_id 0
CONST(TaskType, AUTOMATIC) TaskC = TaskC_id;

/* Task TaskB identifier */
#define TaskB_id 1
CONST(TaskType, AUTOMATIC) TaskB = TaskB_id;

/* Task TaskA identifier */
#define TaskA_id 2
CONST(TaskType, AUTOMATIC) TaskA = TaskA_id;

/*=============================================================================
 * Declaration of Alarm IDs
 */

/* Alarm alarmA identifier */
#define alarmA_id 0
CONST(AlarmType, AUTOMATIC) alarmA = alarmA_id;

/* Alarm alarmB identifier */
#define alarmB_id 1
CONST(AlarmType, AUTOMATIC) alarmB = alarmB_id;

/* Alarm alarmC identifier */
#define alarmC_id 2
CONST(AlarmType, AUTOMATIC) alarmC = alarmC_id;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * The scheduler resource descriptor.
 * One scheduler resource is defined per core.
 *
 * @see #RES_SCHEDULER
 */

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
VAR(tpl_resource, OS_VAR) res_sched_rez_desc = {
  RES_SCHEDULER_PRIORITY,   /*  ceiling priority                            */
  0,                        /*  owner_prev_priority                         */
  INVALID_PROC_ID,          /*  owner                                       */
#if WITH_OSAPPLICATION == YES
  INVALID_OSAPPLICATION_ID, /*  OS Application id                           */
#endif

  NULL                      /*  next_res                                    */
};
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_resource, AUTOMATIC, OS_APPL_DATA)
tpl_resource_table[RESOURCE_COUNT] = {
  &res_sched_rez_desc
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of Counters related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Counter SystemCounter descriptor
 */

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_tick, OS_CONST) OSTICKSPERBASE = 1;
CONST(tpl_tick, OS_CONST) OSMAXALLOWEDVALUE = 65535;
CONST(tpl_tick, OS_CONST) OSMINCYCLE = 1;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_counter, OS_VAR) SystemCounter_counter_desc = {
  /* ticks per base       */  1,
  /* max allowed value    */  65535,
  /* minimum cycle        */  1,
  /* current tick         */  0,
  /* current date         */  0,
#if WITH_OSAPPLICATION == YES
    /* OS Application id    */  
#endif
    /* first alarm          */  NULL_PTR,
    /* next alarm to raise  */  NULL_PTR
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#include "tpl_os_kernel.h"          /* tpl_schedule */
#include "tpl_os_timeobj_kernel.h"  /* tpl_counter_tick */
#include "tpl_machine_interface.h"  /* tpl_switch_context_from_it */

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

//gcc uses ISR as a keyword to define an interrupt handler.
//Osek uses ISR to define an ISR2 :-/
#ifdef ISR
 #undef ISR
#endif
#include <avr/interrupt.h>

//function defined in avr assembly files.
FUNC(void, OS_CODE) tpl_avr_counter_tick(
    P2VAR(tpl_counter, AUTOMATIC, OS_APPL_DATA) counter);


void trampolineSystemCounter()
{
  tpl_avr_counter_tick(&SystemCounter_counter_desc);
}
  
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*=============================================================================
 * Descriptor(s) of the idle task(s)
 */
/*-----------------------------------------------------------------------------
 * Task IDLE_TASK descriptor
 */
#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task IDLE_TASK function prototype
 */

FUNC(void, OS_APPL_CODE) idle_function(void);
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task IDLE_TASK stack
 *
 */
#define APP_Task_IDLE_TASK_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word IDLE_TASK_stack_zone[IDLE_STACK_SIZE/sizeof(tpl_stack_word)];
#define APP_Task_IDLE_TASK_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define IDLE_TASK_STACK { IDLE_TASK_stack_zone, IDLE_STACK_SIZE }

/*
 * Task IDLE_TASK context
 */
avr_context IDLE_TASK_int_context;
#define IDLE_TASK_CONTEXT &IDLE_TASK_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task IDLE_TASK
 */
CONST(tpl_proc_static, OS_CONST) IDLE_TASK_task_stat_desc = {
  /* context                  */  IDLE_TASK_CONTEXT,
  /* stack                    */  IDLE_TASK_STACK,
  /* entry point (function)   */  idle_function,
  /* internal ressource       */  NULL,
  /* task id                  */  IDLE_TASK_ID,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  0,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task IDLE_TASK
 */
VAR(tpl_proc, OS_VAR) IDLE_TASK_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  0,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Task related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Task TaskC descriptor
 */
#define APP_Task_TaskC_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task TaskC function prototype
 */

FUNC(void, OS_APPL_CODE) TaskC_function(void);
#define APP_Task_TaskC_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task TaskC stack
 *
 */
#define APP_Task_TaskC_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word TaskC_stack_zone[256/sizeof(tpl_stack_word)];
#define APP_Task_TaskC_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define TaskC_STACK { TaskC_stack_zone, 256 }

/*
 * Task TaskC context
 */
avr_context TaskC_int_context;
#define TaskC_CONTEXT &TaskC_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task TaskC
 */
CONST(tpl_proc_static, OS_CONST) TaskC_task_stat_desc = {
  /* context                  */  TaskC_CONTEXT,
  /* stack                    */  TaskC_STACK,
  /* entry point (function)   */  TaskC_function,
  /* internal ressource       */  NULL,
  /* task id                  */  TaskC_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task TaskC
 */
VAR(tpl_proc, OS_VAR) TaskC_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task TaskB descriptor
 */
#define APP_Task_TaskB_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task TaskB function prototype
 */

FUNC(void, OS_APPL_CODE) TaskB_function(void);
#define APP_Task_TaskB_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task TaskB stack
 *
 */
#define APP_Task_TaskB_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word TaskB_stack_zone[256/sizeof(tpl_stack_word)];
#define APP_Task_TaskB_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define TaskB_STACK { TaskB_stack_zone, 256 }

/*
 * Task TaskB context
 */
avr_context TaskB_int_context;
#define TaskB_CONTEXT &TaskB_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task TaskB
 */
CONST(tpl_proc_static, OS_CONST) TaskB_task_stat_desc = {
  /* context                  */  TaskB_CONTEXT,
  /* stack                    */  TaskB_STACK,
  /* entry point (function)   */  TaskB_function,
  /* internal ressource       */  NULL,
  /* task id                  */  TaskB_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  2,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task TaskB
 */
VAR(tpl_proc, OS_VAR) TaskB_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  2,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task TaskA descriptor
 */
#define APP_Task_TaskA_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task TaskA function prototype
 */

FUNC(void, OS_APPL_CODE) TaskA_function(void);
#define APP_Task_TaskA_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task TaskA stack
 *
 */
#define APP_Task_TaskA_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word TaskA_stack_zone[256/sizeof(tpl_stack_word)];
#define APP_Task_TaskA_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define TaskA_STACK { TaskA_stack_zone, 256 }

/*
 * Task TaskA context
 */
avr_context TaskA_int_context;
#define TaskA_CONTEXT &TaskA_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task TaskA
 */
CONST(tpl_proc_static, OS_CONST) TaskA_task_stat_desc = {
  /* context                  */  TaskA_CONTEXT,
  /* stack                    */  TaskA_STACK,
  /* entry point (function)   */  TaskA_function,
  /* internal ressource       */  NULL,
  /* task id                  */  TaskA_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  3,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task TaskA
 */
VAR(tpl_proc, OS_VAR) TaskA_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  3,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#include "tpl_machine.h"
#define OS_START_SEC_CODE
#include "tpl_memmap.h"

//function defined in avr assembly files.
FUNC(void, OS_CODE) tpl_avr_ISR2_handler(CONST(uint16, AUTOMATIC) id);


#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*=============================================================================
 * Definition and initialization of process tables (tasks and isrs)
 */
CONSTP2CONST(tpl_proc_static, AUTOMATIC, OS_APPL_DATA)
tpl_stat_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &TaskC_task_stat_desc,
  &TaskB_task_stat_desc,
  &TaskA_task_stat_desc,
  &IDLE_TASK_task_stat_desc
};

CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA)
tpl_dyn_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &TaskC_task_desc,
  &TaskB_task_desc,
  &TaskA_task_desc,
  &IDLE_TASK_task_desc
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Alarm related structures
 */
/*-----------------------------------------------------------------------------
 * Alarm alarmA descriptor
 *
 * This alarm does the activation of task TaskA
 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) alarmA_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  TaskA_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
 
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_alarm_static, OS_CONST) alarmA_static = {
  {
    /* pointer to counter           */  &SystemCounter_counter_desc,
    /* pointer to the expiration    */  tpl_raise_alarm
#if (WITH_ID == YES)
    /* id of the alarm for tracing  */  , alarmA_id
#endif
#if WITH_OSAPPLICATION == YES
    /* OS application id            */  , 
#endif
  },
  /* action of the alarm  */  (tpl_action *)&alarmA_action
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_time_obj, OS_VAR) alarmA_alarm_desc = {
    /* pointer to the static part   */  (tpl_time_obj_static *)&alarmA_static,
    /* next alarm                   */  NULL,
    /* prev alarm                   */  NULL,
    /* cycle                        */  1172,
    /* date                         */  1172,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Alarm alarmB descriptor
 *
 * This alarm does the activation of task TaskB
 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) alarmB_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  TaskB_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
 
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_alarm_static, OS_CONST) alarmB_static = {
  {
    /* pointer to counter           */  &SystemCounter_counter_desc,
    /* pointer to the expiration    */  tpl_raise_alarm
#if (WITH_ID == YES)
    /* id of the alarm for tracing  */  , alarmB_id
#endif
#if WITH_OSAPPLICATION == YES
    /* OS application id            */  , 
#endif
  },
  /* action of the alarm  */  (tpl_action *)&alarmB_action
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_time_obj, OS_VAR) alarmB_alarm_desc = {
    /* pointer to the static part   */  (tpl_time_obj_static *)&alarmB_static,
    /* next alarm                   */  NULL,
    /* prev alarm                   */  NULL,
    /* cycle                        */  1954,
    /* date                         */  1954,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Alarm alarmC descriptor
 *
 * This alarm does the activation of task TaskC
 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) alarmC_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  TaskC_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
 
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_alarm_static, OS_CONST) alarmC_static = {
  {
    /* pointer to counter           */  &SystemCounter_counter_desc,
    /* pointer to the expiration    */  tpl_raise_alarm
#if (WITH_ID == YES)
    /* id of the alarm for tracing  */  , alarmC_id
#endif
#if WITH_OSAPPLICATION == YES
    /* OS application id            */  , 
#endif
  },
  /* action of the alarm  */  (tpl_action *)&alarmC_action
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_time_obj, OS_VAR) alarmC_alarm_desc = {
    /* pointer to the static part   */  (tpl_time_obj_static *)&alarmC_static,
    /* next alarm                   */  NULL,
    /* prev alarm                   */  NULL,
    /* cycle                        */  2930,
    /* date                         */  2930,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA)
  tpl_alarm_table[ALARM_COUNT] = {
  &alarmA_alarm_desc,
  &alarmB_alarm_desc,
  &alarmC_alarm_desc
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of flags functions
 */
/* $FLAGSFUNCTIONS$ */

/*=============================================================================
 * Definition and initialization of Ready List structures
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_heap_entry, OS_VAR) tpl_ready_list[5];
VAR(tpl_rank_count, OS_VAR) tpl_tail_for_prio[5] = {
  0,
  0,
  0,
  0
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * @internal
 *
 * tpl_kern gather informations on the current executing object and
 * the previous one
 */
VAR(tpl_kern_state, OS_VAR) tpl_kern =
{
  NULL,                      /* no running task static descriptor   */
  &IDLE_TASK_task_stat_desc, /* elected task to run is idle task    */
  NULL,                      /* no running task dynamic descriptor  */
  &IDLE_TASK_task_desc,      /* elected task to run is idle task    */
  INVALID_PROC_ID,           /* no running task so no ID            */
  INVALID_PROC_ID,           /* idle task has no ID                 */
  NO_NEED_SWITCH,            /* no context switch needed at start   */
  FALSE,                     /* no schedule needed at start         */
#if WITH_MEMORY_PROTECTION == YES
  1,                         /* at early system startup, we run in  */
                             /*  kernel mode, so in trusted mode    */
#endif /* WITH_MEMORY_PROTECTION */
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2CONST(char, AUTOMATIC, OS_APPL_DATA) proc_name_table[TASK_COUNT + ISR_COUNT + 1] = {

  "TaskC",
  "TaskB",
  "TaskA",
  "*idle*"
};
#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/* End of file tpl_app_config.c */
