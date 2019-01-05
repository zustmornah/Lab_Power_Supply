/**
 * @Author
 * 	 Adom Kwabena
 *
 * @File Name
 *   system.c
 *
 * @Summary
 *   This source file provides APIs for initializing the current project
 *
 * @Description
 *   This code requires TI's driver library from MSP430Ware 3.70.00.05
 */

/**
 * @Section: Included Files
 */

#include <driverlib.h>
#include "system.h"
#include "ads8332.h"
#include "dac8411.h"
#include "LCD_driver.h"

/**
 * @Section: Module APIs
 */

void clocks_initialize(void)
{
	// set P5.2 as XT2IN
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN2 + GPIO_PIN4);
	// set P5.3 as XT2OUT
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN3 + GPIO_PIN5);
	// set frequencies of XT1 and XT2 in Hz
	UCS_setExternalClockSource(32768, 4000000);
	// initialize crystals
	UCS_turnOnXT2(UCS_XT2_DRIVE_4MHZ_8MHZ);
	UCS_turnOnLFXT1(UCS_XT1_DRIVE_0, UCS_XCAP_3);
	// use the crystals to set the clocks
	// initialize master clock with a frequency of 4MHz
	UCS_initClockSignal(UCS_MCLK, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_1);
	// initialize sub master clock with a frequency of 1MHz
	UCS_initClockSignal(UCS_SMCLK, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_4);
	// initialize auxilliary clock with a frequency of 32.768KHz
	UCS_initClockSignal(UCS_ACLK, UCS_XT1CLK_SELECT, UCS_CLOCK_DIVIDER_1);
}

void system_initialize(void)
{
	// Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    // Initialize clocks
	clocks_initialize();

    // configure GPIO for LCD
    P2DIR |= BIT2 + BIT3;
    P3DIR |= BIT7;
    P7DIR |= BIT4;
    P8DIR |= BIT1 + BIT2;

    // Initialize LCD
	LCD_Init();
	LCD_PutCmd(_LCD_CURSOR_OFF);
	LCD_PutCmd(_LCD_CLEAR);

	// Initialize ADC
	//ads8332_initialize(CUSTOM_CONFIG_MASK);
	// Initialize DAC
	dac8411_initialize();
}
