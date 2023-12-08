#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"

#define K 5    //queue size

//Global variables
int Q[K];       //shared queue
int error;
int alarm;
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

    // //Get analog value of voltage source
    // X = analogRead(A0);


    X++;


    // //Checks error
    // if(X<10 || X>1013){
    //     error = 1;
    // }
    // else{
    //     error = 0;
    // }

    //Checks for overflow
    if (num >= K){
        Serial.println("==================  Queue Overflow  ==================");
    }
    else{
        //Critical Section begins
        GetResource(Sem);



        Q[add] = X;         //Inserts X in Q



        Serial.print("Added ");
        Serial.print(X);
        Serial.print(" in position ");
        Serial.print(add);
        Serial.print(" -> amount: ");

        

        num++;              //Increment amount of data

        Serial.println(num);


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


            Serial.print("\t\t\tRemoved ");
            Serial.print(Q[rem]);
            Serial.print(" in position ");
            Serial.print(rem);
            Serial.print(" -> amount: ");


            rem = (rem+1)%K;    //circular buffer: 0 <= rem <= K-1


            //Critical Section begins
            GetResource(Sem);

            num--;              //Decrement amount of data




            Serial.println(num);

            //Critical Section ends
            ReleaseResource(Sem);




        }
    }

    Serial.print("\t\t\tN: ");
    Serial.print(N);
    Serial.print("   |   M: ");
    Serial.println(M);




    // //Checks alarm
    // if(M-N > 500){
    //     alarm = 1;
    // }
    // else{
    //     alarm=0;
    // }



    TerminateTask();
}


TASK (TaskV){
    TerminateTask();
}








