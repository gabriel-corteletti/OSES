#include "tpl_os.h"
#include "Arduino.h"

void setup() {
 pinMode(13, OUTPUT);
 pinMode(12, OUTPUT);
}

//the periodic task is activated by the 
TASK(TaskV) {

static unsigned int m;
ReceivedMessage(receive_v , &m);
if(m==0){
  digitalWrite(13,0);
}else if(m==1){
  digitalWrite(13,LOW);
}else if(m==2){
  digitalWrite(13,HIGH);
}else{
  digitalWrite(13,1);
}
TerminateTask(); 
   }


//activates every 100ms by alarm see oil file 

TASK(TaskC) {
static unsigned int val;
static unsigned int s;
s=signalRead(S0);
val=analogRead(A0);
static unsigned int scont=0;
int length = strlen(val);
if(length=12){
//bit 12 is set 
scont=1;
}
int binaryToDecimal(char *val) {
    int length = strlen(val);
    static int decimalNumber = 0;

    for (int i = length - 1, j = 0; i >= 0; i--, j++) {
        if (binaryString[i] == '1') {
            decimalNumber += (1 << j);
        }
    }

    return decimalNumber;
}
SendMessage(send_m , &decimalNumber);
SendMessage(send_m , &scont);

TerminateTask(); }

//activates every 500ms 
TASK(TaskM){
static unsigned int x;
static unsigned int R=0;

ReceivedMessage(receive_m , &decimalNumber);
ReceivedMessage(receive_m , &scont);
static unsigned int X=&decimalNumber - R;
if(scont==1){
R=&decimalNumber
}else if(R=0){
 SendMessage(send_v, 3);  //m=3
}else if(R!=0 && abs(&decimalNumber - R) < 100){
 SendMessage(send_v, 0);   //m=0
}else if(X>=100 && X<200){
 SendMessage(send_v, 1); 
}else if(X>=200){
 SendMessage(send_v, 2); 
}

}

TASK(stop) {
ShutdownOS(E_OK);
TerminateTask(); }