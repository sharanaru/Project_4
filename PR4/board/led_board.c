#include "led_board.h"
#include "board.h"

void delay()
{
volatile uint64_t i=0;
while(i!=190000) //holds execution till delay is achieved
{ __asm("NOP");
i++;
  }
}
//only for kl25z

void LED_Initialise()
{
	LED_BLUE_INIT(1);
	LED_RED_INIT(1);
	LED_GREEN_INIT(1);
}
void ALLLED_OFF()
{
	LED_BLUE_OFF();
	LED_RED_OFF();
	LED_GREEN_OFF();
}
void LED_PASS()
{
ALLLED_OFF();
LED_GREEN_ON();
#ifdef ddebug
printf("led green on");
#endif
delay();
}
void LED_PROCESS()
{
ALLLED_OFF();
LED_BLUE_ON();
#ifdef ddebug
printf("led blue on");
#endif
delay();
}
void LED_FAIL()
{
	ALLLED_OFF();
	LED_RED_ON();
#ifdef ddebug
printf("led red on");
#endif
	delay();
}

