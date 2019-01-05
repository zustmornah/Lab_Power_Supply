/**
 * @Author
 * 	 Adom Kwabena
 *
 * @File Name
 *   system.h
 *
 * @Summary
 *   This source file provides APIs for initializing the current project
 *
 * @Description
 *   This code requires TI's driver library from MSP430Ware 3.70.00.05
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/**
 * @Section: Module Definitions
 */

// Delay macros
#define _CLOCK_FREQ 4000000
#define delay_us(x)   __delay_cycles((unsigned long) ((x) * (_CLOCK_FREQ / 1000000.0)))
#define delay_ms(x)   __delay_cycles((unsigned long) ((x) * (_CLOCK_FREQ / 1000.0)))

/**
 * @Section: Module APIs
 */

/**
 * @Summary
 *   This function initializes the clocks to be used by the MCU
 *   This function is not to be called outside of 'system.c'
 *
 * @Param
 *   None
 *
 * @Returns
 *   None
 */
void clocks_initialize(void);

/**
 * @Summary
 *   This function initializes all modules and peripherals used by the project
 *
 * @Param
 *   None
 *
 * @Returns
 *   None
 */
void system_initialize(void);


#endif /* SYSTEM_H_ */
