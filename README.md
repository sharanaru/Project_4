
# Project 4 PES - Readme

Team Members: 
Sharan Arumugam
Abhijeet Srivastava

# Execution Instructions
+ Using custom build configuration this time, to compile for different modes. As always ,please run clean before building a new configuration. 
+ 3 Configurations : Debug, Normal, Test
**+ COMPILER COMMANDS**
+ *For building Debug config :* 
arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -Dddebug -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"source/t1.d" -MT"source/t1.o" -MT"source/t1.d" -o "source/t1.o" "../source/t1.c"
+ *For building Normal config :* 
arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DNORMAL -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"source/t1.d" -MT"source/t1.o" -MT"source/t1.d" -o "source/t1.o" "../source/t1.c"
+ *For building TEST config :* 
arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DTEST -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"source/t1.d" -MT"source/t1.o" -MT"source/t1.d" -o "source/t1.o" "../source/t1.c"



# Files in Repo
+ MCU XPRESSO Project Directory
     + Board Folder: Contains regular board files plus
	    + events.h/.c: These contain the state machine functions
		+ led_board.h/.c These contain the LED functions
	    + TMP102.h/.c These contain the I2C functions 
	    + System .h/.c, Testsuite.h/.c, uCUnit-v1.0 These are the files needed for running                  the unit tests  
     + Source Folder - Contains main routine - PR4.c
	
     + Default folders with no change -CMSIS,startup,drivers,utilities
     + Debug - Contains .o files after compilation and also contains .axf binary and .exe files
+ Readme 
+ I2C-Screenshots (contains screenshots of i2c transactions)


## Issues faced

+ The I2C write transaction and the read transaction were happening when done individually and not   together. This problem was solved by putting a small delay between each transactions. 
+ Interrupt on both board and sensor had to be configured differently. On Senor, interrupt had to be set to comparator mode, which both high and low temp being set as same temp to trigger alert for out requirement of a single critical temperature
 
## References
+ Slack channel for clearing up questions on function definitions
+ https://e2e.ti.com/support/sensors/f/1023/t/503810
+ https://community.nxp.com/thread/357858
+ https://community.nxp.com/thread/389714

```
