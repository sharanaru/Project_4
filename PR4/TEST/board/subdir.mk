################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/System.c \
../board/TMP102.c \
../board/Testsuite.c \
../board/board.c \
../board/clock_config.c \
../board/events.c \
../board/led_board.c \
../board/peripherals.c \
../board/pin_mux.c 

OBJS += \
./board/System.o \
./board/TMP102.o \
./board/Testsuite.o \
./board/board.o \
./board/clock_config.o \
./board/events.o \
./board/led_board.o \
./board/peripherals.o \
./board/pin_mux.o 

C_DEPS += \
./board/System.d \
./board/TMP102.d \
./board/Testsuite.d \
./board/board.d \
./board/clock_config.d \
./board/events.d \
./board/led_board.d \
./board/peripherals.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DTEST -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


