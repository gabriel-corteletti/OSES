#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"

#define K 67                                //queue size

//Global variables
int Q[K];                                   //shared queue
unsigned int num = 0;                       //amount of data in Q


void setup()
{
    pinMode(A0, INPUT);                     //signal
    Serial.begin(9600);
}


DeclareTask(TaskS);
DeclareTask(TaskC);
DeclareMessage(msgS_send);
DeclareMessage(msgC_receive);
DeclareResource(Sem);


TASK (TaskS){
    static int msgS = 1;                    //message to activate consumer
    static int S;                           //sample of the signal
    static int add = 0;                     //position to add next element

    S = analogRead(A0);                     //get a new sample of the signal

    GetResource(Sem);                       //Critical Section begins

    //Checks for overflow
    if (num >= K){
        Serial.println("ERROR: Queue Overflow");
        ReleaseResource(Sem);               //Critical Section ends
    }
    else{
        Q[add] = S;                         //inserts new S in Q
        num++;                              //increment amount of data

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

        ReleaseResource(Sem);               //Critical Section ends

        add = (add+1)%K;                    //circular buffer: 0 <= add <= K-1
    }

    TerminateTask();
}


TASK (TaskC){
    static int rem = 0;                     //position to remove next element
    static int next_rem;
    static int prev_rem;
    static int s_count = 0;
    static int first_peak = 1;
    float RR;
    float HR;
    static int peak_flag = 0;
    static int psbl_peak = -1;


    for(int i=0; i<50; i++){                //reads 50 elements in Q

        next_rem = (rem + 1)%K;             //next sample
        prev_rem = (rem - 1 + K)%K;         //previous sample

        GetResource(Sem);                   //Critical Section begins

        // if (((i<49) && (Q[rem] > Q[prev_rem]) && (Q[rem] >= Q[next_rem])) ||
        //     ((i==49) && (Q[rem] > Q[prev_rem]) && (Q[rem] > 1000))) {         //if (i>1 && i<49) {          //discards the first and last of the 50 samples
        //     peak_flag = 1;
        //     Serial.print("\t\tPEAK: ");
        //     Serial.println(Q[rem]);
        // }

        if ((i==0) && (psbl_peak >= Q[rem])) {                              //check if possible peak is
            peak_flag = 1;                                                  //indeed an actual peak
            Serial.print("\t\t###POSSIBLE PEAK: ");
            Serial.println(psbl_peak);
        }
        psbl_peak = -1;                                                     //resets possible peak
        if ((i<49) && (Q[rem] > Q[prev_rem]) && (Q[rem] >= Q[next_rem])) {  //find peaks
            peak_flag = 1;
            Serial.print("\t\tPEAK: ");
            Serial.println(Q[rem]);
        }
        else if ((i==49) && (Q[rem] > Q[prev_rem]) && (Q[rem] > 900)) {     //special case for last sample
            psbl_peak = Q[rem];                                             //save possible peak
        }

        num--;                              //decrement amount of data

        ReleaseResource(Sem);               //Critical Section ends

        if (peak_flag) {                    //if a peak was found
            if (!first_peak) {              //check if it's not the 1st
                RR = s_count*0.02;
                HR = 60/RR;
                Serial.print("\t\tHR: ");
                Serial.println(HR);
            }
            else {                          //updates the first flag
                first_peak = 0;
            }

            s_count = 0;                    //resets sample counter
            peak_flag = 0;                  //reset peak flag
        }

        s_count++;                          //increment sample counter
        rem = next_rem;                     //circular buffer: 0 <= rem <= K-1
    }

    TerminateTask();
}