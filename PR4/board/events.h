#include<stdio.h>
#include "TMP102.h"
#include "led_board.h"
 extern int8_t sumtemp;
extern uint8_t timeoutcounter;
extern int8_t avgtemp;
extern int8_t reading;

typedef enum {
disconnect=0,
temp_reading,
average,
temp_alert
}statetypes;
extern statetypes state;
volatile extern int sm1;//starting with state machine 1
volatile extern int sm2;
int disconnect1(void);
//int disconnectcheck();
int timerfor15s();
int gettemp();
int disablealert();
int enablealert();
int timeout();
statetypes complete(statetypes state);
statetypes disconnectcheck();
statetypes temp_readinghandler();
statetypes average_handler();
statetypes alert_handler();
