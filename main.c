/**
 * @Authors
 * 	 Adom Kwabena, Anglaina Hermann
 *
 * @File Name
 *   main.c
 *
 * @Summary
 *   This source file contains the implementation of the project
 *
 * @Description
 *   This code requires TI's driver library from MSP430Ware 3.70.00.05
 */

/**
 * @Section: Included Files
 */

#include <driverlib.h>
#include <stdint.h>
#include "LCD_driver.h"
#include "system.h"
#include "ads8332.h"
#include "dac8411.h"
#include "ftoa.h"


/**
 * @Section: Main Application
 */

//uint16_t adc_data = 0x0000;
//float measured_voltage = 0;

void main(void)
{
	system_initialize();

	//char s[16];
	uint32_t voltage[6] = {0x9C40, 0xDAC0, 0x1F40, 0xFA00, 0x3E80, 0x5DC0};

	while (1)
	{
		uint8_t i;
		for (i = 0; i < 6; i++)
		{
			dac8411_send_data(voltage[i]);
			//delay_ms(5);
			//adc_data = ads8332_get_conversion(SELECT_CHANNEL_1);
			//measured_voltage = 4.096 * (adc_data  / 65535.0);
			//float_to_string(measured_voltage, s);
			//LCD_PutString(1, 1, "V: ");
			//LCD_PutString(1, 4, "          ");
			//LCD_PutString(1, 4, s);

			delay_ms(1000);
		}
	}
}
