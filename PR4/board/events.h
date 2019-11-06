/*Functions and events to be carried out in each state machine
 Authors- Sharan Arumugam and Abhijeet
*/
#include<stdio.h>
#include "TMP102.h"
#include "led_board.h"
#include "loggers.h"
#include "TMP102.h"
#include "Testsuite.h"
#include "uCUnit-v1.0.h"
#include "System.h"
extern int8_t sumtemp; //calculates sum of temperatures read in a specific statemachine
extern uint8_t timeoutcounter;//tracks no. of timeouts
extern int8_t avgtemp;//records average temp
extern int8_t reading;//records present reading
//State types that can be found
typedef enum {
disconnect=0,//When sensor is disconnected
temp_reading,//When sensor value is read
average,//where average is calculated and displayed
temp_alert//when temperature goes below 0 deg C
}statetypes;
extern statetypes state;
volatile extern int sm1;//starting with state machine 1
volatile extern int sm2;//sm2 flag
int timerfor15s();//counts for 15s
int gettemp();//reads temp from sensor
int disablealert();//disables interrupt
int enablealert();//enables interrupt
//all of the below functions return the next state to be executed
statetypes disconnectcheck(); //handles operations to be carried out in disconnect state
statetypes temp_readinghandler();//handles operations to be carried out in temp_reading state
statetypes average_handler();//handles operations to be carried out in average state
statetypes alert_handler();//handles operations to be carried out in alert state
