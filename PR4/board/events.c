#include "events.h"
#include "loggers.h"
#include "TMP102.h"

statetypes disconnectcheck()
{
	while(disconnect1()) //if sensor disconnected program keeps printing discoonect and needs a reset to setup again
	{
		printf("\nSensor disconnected\n");
		LED_FAIL();//red led up
	}
	return temp_reading;//if not disconnected goes to next state
}
int gettemp()
{
	LED_PASS();//grren led on
	reading=I2C_Read(TEMP_REG);//performs i2c read of temp register

	return 0;
}
int disablealert()
{
	PORTA->PCR[4] |= PORT_PCR_ISF_MASK; //masks interrupt flag

	NVIC->ICER[0] |=(1<<PORTA_IRQn);//disables interrupt
	return 0;
}


int timerfor15s() //approx. 15s timer
{  volatile uint64_t i=0; //34500000
while(i!=31500000) //holds execution till delay is achieved
{
	__asm("NOP");
	i++;
}
return 0;
}
int enablealert()
{
	PORTA->PCR[4] |= PORT_PCR_ISF_MASK; //handles flag
	NVIC->ISER[0] |= (1<<PORTA_IRQn);//sets interrupot

	return 0;
}
statetypes temp_readinghandler()
{
	if(disconnect1())
		return disconnect;
	else
	{
	enablealert();//enables interrupt
	LED_PASS();//green led on
	logstate(state);//displays state
	gettemp();//reads temp
	return average;//next state transition
	}

}

statetypes average_handler()
{
	disablealert();//disables interrupt
	if(disconnect1())
		return disconnect;
	else
	{
		if(timeoutcounter<5) //when 4 timeouts havent occured
		{   LED_PASS();//green led on
		logstate(state);//displays state
		sumtemp=sumtemp+reading; //calculates sum of temperatures in present statemachine
		logtemp(reading); //prints current reading
		avgtemp=(sumtemp)/timeoutcounter;//calculates average of temperatures recorded
		logavgtemp(avgtemp);//prints average temperature
		timerfor15s();//15second delay
		timeoutcounter++;//increments timeout counter

		}
		else //if 4 timeouts have occured
		{
			timeoutcounter=1; //resets counter value
			sumtemp=0; //clears sum of temperatures
			if(sm1) //switches statemachine
			{
				sm1=0;
				sm2=1;
			}
			else if(sm2)
			{
				sm1=1;
				sm2=0;
			}

		}
		return temp_reading; //next state is temp_reading
	}
}
statetypes alert_handler() //alert state handler
{
	disablealert(); //disables interrupt to prevent another interrupt from firing

	LED_PROCESS(); //lights blue led on

	if(disconnect1()) //if sensor disconnected
		return disconnect;
	else//if sensor not disconnected go back to average state
	{
		logstate(state);
		gettemp();// reads temp
		// to show led on

		return average;
	}
}



