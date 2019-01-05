/**
 * @Author
 * 	 Anglaina Hermann
 *
 * @File Name
 *   dac8411.h
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

#ifndef DAC_8411_H_
#define DAC_8411_H_

/**
 * @Section: Module Definitions
 */

// Hardware abstraction for SPI chip select
#define SYNC_LOW			P2OUT &= !BIT6
#define SYNC_HIGH			P2OUT |= BIT6

//Mask for normal operation
#define NORMAL_MODE_MASK		0x3FFFFFFF

/**
 * @Section: Module APIs
 */

/**
 * @Summary
 *   This function initializes the spi module for the DAC (DAC8411)
 *
 * @Param
 *   None
 *
 * @Returns
 *   None
 */
void dac8411_initialize(void);

/**
 * @Summary
 *   This function sends 8bits of data to the DAC (DAC8411)
 *
 *  @Param
 *    data - data to be sent to DAC (DAC8411)
 *
 *  @Returns
 *    None
 */
void dac8411_send_8bits(uint8_t data);

/**
 * @Summary
 *   This function sends 24bits of data to the DAC (DAC8411)
 *
 * @Param
 *   data - data to be sent to DAC (DAC8411)
 *
 * @Returns
 *   None
 */
void dac8411_send_data(uint32_t data);


#endif /* DAC_8411_H_ */
