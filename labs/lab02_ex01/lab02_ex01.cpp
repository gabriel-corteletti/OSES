#include <stdio.h>
#include "Arduino.h"
#include "tpl_os.h"
// #include <math.h>
// #include <unistd.h>
// #include <sys/time.h>
// #include "tpl_com.h"
// #include "tpl_posixvp_irq_gen.h"


void setup()
{
    //Define I/O settings of pins
    pinMode(A0, INPUT);
    pinMode(12, INPUT_PULLUP);	//enable the internal pull-up resistor
    pinMode(13, OUTPUT);

	Serial.begin(115200);
}


DeclareTask(TaskC);
DeclareTask(TaskM);
DeclareTask(TaskV);
DeclareMessage(msgC_send);
DeclareMessage(msgM_receive);
DeclareMessage(msgM_send);
DeclareMessage(msgV_receive);


// int bin_to_dec(unsigned int binary){
// 	//auxiliary function to convert binary values to decimal
// 	int i = 0;
// 	int decimal = 0;
// 	int bit;
// 	int weight = 1;

// 	while (binary != 0){
// 		bit = binary % 10;
// 		decimal += bit*weight;
// 		weight *= 2;
// 		binary /= 10;
// 		i++;
// 	}

// 	return decimal;
// }


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
	//A0_dec = bin_to_dec(A0_bin);

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



	// Serial.print("S_state:");
	// Serial.println(S_state);
	// Serial.print("A0_val:");
	// Serial.println(A0_val);
	// Serial.print("R:");
	// Serial.println(R);
	// Serial.print("X:");
	// Serial.println(X);
	// Serial.print("msgM:");
	// Serial.println(msgM);
	// Serial.print("------------------\n");


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







// #define	DELAY	2000000

// int num=0;	

// void wait_a_lot( long int t )
// {
// 	struct timeval start, end;
// 	gettimeofday(&start, NULL);

// 	do {
// 		gettimeofday(&end, NULL);
// 	} while( ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) < t );
// }

// int main(void)
// {
// 	fflush( stdout );
// 	StartOS(OSDEFAULTAPPMODE);
// 	return 0;
// }

// DeclareAlarm(one_sec_producer);
// DeclareTask(Producer);
// DeclareTask(Consumer);
// DeclareTask(Threshold);
// DeclareMessage(from_producer);
// DeclareMessage(consumer_receive);
// DeclareResource(sem);

// TASK(Producer)
// {
// 	static int i=0;

// 	if( SendMessage(from_producer, &i) != E_OK ) {
// 		printf( "Producer: error sending data\n\r");
// 	} else {
// 		GetResource(sem);
// 		num++;
// 		printf ("Producer: inserted %d \t\t %d elements in the buffer\n\r", i, num);
// 		fflush( stdout );
// 		ReleaseResource(sem);

// 		i++;
// 	}
// 	TerminateTask();
// }

// TASK(Consumer)
// {
// 	int	i;

// 	if( ReceiveMessage(consumer_receive, &i) == E_COM_LIMIT ) {
// 		printf( "Consumer: at least one message is lost\n\r" );
// 	}
// 	wait_a_lot(DELAY);

// 	GetResource(sem);
// 	num--;
// 	printf ("Consumer: consumed value %d \t %d elements in the buffer\n\r", i, num);
// 	fflush( stdout );
// 	ReleaseResource(sem);

// 	wait_a_lot(DELAY);

// 	TerminateTask();
// }

// TASK(Threshold)
// {
// 	int	i;

// 	if( ReceiveMessage(threshold_receive, &i) != E_OK ) {
// 		printf( "Threshold: receive error\n\r" );
// 		fflush(stdout);
// 	} else {
// 		printf( "Threshold: received data %d\n\r", i );
// 		fflush(stdout);
// 	}
// 	TerminateTask();
// }
