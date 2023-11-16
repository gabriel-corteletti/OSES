/**
 * @file tpl_app_config.c
 *
 * @section desc File description
 *
 * OS data structure generated from application MVC_system
 * Automatically generated by goil on Www Mmm dd hh:mm:ss yyyy
 * from root OIL file lab02_ex02.oil
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


#include "tpl_com_notification.h"
#include "tpl_com_mo.h"
#include "tpl_com_internal.h"
#include "tpl_com_internal_com.h"
/*#include "tpl_com_external_com.h"*/
#include "tpl_com_app_copy.h"
#include "tpl_com_filters.h"

/*=============================================================================
 * Application Modes tables for tasks, alarms and schedule tables
 * Application Modes masks are as follow:
 * stdAppmode = 1
 */

CONST(tpl_application_mode, OS_CONST) stdAppmode = 0; /* mask = 1 */
CONST(tpl_application_mode, OS_CONST) OSDEFAULTAPPMODE = 0;
CONST(tpl_appmode_mask, OS_CONST) tpl_task_app_mode[TASK_COUNT] = {
  0 /* task TaskV :  */ ,
  0 /* task TaskM :  */ ,
  1 /* task TaskC : stdAppmode */ 
};

CONST(tpl_appmode_mask, OS_CONST) tpl_alarm_app_mode[ALARM_COUNT] = {
  1 /* alarm alarmC : stdAppmode */ ,
  1 /* alarm alarmV : stdAppmode */ 
};

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of processes IDs
 */

/* Task TaskV identifier */
#define TaskV_id 0
CONST(TaskType, AUTOMATIC) TaskV = TaskV_id;

/* Task TaskM identifier */
#define TaskM_id 1
CONST(TaskType, AUTOMATIC) TaskM = TaskM_id;

/* Task TaskC identifier */
#define TaskC_id 2
CONST(TaskType, AUTOMATIC) TaskC = TaskC_id;

/*=============================================================================
 * Declaration of Alarm IDs
 */

/* Alarm alarmC identifier */
#define alarmC_id 0
CONST(AlarmType, AUTOMATIC) alarmC = alarmC_id;

/* Alarm alarmV identifier */
#define alarmV_id 1
CONST(AlarmType, AUTOMATIC) alarmV = alarmV_id;

/*=============================================================================
 * Declaration of receive messages IDs
 */

/* Message msgM_receive identifier */
#define msgM_receive_id 0
CONST(MessageIdentifier, AUTOMATIC) msgM_receive = msgM_receive_id;

/* Message msgV_receive identifier */
#define msgV_receive_id 1
CONST(MessageIdentifier, AUTOMATIC) msgV_receive = msgV_receive_id;

/*=============================================================================
 * Declaration of send messages IDs
 */

/* Message msgC_send identifier */
#define msgC_send_id 0
CONST(MessageIdentifier, AUTOMATIC) msgC_send = msgC_send_id;

/* Message msgM_send identifier */
#define msgM_send_id 1
CONST(MessageIdentifier, AUTOMATIC) msgM_send = msgM_send_id;

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
 * Task TaskV descriptor
 */
#define APP_Task_TaskV_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task TaskV function prototype
 */

FUNC(void, OS_APPL_CODE) TaskV_function(void);
#define APP_Task_TaskV_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task TaskV stack
 *
 */
#define APP_Task_TaskV_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word TaskV_stack_zone[256/sizeof(tpl_stack_word)];
#define APP_Task_TaskV_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define TaskV_STACK { TaskV_stack_zone, 256 }

/*
 * Task TaskV context
 */
avr_context TaskV_int_context;
#define TaskV_CONTEXT &TaskV_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task TaskV
 */
CONST(tpl_proc_static, OS_CONST) TaskV_task_stat_desc = {
  /* context                  */  TaskV_CONTEXT,
  /* stack                    */  TaskV_STACK,
  /* entry point (function)   */  TaskV_function,
  /* internal ressource       */  NULL,
  /* task id                  */  TaskV_id,
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
 * Dynamic descriptor of task TaskV
 */
VAR(tpl_proc, OS_VAR) TaskV_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task TaskM descriptor
 */
#define APP_Task_TaskM_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task TaskM function prototype
 */

FUNC(void, OS_APPL_CODE) TaskM_function(void);
#define APP_Task_TaskM_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task TaskM stack
 *
 */
#define APP_Task_TaskM_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word TaskM_stack_zone[256/sizeof(tpl_stack_word)];
#define APP_Task_TaskM_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define TaskM_STACK { TaskM_stack_zone, 256 }

/*
 * Task TaskM context
 */
avr_context TaskM_int_context;
#define TaskM_CONTEXT &TaskM_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task TaskM
 */
CONST(tpl_proc_static, OS_CONST) TaskM_task_stat_desc = {
  /* context                  */  TaskM_CONTEXT,
  /* stack                    */  TaskM_STACK,
  /* entry point (function)   */  TaskM_function,
  /* internal ressource       */  NULL,
  /* task id                  */  TaskM_id,
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
 * Dynamic descriptor of task TaskM
 */
VAR(tpl_proc, OS_VAR) TaskM_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  2,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

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
 * Dynamic descriptor of task TaskC
 */
VAR(tpl_proc, OS_VAR) TaskC_task_desc = {
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
  &TaskV_task_stat_desc,
  &TaskM_task_stat_desc,
  &TaskC_task_stat_desc,
  &IDLE_TASK_task_stat_desc
};

CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA)
tpl_dyn_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &TaskV_task_desc,
  &TaskM_task_desc,
  &TaskC_task_desc,
  &IDLE_TASK_task_desc
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Alarm related structures
 */
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
    /* cycle                        */  98,
    /* date                         */  98,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Alarm alarmV descriptor
 *
 * This alarm does the activation of task TaskV
 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) alarmV_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  TaskV_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
 
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_alarm_static, OS_CONST) alarmV_static = {
  {
    /* pointer to counter           */  &SystemCounter_counter_desc,
    /* pointer to the expiration    */  tpl_raise_alarm
#if (WITH_ID == YES)
    /* id of the alarm for tracing  */  , alarmV_id
#endif
#if WITH_OSAPPLICATION == YES
    /* OS application id            */  , 
#endif
  },
  /* action of the alarm  */  (tpl_action *)&alarmV_action
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_time_obj, OS_VAR) alarmV_alarm_desc = {
    /* pointer to the static part   */  (tpl_time_obj_static *)&alarmV_static,
    /* next alarm                   */  NULL,
    /* prev alarm                   */  NULL,
    /* cycle                        */  122,
    /* date                         */  122,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA)
  tpl_alarm_table[ALARM_COUNT] = {
  &alarmC_alarm_desc,
  &alarmV_alarm_desc
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of flags functions
 */
/* $FLAGSFUNCTIONS$ */


/*=============================================================================
 * Definitions of the custom filter functions
 * filter functions are generated according to the type
 * used for the corresponding message object
 */
/*
 * NEWISDIFFERENT filter function for type uint32_t
 */

FUNC(tpl_bool, OS_CODE) newisdifferent_uint_33__32__5F_t(
  CONSTP2CONST(tpl_filter_desc, AUTOMATIC, OS_CODE) fd,
  CONSTP2CONST(void, AUTOMATIC, OS_VAR) old_value,
  CONSTP2CONST(void, AUTOMATIC, OS_VAR) new_value)
{
  return (tpl_bool)((*((uint32_t *)new_value)) != (*((uint32_t *)old_value)));
}

/*=============================================================================
 * Definition and initialization of Receive Messages related structures
 */

/*-----------------------------------------------------------------------------
 * Action of message msgM_receive
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) msgM_receive_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  TaskM_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*-----------------------------------------------------------------------------
 * NEWISDIFFERENT filter of message object msgM_receive
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

tpl_noparam_filter_desc msgM_receive_filter = {
    /*  filtering function          */  newisdifferent_uint_33__32__5F_t
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Static internal receiving unqueued message object msgM_receive
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(uint32_t, OS_VAR) msgM_receive_buffer = 65535;

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_internal_receiving_unqueued_mo, OS_CONST) msgM_receive_message = {
  { /* data receiving mo struct   */
    { /* base receiving mo struct */
      /* notification pointer     */  (tpl_action *)&msgM_receive_action,
      /*  next receiving mo       */  NULL
    },
    /*  receiving function      */  (tpl_receiving_func)tpl_receive_static_internal_unqueued_message,
    /*  copy function           */  (tpl_data_copy_func)tpl_copy_from_unqueued,
    /*  filter pointer          */  (tpl_filter_desc *)&msgM_receive_filter
  },
  { /* buffer struct    */
    /*  buffer  */  (tpl_com_data *)&msgM_receive_buffer,
    /*  size    */  sizeof(uint32_t)
  }
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Action of message msgV_receive
 */
/*-----------------------------------------------------------------------------
 * NEWISDIFFERENT filter of message object msgV_receive
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

tpl_noparam_filter_desc msgV_receive_filter = {
    /*  filtering function          */  newisdifferent_uint_33__32__5F_t
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Static internal receiving unqueued message object msgV_receive
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(uint32_t, OS_VAR) msgV_receive_buffer = 0;

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_internal_receiving_unqueued_mo, OS_CONST) msgV_receive_message = {
  { /* data receiving mo struct   */
    { /* base receiving mo struct */
      /* notification pointer     */  NULL,
      /*  next receiving mo       */  NULL
    },
    /*  receiving function      */  (tpl_receiving_func)tpl_receive_static_internal_unqueued_message,
    /*  copy function           */  (tpl_data_copy_func)tpl_copy_from_unqueued,
    /*  filter pointer          */  (tpl_filter_desc *)&msgV_receive_filter
  },
  { /* buffer struct    */
    /*  buffer  */  (tpl_com_data *)&msgV_receive_buffer,
    /*  size    */  sizeof(uint32_t)
  }
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of the receive messages table
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONSTP2CONST(tpl_base_receiving_mo, AUTOMATIC, OS_CONST)
tpl_receive_message_table[RECEIVE_MESSAGE_COUNT] = {
  (tpl_base_receiving_mo*)&msgM_receive_message,    
  (tpl_base_receiving_mo*)&msgV_receive_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of Send Messages related structures
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Static internal sending static message object msgC_send
 */
CONST(tpl_internal_sending_mo, OS_CONST) msgC_send_message = {
  { /* base message object       */
    /* sending function          */ tpl_send_static_internal_message
  },
  /* pointer to the receiving mo */ (tpl_base_receiving_mo *)&msgM_receive_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Static internal sending static message object msgM_send
 */
CONST(tpl_internal_sending_mo, OS_CONST) msgM_send_message = {
  { /* base message object       */
    /* sending function          */ tpl_send_static_internal_message
  },
  /* pointer to the receiving mo */ (tpl_base_receiving_mo *)&msgV_receive_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of the send messages table
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONSTP2CONST(tpl_base_sending_mo, AUTOMATIC, OS_CONST)
tpl_send_message_table[SEND_MESSAGE_COUNT] = {
  (tpl_base_sending_mo*)&msgC_send_message,    
  (tpl_base_sending_mo*)&msgM_send_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
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

  "TaskV",
  "TaskM",
  "TaskC",
  "*idle*"
};
#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/* End of file tpl_app_config.c */
