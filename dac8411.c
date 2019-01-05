/**
 * @Author
 * 	 Anglaina Hermann
 *
 * @File Name
 *   dac8411.c
 *
 * @Summary
 *   This source file provides APIs for interfacing
 *   with the DAC8411 DAC from Texas Instruments
 *
 * @Description
 *   This code provides an abstraction layer for communicating with the
 *   TI DAC8411 ADC chip
 *   The code requires TI's driver library from MSP430Ware 3.70.00.05
 *
 * @TODO
 * 	 Resolve failure to update DAC8411 issue
 */

/**
 * @Section: Included Files
 */

#include <driverlib.h>
#include <stdint.h>
#include "dac8411.h"
#include "system.h"

/**
 * @Section: Module APIs
 */

void dac8411_initialize(void)
{
	// SPI GPIO Configuration
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2
        );

    // CS or SYNC pin Configuration
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6);

	// Initialize SPI master
	USCI_B_SPI_initMasterParam param = {0};
	param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK;
	param.clockSourceFrequency = UCS_getSMCLK();
	param.desiredSpiClock = 50000;
	param.msbFirst = USCI_B_SPI_MSB_FIRST;
	param.clockPhase = USCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
	//param.clockPhase = 1;
	param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
	//param.clockPolarity = 0;
	USCI_B_SPI_initMaster(USCI_B0_BASE, &param);

	// Enable SPI module
	USCI_B_SPI_enable(USCI_B0_BASE);
}

void dac8411_send_8bits(uint8_t data)
{
	USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
	// Send 8 bits
	// Is TX buffer ready?
	while (!(UCB0IFG & UCTXIFG));
	USCI_B_SPI_transmitData(USCI_B0_BASE, data);

	// Receive 8 bits
	// Wait for the RX interrupt flag to be set
	while (!(UCB0IFG & UCRXIFG));
	uint8_t dummy_data = USCI_B_SPI_receiveData(USCI_B0_BASE);
}

void dac8411_send_data(uint32_t data)
{
	// Format data to be sent
	data = (data << 14) & NORMAL_MODE_MASK;

	// Start SPI transaction
	SYNC_LOW;

	// Send first(MSB) byte
	dac8411_send_8bits((data >> 24));

	// Send second byte
	dac8411_send_8bits((data >> 16));

	// Send last(LSB) byte
	dac8411_send_8bits((data >> 8));

	// End SPI transaction
	SYNC_HIGH;

	// Keep the sync line for at least 1us before starting/bringing it low
	delay_us(1);
}



