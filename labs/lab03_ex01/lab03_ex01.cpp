#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"


void setup()
{
    Serial.begin(9600);
}


DeclareTask(TaskA);
DeclareTask(TaskB);
DeclareTask(TaskC);


void do_things(int ms)
{
    unsigned long mul = ms * 504UL;
    unsigned long i;
    for(i=0; i<mul; i++) millis();
}


TASK(TaskA)
{
    static unsigned int count_A = 0;
    static unsigned long A_ready;
    static unsigned long A_finish;
    static unsigned long A_WCRT = 0;
    static unsigned long A_RT;

    A_ready = 1200*count_A;
    Serial.print("A");
    Serial.print(++count_A);
    Serial.print(" ready: ");
    Serial.println(A_ready);

    do_things(200);
    
    Serial.print("A");
    Serial.print(count_A);
    Serial.print(" ended: ");
    A_finish = millis();
    Serial.print(A_finish);
    Serial.print(" -> RT: ");
    A_RT = A_finish - A_ready;
    Serial.print(A_RT);

    if (A_RT > A_WCRT){
        A_WCRT = A_RT;
        Serial.println(" <<< new A-WCRT");
    }
    else {
        Serial.println();
    }

    TerminateTask();
}


TASK(TaskB)
{
    static unsigned int count_B = 0;
    static unsigned long B_ready;
    static unsigned long B_finish;
    static unsigned long B_WCRT = 0;
    static unsigned long B_RT;

    B_ready = 2000*count_B;
    Serial.print("B");
    Serial.print(++count_B);
    Serial.print(" ready: ");
    Serial.println(B_ready);

    do_things(600);
    
    Serial.print("B");
    Serial.print(count_B);
    Serial.print(" ended: ");
    B_finish = millis();
    Serial.print(B_finish);
    Serial.print(" -> RT: ");
    B_RT = B_finish - B_ready;
    Serial.print(B_RT);

    if (B_RT > B_WCRT){
        B_WCRT = B_RT;
        Serial.println(" <<< new B-WCRT");
    }
    else {
        Serial.println();
    }

    TerminateTask();
}


TASK(TaskC)
{
    static unsigned int count_C = 0;
    static unsigned long C_ready;
    static unsigned long C_finish;
    static unsigned long C_WCRT = 0;
    static unsigned long C_RT;

    C_ready = 3000*count_C;
    Serial.print("C");
    Serial.print(++count_C);
    Serial.print(" ready: ");
    Serial.println(C_ready);

    do_things(300);
    
    Serial.print("C");
    Serial.print(count_C);
    Serial.print(" ended: ");
    C_finish = millis();
    Serial.print(C_finish);
    Serial.print(" -> RT: ");
    C_RT = C_finish - C_ready;
    Serial.print(C_RT);

    if (C_RT > C_WCRT){
        C_WCRT = C_RT;
        Serial.println(" <<< new C-WCRT");
    }
    else {
        Serial.println();
    }

    TerminateTask();
}