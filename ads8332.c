/**
 * @Author
 * 	 Adom Kwabena
 *
 * @File Name
 *   ads8332.c
 *
 * @Summary
 *   This source file provides APIs for interfacing
 *   with the ADS8332 ADC from Texas Instruments
 *
 * @Description
 *   This code provides an abstraction layer for communicating with the
 *   TI ADS8332 ADC chip
 *   The code requires TI's driver library from MSP430Ware 3.70.00.05
 */

/**
 * Section: Included Files
 */

#include <driverlib.h>
#include <stdint.h>
#include "ads8332.h"

/**
 * Section: Module APIS
 */

void ads8332_spi_initialize(void)
{
	// Configure SPI GPIO
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2
        );

    // Configure CS pin
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN3);

	// Initialize SPI master
	USCI_B_SPI_initMasterParam param = {0};
	param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK;
	param.clockSourceFrequency = UCS_getSMCLK();
	param.desiredSpiClock = 50000;
	param.msbFirst = USCI_B_SPI_MSB_FIRST;
	param.clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
	param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
	USCI_B_SPI_initMaster(USCI_B0_BASE, &param);

	// Enable SPI module
	USCI_B_SPI_enable(USCI_B0_BASE);
}

uint8_t ads8322_exchange_8bits(uint8_t data)
{
	USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
	// Send 8 bits
	// Is TX buffer ready?
	while (!(UCB0IFG & UCTXIFG));
	USCI_B_SPI_transmitData(USCI_B0_BASE, data);

	// Receive 8 bits
	// Wait for the RX interrupt flag to be set
	while (!(UCB0IFG & UCRXIFG));
	return USCI_B_SPI_receiveData(USCI_B0_BASE);
}

uint16_t ads8332_exchange_data(uint16_t data)
{
	// Start SPI transaction
	SPI_CS_LOW();

	// Send MSB first
	uint8_t data_MSB = ads8332_exchange_8bits((data >> 8));

	// Send LSB next
	uint8_t data_LSB = ads8332_exchange_8bits(data);

	// End SPI transaction
	SPI_CS_HIGH();

	return (((uint16_t) (data_MSB << 8)) | data_LSB);
}

void ads8332_initialize(uint16_t config_data)
{
	// Initialize SPI module
	ads8332_spi_initialize();

	// Send configuration data
	ads8332_exchange_data((config_data & WRITE_CFR_MASK));
}

/**
 * TODO: ADS8322 doesn't allow channel changing in continuous mode
 *       Enable channel changing in continuous mode by editing
 *       the 'ads8332_get_conversion' function
 */

uint16_t ads8332_get_conversion(uint16_t channel)
{
	return ads8332_exchange_data(channel);
}
