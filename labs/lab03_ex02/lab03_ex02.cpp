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
DeclareResource(Sem);


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
    static unsigned long A_CS_start;
    static unsigned long A_CS_finish;

    A_ready = 1200*count_A;
    Serial.print("A");
    Serial.print(++count_A);
    Serial.print(" ready: ");
    Serial.println(A_ready);

    GetResource(Sem);
    
    Serial.print("  --C.S. of A");
    Serial.print(count_A);
    Serial.print(" begun: ");
    A_CS_start = millis();
    Serial.println(A_CS_start);
    
    do_things(300);
    
    Serial.print("  --C.S. of A");
    Serial.print(count_A);
    Serial.print(" ended: ");
    A_CS_finish = millis();
    Serial.println(A_CS_finish);

    ReleaseResource(Sem);
    
    Serial.print("A");
    Serial.print(count_A);
    Serial.print(" ended: ");
    A_finish = millis();
    Serial.println(A_finish);

    TerminateTask();
}


TASK(TaskB)
{
    static unsigned int count_B = 0;
    static unsigned long B_ready;
    static unsigned long B_finish;

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
    Serial.println(B_finish);

    TerminateTask();
}


TASK(TaskC)
{
    static unsigned int count_C = 0;
    static unsigned long C_ready;
    static unsigned long C_finish;
    static unsigned long C_CS_start;
    static unsigned long C_CS_finish;

    C_ready = 3000*count_C;
    Serial.print("C");
    Serial.print(++count_C);
    Serial.print(" ready: ");
    Serial.println(C_ready);

    do_things(200);

    GetResource(Sem);
    
    Serial.print("  --C.S. of C");
    Serial.print(count_C);
    Serial.print(" begun: ");
    C_CS_start = millis();
    Serial.println(C_CS_start);
    
    do_things(300);
    
    Serial.print("  --C.S. of C");
    Serial.print(count_C);
    Serial.print(" ended: ");
    C_CS_finish = millis();
    Serial.println(C_CS_finish);

    ReleaseResource(Sem);
    
    Serial.print("C");
    Serial.print(count_C);
    Serial.print(" ended: ");
    C_finish = millis();
    Serial.println(C_finish);

    TerminateTask();
}