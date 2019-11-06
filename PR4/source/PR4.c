

//main routine PES PRoject 4-
//SHaran Arumugam and Abhijeet

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "events.h"
#include "led_board.h"
#include "TMP102.h"
#include "loggers.h"
#include "Testsuite.h"
#include "uCUnit-v1.0.h"
#include "System.h"

int8_t sumtemp=0; //contains sum of numbers
int8_t reading=0; //contains active reading
uint8_t timeoutcounter=1; //counts number of timeouts
int8_t avgtemp=0; //stores avgtemp
statetypes state=temp_reading; //starting with temp_reading
volatile int sm1=1;//starting with state machine 1
volatile int sm2=0;

void init()
{
	LED_Initialise();//led initialization
	All_Init();//initilalises both i2c and interrupt on PORTA Pin 4
}

void post()
{
disconnectcheck(); //to check if sensor is connected
LED_PASS();//switches on green led and all others off
LED_PROCESS();//switches on blue led and others off
LED_FAIL();//switches on red led and others off to find when alert is triggered
}
void statemachine1()
{ logmachine(); //states which state machine you are in
	switch(state)
		{
		case disconnect: //disconnected state
			state=disconnectcheck();UCUNIT_Tracepoint(1);//for testing-- trace 1 for disconnected state
			break;

		case temp_reading:
			state=temp_readinghandler();UCUNIT_Tracepoint(2);//for testing-- trace2 for temp reading state
			break;

		case average:
			state=average_handler();UCUNIT_Tracepoint(3);//for testing-- trace 3 for finding and printing average
			break;
		case temp_alert:

				state=alert_handler();UCUNIT_Tracepoint(4);//for testing-- sets when in alert
			break;
		}
	}


//ptr to call functions in statemachine 2
statetypes (*currentfunction)();
//state table shows functions to be carried out when in a particular state- Rows correspond to state and colums to different functions
statetypes (*functiontable[4][4])()=
{
		{&disconnectcheck,NULL,NULL,NULL}, //state disconnected
		{NULL,&temp_readinghandler,NULL,NULL},//state tempread
		{NULL,NULL,&average_handler,NULL},//state average
		{NULL,NULL,NULL,&alert_handler}//state alert
};
//state machine based on table
void statemachine2()
{ logmachine();//prints which statemachine on
	currentfunction=functiontable[state][state];//loading ptr to point at function
		if(currentfunction!=NULL)
			state=(*currentfunction)(); //dereferences fn. pointer when not null

}



int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	init();
	post();
#ifdef TEST //runs test case statements
UCUNIT_Init();
UCUNIT_TestcaseBegin("Project 4 testing begins");
statemachine1();
statemachine2();
UCUNIT_CheckIsInRange(avgtemp,-10, 100);//checks if temperature was in between -10 and 100
UCUNIT_CheckIsEqual(temp_reading,average_handler()); //checks whether correct state is assigned is being passed
UCUNIT_CheckIs8Bit(avgtemp);//check if result temp. is 8bit value
UCUNIT_CheckIsEqual(average,alert_handler());//checks whether correct state is assigned is being passed
UCUNIT_CheckIsEqual(average,temp_readinghandler());//checks whether correct state is assigned is being passed
UCUNIT_CheckTracepointCoverage(1);//checks if discoonect passed
UCUNIT_CheckTracepointCoverage(2);//checks if temp reading passed
UCUNIT_CheckTracepointCoverage(3);//checks if average passed
UCUNIT_CheckTracepointCoverage(4);//checks if alert passed
UCUNIT_WriteSummary();//writes results
UCUNIT_Shutdown();//stops testing
return 0;
}
#else
	while(1)
	{
		if((sm1==1)&&(sm2==0))//for running statemachine 1 ; sm1 needs to be set and sm2 to be off
		{
			statemachine1();
		}

		if((sm2==1)&&(sm1==0))//for running statemachine 2 ; sm2 needs to be set and sm1 to be off
		{
				statemachine2();

		}

	}




	return 0 ;
}
#endif
void PORTA_IRQHandler(void)//interrupt handler
{
PORTA->PCR[4] |= PORT_PCR_ISF_MASK; //masks interrupt flag
NVIC->ICER[0] |=(1<<PORTA_IRQn);//clears interrupt
state=temp_alert; //sets state to alert state
}

