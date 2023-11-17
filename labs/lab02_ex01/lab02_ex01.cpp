#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"


void setup()
{
    //Define I/O settings of pins
    pinMode(A0, INPUT);
    pinMode(12, INPUT_PULLUP);	//enable the internal pull-up resistor
    pinMode(13, OUTPUT);
	Serial.begin(9600);			//JUST FOR DEBBUGING
}


DeclareTask(TaskC);
DeclareTask(TaskM);
DeclareTask(TaskV);
DeclareMessage(msgC_send);
DeclareMessage(msgM_receive);
DeclareMessage(msgM_send);
DeclareMessage(msgV_receive);


TASK(TaskC)
{
    static unsigned int msgC = 0;
    static int A0_read = 0;
    static int S_count = 0;
	static int S_pressed = 0;

	//Get analog value of voltage source
    A0_read = analogRead(A0);

	//Get switch state and check minimum duration
    if (digitalRead(12) == LOW){   	//closed
    	S_count++;
		if (S_count >= 10){			//at least 1s
			S_pressed = 1;
		}
  	}
  	else{             				//open
    	S_count = 0;
    	S_pressed = 0;
  	}

	//Encode and send message
	msgC = A0_read | S_pressed<<12;
	SendMessage(msgC_send, &msgC);

	TerminateTask();
}


TASK(TaskM)
{
	static unsigned int msgM = 0;
	unsigned int msgC;
	int S_state;
    int A0_val;
	static int R = -1;
	static int X;
	
	ReceiveMessage(msgM_receive, &msgC);
	
	//Decode switch state from message
	S_state = msgC>>12 && 0x01;

	//Decode A0 value from message
	A0_val = msgC & 0x03FF;

	//Update reference value
	if (S_state){
		R = A0_val;
	}

	//Get absolute difference between reference and reading
	X = abs(A0_val - R);

	//Define and send proper state
	if (R == -1){
		msgM = 3;						//ON
	}
	else if (X < 100){
		msgM = 0;						//OFF
	}
	else if (X >= 100 && X < 200){
		msgM = 1;						//slowly
	}
	else if (X >= 200){
		msgM = 2;						//fast
	}
	SendMessage(msgM_send, &msgM);

	TerminateTask();
}


TASK(TaskV)
{
	unsigned int msgM = 0;
	static int led_state = 0;
	static int countV = 0;

	ReceiveMessage(msgV_receive, &msgM);

	//Update state
	if (msgM == 0){							//OFF
		digitalWrite(13, LOW);
	}
	else if (msgM == 1 && countV >= 4){		//slowly
		digitalWrite(13, led_state);
		led_state = !led_state;
		countV = 0;
	}
	else if (msgM == 2){					//fast
		digitalWrite(13, led_state);
		led_state = !led_state;
	}
	else if (msgM == 3){					//ON
		digitalWrite(13, HIGH);
	}

	countV++;

	TerminateTask();
}