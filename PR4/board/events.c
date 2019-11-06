#include "events.h"
#include "loggers.h"
#include "TMP102.h"

statetypes disconnectcheck()
{
	while(disconnect1())
	{
	printf("Sensor disconnected");
	LED_FAIL();
	}
	return temp_reading;
}
int gettemp()
{
	LED_PASS();
	reading=I2C_Read(TEMP_REG);
	//sumtemp+=reading;
	return 0;
}
int disablealert()
{
	PORTA->PCR[4] |= PORT_PCR_ISF_MASK; //PORT_ISFR_ISF(0x40);

	NVIC->ICER[0] |=(1<<PORTA_IRQn);
	return 0;
}
int timeout()
{
	LED_PASS();
	disablealert();
	if(timeoutcounter<5)
	{
		logstate(state);
		sumtemp=sumtemp+reading;
		logtemp(reading);
		//printf(reading);
		avgtemp=(sumtemp)/timeoutcounter;
		//printf(avgtemp);
		logavgtemp(avgtemp);
		timerfor15s();

		timeoutcounter++;
		printf("timeout value is %d\n",timeoutcounter);
	}
	else
	{
		sm2=0;
		sm1=1;
		printf("sm1 %d\n",sm1);
		sumtemp=0;avgtemp=0;
	}
	enablealert();
	return 0;
}
//statetypes complete(statetypes state)
//{
//
//
//	if(state==disconnect)
//		return temp_reading;
//	if(state==temp_reading)
//		return average;
//	if(state==temp_alert)
//		return average;
//	if((state==average) && (timeoutcounter<6))
//	{
//		return temp_reading;
//
//	}
//
//}
int timerfor15s()
{  volatile uint64_t i=0; //34500000
while(i!=345000) //holds execution till delay is achieved
{
	__asm("NOP");
	i++;
}
return 0;
}
int enablealert()
{
	PORTA->PCR[4] |= PORT_PCR_ISF_MASK;
	NVIC->ISER[0] |= (1<<PORTA_IRQn);

	return 0;
}
statetypes temp_readinghandler()
{
	if(disconnect1())
		return disconnect;
	else
	{   enablealert();
		logstate(state);
		gettemp();
		return average;
	}

}

statetypes average_handler()
{
	disablealert();
	if(disconnect1())
		return disconnect;
	else
	{
		if(timeoutcounter<5)
		{   LED_PASS();
			logstate(state);
			sumtemp=sumtemp+reading;
			logtemp(reading);
			avgtemp=(sumtemp)/timeoutcounter;
			logavgtemp(avgtemp);
			timerfor15s();
			timeoutcounter++;

		}
		else
		{
			timeoutcounter=1;
			sumtemp=0;
			if(sm1)
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
	return temp_reading;
	}
}
statetypes alert_handler()
{
	disablealert();
	gettemp();
	LED_PROCESS();
	if(disconnect1())
		return disconnect;
	else
	{
		logstate(state);
		return average;
	}
}



