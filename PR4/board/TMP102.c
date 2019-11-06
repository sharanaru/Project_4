/*
 * TMP102.c
 *
 *  Created on: 29-Oct-2019
 *      Author: Hp
 */

#include "TMP102.h"
#include "MKL25Z4.h"
#include <fsl_debug_console.h>
#include <stdint.h>

void pause(void)
{
	uint32_t n = 100000;
	while(n!=0)
	{
		n--;
	}
}

void I2C_Init(void)
{
	SIM->SCGC4|= SIM_SCGC4_I2C0_MASK; // I2C0 Gate Enabled

	/* Enable clock for Port E */
	SIM->SCGC5|= SIM_SCGC5_PORTC_MASK;

	/* Port E MUX configuration */
	PORTC->PCR[8] |=  PORT_PCR_MUX(2);//SCL-PTE1-6th
	PORTC->PCR[9] |=  PORT_PCR_MUX(2);//SDA-PTE0-6th


	/*I2C Baud rate selection
    	internal bus speed = 24Mhz
    	Baud Rate = 9600
    	MUL = 0 means the bus speed remains at 24Mhz
    	ICR = 3D is hex for 2560 = 24Mhz/9600
	 */
	I2C0->F = (I2C_F_MULT(0) | I2C_F_ICR(0x11));
	//I2C0->F = (I2C_F_MULT(0) | I2C_F_ICR(0x3B));

	/* Enable I2C module and interrupt */
	I2C0->C1 |= I2C_C1_IICEN_MASK; // Enable I2C, Enable Interrupt | I2C_C1_IICIE_MASK

	I2C0->C2 |= (I2C_C2_HDRS_MASK);
	I2C0->SLTH |= I2C_SLTL_SSLT(0x01);
	/* Enable TX mode */
	//I2C0->C1 |= I2C_C1_TX_MASK;
	// bit-4 TX = 1 means transmit mode

	/* Enable I2C0 NVIC interrupt */
	//Enable_irq(INT_I2C0 - 16);
}


void I2C_Transmit(uint8_t Po_Reg, uint8_t data1, uint8_t data2)
{

	uint32_t x = 100000;
	while(x!=0)
	{
		x--;
	}
	/*PAGE-10 TMP102 datasheet*/
	I2C0->C1 |= I2C_C1_TX_MASK;						// Transmit
	I2C0->C1 |= I2C_C1_MST_MASK;					// Generate START SIGNAL

	//I2C0->D = ((SLAVE_ADDRESS << 1) | READ);		// Write 7-bit Slave Address + READ bit(should be low)

	I2C0->D = 0x90;
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	I2C0->D = Po_Reg;  							// Device register address
	/* Pointer register byte 000000+(00) for temperature register read only  */
	//changed to configuration register
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual


	I2C0->D = data1;							// Send Configuration register byte 1
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	I2C0->D = data2;							// Send Configuration register byte 2
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	I2C0->C1 &=~(I2C_C1_MST_MASK);					//Send stop bit
}

int8_t I2C_Read(uint8_t read_reg)
{
	uint32_t x = 100000;
	while(x!=0)
	{
		x--;
	}

	int8_t data0;
	int8_t data1;
	//uint8_t buffer = 0;
	I2C0->C1 |= I2C_C1_TX_MASK;						// Transmit
	I2C0->C1 |= I2C_C1_MST_MASK;					    // Generate START SIGNAL

	//I2C0->D = ((SLAVE_ADDRESS << 1) | READ);         // Slave address with 8th bit low
	I2C0->D = 0x90;
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	I2C0->D = read_reg;							    // Temperature Register
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	I2C0->C1 |= I2C_C1_RSTA_MASK;					// Restart
	//I2C0->D = ((SLAVE_ADDRESS << 1) | WRITE);		// Slave address with 8th bit high
	I2C0->D = 0x91;
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	I2C0->C1 &= ~I2C_C1_TX_MASK;						// Set as receiver
	I2C0->C1 &= ~I2C_C1_TXAK_MASK; 					// ACK

	data0 = I2C0->D;
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	data0 = I2C0->D;
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	data1 = I2C0->D;
	while((I2C0->S & I2C_S_IICIF_MASK)==0){} 		// Wait for interrupt (1 interrupt pending/0 Not pending)
	I2C0->S |= I2C_S_IICIF_MASK; 					// cleared by writing 1 page 695 manual

	I2C0->C1 |= I2C_C1_TXAK_MASK;						// NACK
	I2C0->C1 &= ~I2C_C1_MST_MASK;					//MASTER STOP

	//buffer = ((data[0]<<8) + (data[1]));
	//PRINTF("\n\r%d   %d",read_reg,data[0]);
	//PRINTF("\n\r%d   %d",read_reg,data[1]);

	//return buffer;

	return data0;
}

// Some function for ALERT Pin on PTC16 GPIO pin



int disconnect1(void)
{
	int8_t check=0;
	check=I2C_Read(TEMP_HIGH_REG);
	if(check!=THIGH_1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void All_Init(void)
{



	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK ;


		PORTA->PCR[4] =PORT_PCR_PS_MASK | PORT_PCR_PE_MASK|PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0C); // Clear MUX bit
		PORTA->PCR[4] |= PORT_PCR_ISF_MASK; // Set PTA4 as GPIO

		I2C_Init();


		pause();
		I2C_Transmit(TEMP_HIGH_REG, THIGH_1, THIGH_2); // Set Temperature High Register

		pause();
		I2C_Transmit(TEMP_LOW_REG, 29 , TLOW_2); // Set Temperature Low Register
		pause();
	    NVIC->ISER[0] |= (1<<PORTA_IRQn);

}


/* void Enable_irq (int irq)
    {
        //Make sure that the IRQ is an allowable number. Up to 32 is used.
         // NOTE: If you are using the interrupt definitions from the header
         //file, you MUST SUBTRACT 16!!!
         //

          // Set the ICPR and ISER registers accordingly
          NVIC_TYPE->ICPR |= 1 << (irq%32);
          NVIC_TYPE->ISER |= 1 << (irq%32);
    }
 */
