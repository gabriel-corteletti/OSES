#include "tpl_os.h"
#include "Arduino.h"
#include <stdio.h>
#include <math.h>


void setup()
{
    // initialize digital pin 13 as an output.
    pinMode(13, OUTPUT);
}



DeclareAlarm(a500msec);
DeclareAlarm(a750msec);

TASK(TaskA)
{
  digitalWrite(13, HIGH);
  TerminateTask();
}

TASK(TaskB)
{
   digitalWrite(13, LOW);
   TerminateTask();
}

TASK(stop)
{
  CancelAlarm(a500msec);
  CancelAlarm(a750msec);
  ShutdownOS(E_OK);
  TerminateTask();
}