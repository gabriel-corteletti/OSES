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
    static int S;                           //sample of the signal
    static int add = 0;                     //position to add next element
    static int msgS = 1;                    //message to activate consumer
    static int S_count = 0;                 //sample counter

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
        S_count++;

        //Checks if there are already 50 samples to activate consumer
        if (S_count >= 50) {
	        SendMessage(msgS_send, &msgS);
            S_count = 0;
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
    static int RR_count = 0;                //distance counter
    static int first_peak = 1;              //flag for the 1st ever peak
    static int peak_flag = 0;               //flag for peak found
    static int psbl_peak = -1;              //possible peak to be considered
    float RR;
    float HR;


    for(int i=0; i<50; i++){                //reads 50 elements in Q

        next_rem = (rem + 1)%K;             //next sample
        prev_rem = (rem - 1 + K)%K;         //previous sample

        GetResource(Sem);                   //Critical Section begins

        if ((i==0) && (psbl_peak >= Q[rem])) {                  //check if possible peak is
            peak_flag = 1;                                      //indeed an actual peak
            RR_count--;                                         //decrement counter to match previous time
        }
        psbl_peak = -1;                                                     //resets possible peak
        if ((i<49) && (Q[rem] > Q[prev_rem]) && (Q[rem] >= Q[next_rem])) {  //find peaks
            peak_flag = 1;
        }
        else if ((i==49) && (Q[rem] > Q[prev_rem]) && (Q[rem] > 900)) {     //special case for last sample
            psbl_peak = Q[rem];                                             //save possible peak
        }

        num--;                              //decrement amount of data

        ReleaseResource(Sem);               //Critical Section ends

        if (peak_flag) {                    //if a peak was found
            if (!first_peak) {              //check if it's not the 1st
                RR = RR_count*0.02;
                HR = 60/RR;
                Serial.print("HR: ");
                Serial.println(HR);
            }
            else {                          //updates the first flag
                first_peak = 0;
            }

            RR_count = 0;                   //resets sample counter
            peak_flag = 0;                  //reset peak flag
        }

        RR_count++;                         //increment sample counter
        rem = next_rem;                     //circular buffer: 0 <= rem <= K-1
    }

    TerminateTask();
}