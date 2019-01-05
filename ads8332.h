/**
 * @Author
 * 	 Adom Kwabena
 *
 * @File Name
 *   ads8332.h
 *
 * @Summary
 *   This header file provides APIs for interfacing
 *   with the ADS8332 ADC from Texas Instruments
 *
 * @Description
 *   This code provides an abstraction layer for communicating with the
 *   TI ADS8332 ADC chip
 *   The code requires TI's driver library from MSP430Ware 3.70.00.05
 */

#ifndef ADS8332_H_
#define ADS8332_H_

/**
 * Section: Module Definitions
 */

// Hardware abstraction for SPI chip select
#define SPI_CS_LOW()		P3OUT &= !BIT3
#define SPI_CS_HIGH()		P3OUT |= BIT3

// ADS8332 command set
#define SELECT_CHANNEL_0	0x0000
#define SELECT_CHANNEL_1	0x1000
#define SELECT_CHANNEL_2	0x2000
#define SELECT_CHANNEL_3	0x3000
#define SELECT_CHANNEL_4	0x4000
#define SELECT_CHANNEL_5	0x5000
#define SELECT_CHANNEL_6	0x6000
#define SELECT_CHANNEL_7	0x7000
#define WAKE_UP				0xB000
#define READ_CFR			0xC000
#define READ_DATA			0xD000
#define WRITE_CFR_MASK		0xEFFF
#define DEFAULT_MODE		0xF000

// Custom configuration data
#define CUSTOM_CONFIG_MASK	0xF4FD

/**
 * Section: Module APIs
 */

/**
 * @Summary
 *   This function initializes the spi module
 *
 * @Param
 *   None
 *
 * @Returns
 *   None
 */
void ads8332_spi_initialize(void);

/**
 * @Summary
 *   This function exchanges 8 bits of data between
 *   the ADS8322 ADC and the caller
 *
 *  @Param
 *    data - 8 bits of data to be sent to the ADC (ADS8322)
 *
 *  @Return
 *    8 bits of data from the ADC (ADS8322)
 */
uint8_t ads8332_exchange_8bits(uint8_t data);

/**
 * @Summary
 * 	 This functions exchanges 16 bits of data between
 * 	 the ADS8332 ADC and the caller
 *
 * @Param
 *   data - 16 bits of data to be sent to the ADC (ADS8332)
 *
 * @Returns
 * 	 16 bits of data from the ADC (ADS8332)
 */
uint16_t ads8332_exchange_data(uint16_t data);

/**
 * @Summary
 *   This function initializes the ADS8332 ADC
 *
 * @Param
 *   config_data - Data that determines the mode of operation of the ADC
 *
 * @Returns
 *   None
 *
 */
void ads8332_initialize(uint16_t config_data);

/**
 * @Summary
 * 	 This function acquires conversion data from the ADC (ADS8322)
 *
 * @Param
 *   channel - The ADC channel from which the conversion is required
 *
 * @Returns
 * 	 ADC conversion result
 */
uint16_t ads8332_get_conversion(uint16_t channel);


#endif /* ADS8332_H_ */
