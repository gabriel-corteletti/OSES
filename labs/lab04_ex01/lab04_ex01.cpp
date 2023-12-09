#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"
#include <string.h>
#include <stdlib.h>

#define K 5    //queue size

//Global variables
int Q[K];       //shared queue
int error = 0;
int alarm = 0;
int add = 0;    //position to add next element
int rem = 0;    //position to remove next element
int num = 0;


void setup()
{
    pinMode(A0, INPUT);     //voltage
    pinMode(13, OUTPUT);    //led
    Serial.begin(9600);
}


DeclareTask(TaskS);
DeclareTask(TaskB);
DeclareTask(TaskV);
DeclareResource(Sem);


TASK (TaskS){
    static int X;

    //Get analog value of voltage source
    X = analogRead(A0);

    //Checks error
    if(X<10 || X>1013){
        error = 1;
    }
    else{
        error = 0;
    }

    //Checks for overflow
    if (num >= K){
        Serial.println("ERROR: Queue Overflow");
    }
    else{
        //Critical Section begins
        GetResource(Sem);

        Q[add] = X;         //Inserts new X in Q

        //Prints new measured X
        char msg[64];
        sprintf(msg, "S: New X = %d -> err: %d",X,error);
        Serial.println(msg);

        num++;              //Increment amount of data

        //Critical Section ends
        ReleaseResource(Sem);

        add = (add+1)%K;    //circular buffer: 0 <= add <= K-1
    }

    TerminateTask();
}


TASK (TaskB){
    int M = -9999;   //maximum
    int N = 9999;    //minimum

    for(int i=0; i<K; i++){     //Reads all elements in Q
        if(num>0){              //if there are any left

            //Check if it is greater than the current maximum
            if(Q[rem] > M){
                M = Q[rem];
            }

            //Check if it is smaller than the current minimum
            if(Q[rem] < N){
                N = Q[rem];
            }

            //Critical Section begins
            GetResource(Sem);

            num--;              //Decrement amount of data

            //Critical Section ends
            ReleaseResource(Sem);

            rem = (rem+1)%K;    //circular buffer: 0 <= rem <= K-1
        }
    }

    //Checks alarm
    if(M-N > 500){
        alarm = 1;
    }
    else{
        alarm = 0;
    }

    //Print B results
    char msg[64];
    sprintf(msg, "\t\tB: N = %d  |  M = %d\n\t\t   M-N = %d -> alarm: %d", N, M, N-M, alarm);
    Serial.println(msg);

    TerminateTask();
}


TASK (TaskV){
    static int led_state = 0;
    static int countV = 0;

    //Update state
	if (error == 1){					                //fast
		digitalWrite(13, led_state);
		led_state = !led_state;
	}
	else if (error == 0 && alarm == 1 && countV >= 4){	//slowly
		digitalWrite(13, led_state);
		led_state = !led_state;
		countV = 0;
	}
	else if (error == 0 && alarm == 0){					//OFF
		digitalWrite(13, LOW);
	}

    countV++;

    TerminateTask();
}