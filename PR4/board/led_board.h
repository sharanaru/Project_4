//PES Project3 - Sharan Arumugam and Abhijeet ( LEd routines)
#include<stdio.h>
#include<stdint.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "MKL25Z4.h"
//all functions dependent on platform
void LED_Initialise(); //depending on platform led initialises or does nothing
void ALLLED_OFF();//switches all led off
void LED_PASS();//switches on green led and all others off
void LED_PROCESS();//switches on blue led and others off
void LED_FAIL();//switches on red led and others off
void DELAY();//delay to create halt in order to observe led status

