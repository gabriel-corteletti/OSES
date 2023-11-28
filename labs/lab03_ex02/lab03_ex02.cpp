#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"

// ../../goil/makefile-unix/goil --target=avr/arduino/uno --templates=../../goil/templates/ lab03_ex01.oil


void setup()
{
    Serial.begin(9600);
}


DeclareTask(TaskA);
DeclareTask(TaskB);
DeclareTask(TaskC);
DeclareResource(Sem);


void do_things(int ms)
{
    unsigned long mul = ms * 504UL;
    unsigned long i;
    for(i=0; i<mul; i++) millis();
}


TASK(TaskA)
{
    static unsigned int count_A = 1;
    static unsigned long A_end;

    Serial.print("Task A");
    Serial.print(count_A);
    Serial.println(" begun");

    GetResource(Sem);
    do_things(300);
    ReleaseResource(Sem);
    
    Serial.print("Task A");
    Serial.print(count_A++);
    Serial.print(" finished: ");
    A_end = millis();
    Serial.println(A_end);

    TerminateTask();
}


TASK(TaskB)
{
    static unsigned int count_B = 1;
    static unsigned long B_end;

    Serial.print("Task B");
    Serial.print(count_B);
    Serial.println(" begun");

    do_things(600);
    
    Serial.print("Task B");
    Serial.print(count_B++);
    Serial.print(" finished: ");
    B_end = millis();
    Serial.println(B_end);

    TerminateTask();
}


TASK(TaskC)
{
    static unsigned int count_C = 1;
    static unsigned long C_end;

    Serial.print("Task C");
    Serial.print(count_C);
    Serial.println(" begun");

    do_things(200);
    GetResource(Sem);
    do_things(300);
    ReleaseResource(Sem);

    Serial.print("Task C");
    Serial.print(count_C++);
    Serial.print(" finished: ");
    C_end = millis();
    Serial.println(C_end);

    TerminateTask();
}