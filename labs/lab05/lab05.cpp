#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"

#define K 67                //queue size

//Global variables
int Q[K];                   //shared queue
unsigned int num = 0;       //amount of data in Q


void setup()
{
    pinMode(A0, INPUT);     //signal
    Serial.begin(9600);
}


DeclareTask(TaskS);
DeclareTask(TaskC);
DeclareMessage(msgS_send);
DeclareMessage(msgC_receive);
DeclareResource(Sem);


TASK (TaskS){
    static int msgS = 1;            //message to activate consumer
    static int S;                   //sample of the signal
    static int add = 0;             //position to add next element

    S = analogRead(A0);             //get a new sample of the signal

    GetResource(Sem);               //Critical Section begins

    //Checks for overflow
    if (num >= K){
        Serial.println("ERROR: Queue Overflow");
        ReleaseResource(Sem);       //Critical Section ends
    }
    else{
        Q[add] = S;                 //inserts new S in Q
        num++;                      //increment amount of data

        //prints new data
        Serial.print("S: ");       
        Serial.print(S);
        Serial.print("\t| ");
        Serial.println(num);

        //Checks if there are already 50 samples to activate consumer
        if (num >= 50) {
            Serial.println("-------Activate C--------");
	        SendMessage(msgS_send, &msgS);
        }

        ReleaseResource(Sem);       //Critical Section ends

        add = (add+1)%K;            //circular buffer: 0 <= add <= K-1
    }

    TerminateTask();
}


TASK (TaskC){
    static int rem = 0;             //position to remove next element
    static int next_rem;
    static int prev_rem;
    static int s_count = 0;
    static int first_peak = 1;
    float RR;
    float HR;
    static int peak_flag = 0;


    for(int i=0; i<50; i++){        //reads 50 elements in Q

        next_rem = (rem + 1)%K;
        prev_rem = (rem - 1 + K)%K;

        GetResource(Sem);               //Critical Section begins

        // if (i<49) {         //if (i>1 && i<49) {          //discards the first and last of the 50 samples
        //     if ((Q[rem] > Q[prev_rem]) && (Q[rem] > Q[next_rem])) {
        //         peak_flag = 1;
        //     }
        // }
        // else if ((Q[rem] > Q[prev_rem]) && (Q[rem] > 1000)) {
        //     peak_flag = 1;
        // }

        if (((i<49) && (Q[rem] > Q[prev_rem]) && (Q[rem] > Q[next_rem])) ||
            ((i==49) && (Q[rem] > Q[prev_rem]) && (Q[rem] > 1000))) {         //if (i>1 && i<49) {          //discards the first and last of the 50 samples
            // peak_flag = 1;
            Serial.print("\t\tPEAK: ");
            Serial.println(Q[rem]);
            if (!first_peak) {
                RR = s_count*0.02;
                HR = 60/RR;
                // Serial.print("\t\tRR: ");
                // Serial.print(RR);
                // Serial.print("  |  HR: ");
                Serial.print("\t\tHR: ");
                Serial.println(HR);
            }
            else {
                first_peak = 0;
            }
            s_count = 0;
        }






        // if (peak_flag) {
        //     Serial.print("\t\tPEAK: ");
        //     Serial.println(Q[rem]);
        //     if (!first_peak) {
        //         RR = s_count*0.02;
        //         HR = 60/RR;
        //         // Serial.print("\t\tRR: ");
        //         // Serial.print(RR);
        //         // Serial.print("  |  HR: ");
        //         Serial.print("\t\tHR: ");
        //         Serial.println(HR);
        //     }
        //     else {
        //         first_peak = 0;
        //     }
        //     s_count = 0;
        //     peak_flag = 0;
        // }



        num--;                      //decrement amount of data

        ReleaseResource(Sem);       //Critical Section ends

        s_count++;                  //increment sample counter
        rem = next_rem; //(rem+1)%K;            //circular buffer: 0 <= rem <= K-1
    }

    TerminateTask();
}