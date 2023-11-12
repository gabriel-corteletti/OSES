#include <stdio.h>
#include <math.h>
#include "tpl_os.h"

int main(void)
{
	StartOS(OSDEFAULTAPPMODE);
	return 0;
}

DeclareAlarm(a500msec);
DeclareAlarm(a750msec);

TASK(TaskA)
{
  static int CounterA = 0;
 
  printf("Task A counter = %d\r\n", CounterA);
  CounterA += 500;

  TerminateTask();
}

TASK(TaskB)
{
  static int CounterB = 1500;
  printf("Task B counter = %d\r\n", CounterB);
  CounterB += 750;
 
  TerminateTask();
}

TASK(stop)
{
  CancelAlarm(a500msec);
  CancelAlarm(a750msec);
  printf("Shutdown\r\n");
  ShutdownOS(E_OK);
  TerminateTask();
}