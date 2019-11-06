/*
 * TMP102.h
 *
 *  Created on: 28-Oct-2019
 *      Author: Hp
 */

#ifndef TMP102_H_
#define TMP102_H_

#include <stdint.h>


#endif /* TMP102_H_ */

#define SLAVE_ADDRESS 0x48
#define WRITE	0x01 // Read/Write bit according to TMP102-Check during execution
#define	READ	0x00
#define TEMP_REG 0x00
#define CONFIG_REG 0x01
#define CONFIG_BYTE1 0x6E // CR Byte1 - Faults = 6 // Interrupt Alert
#define CONFIG_BYTE2 0xA0 // Configuration register byte 2 // Alert Bit Set
#define TEMP_LOW_REG 0x02    // Temp Low register
#define TEMP_HIGH_REG 0x03    // Temp  register
#define THIGH_1 29          // 24C18
#define THIGH_2 0x00   //200-C8
#define TLOW_1 29   //22C16,27C1B
#define TLOW_2 0x00    //128
#define ALERT_PIN 17 //PTC17 set as alert input pin
#define MASK(x)(1UL << (x))
#define RED_LED_POS (18)


void I2C_Init(void); // Initialise I2C
void I2C_Transmit(uint8_t Po_Reg, uint8_t data1, uint8_t data2); // I2C transmit in Master mode
int8_t I2C_Read(uint8_t read_reg); //I2C Read - Working
void pause(void); // Some delay

int disconnect1(void);
void All_Init(void);
