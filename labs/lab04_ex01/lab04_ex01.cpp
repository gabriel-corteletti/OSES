#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"


void setup()
{
    Serial.begin(9600);
}


DeclareTask(TaskS);
DeclareTask(TaskB);
DeclareTask(TaskV);
DeclareResource(Sem);


TASK (TaskS){


    TerminateTask();
}