

/**
 * @file    PR4.c
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include<stdio.h>
#include "events.h"
#include "led_board.h"
#include "TMP102.h"
#include "loggers.h"
int8_t sumtemp=0;
int8_t reading=0;
uint8_t timeoutcounter=1;
int8_t avgtemp=0;
statetypes state=temp_reading;
volatile int sm1=1;//starting with state machine 1
volatile int sm2=0;

void init()
{
	LED_Initialise();
	All_Init();
}

void post()
{  disconnectcheck();
LED_PASS();//switches on green led and all others off
LED_PROCESS();//switches on blue led and others off
LED_FAIL();
}
void statemachine1()
{
	switch(state)
		{
		case disconnect: //disconnected state
			state=disconnectcheck();
			break;

		case temp_reading:
			state=temp_readinghandler();
			break;

		case average:
			state=average_handler();
			break;
		case temp_alert:

				state=alert_handler();
			break;
		}
	}

// run timer for 15s and delay here and increment counter

statetypes (*currentfunction)();
statetypes (*functiontable[4][4])()=
{
		{&disconnectcheck,NULL,NULL,NULL}, //state disconnected
		{NULL,&temp_readinghandler,NULL,NULL},//state tempread
		{NULL,NULL,&average_handler,NULL},//state average
		{NULL,NULL,NULL,&alert_handler}//state alert
};

void statemachine2()
{ printf("sm2\n");
	currentfunction=functiontable[state][state];
		if(currentfunction!=NULL)
			state=(*currentfunction)();

//		if(k==3)
//		{
//			//printf("here\n");logstate(state);
//			state=complete(state);
//			if(timeoutcounter==5)
//					{
//						sm2=0;sm1=1;timeoutcounter=1;currentfunction=NULL;sumtemp=0;
//					}
//		}

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


	while(1)
	{
		if((sm1==1)&&(sm2==0))
		{
			statemachine1();
		}

		if((sm2==1)&&(sm1==0))
		{
				statemachine2();

		}

	}




	return 0 ;
}

void PORTA_IRQHandler(void)
{
	PORTA->PCR[4] |= PORT_PCR_ISF_MASK; //PORT_ISFR_ISF(0x40);
//
	NVIC->ICER[0] |=(1<<PORTA_IRQn);
	//Raw_Temp=I2C_Read(TEMP_REG);
	state=temp_alert;
}
