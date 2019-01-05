/**
 * @Authors
 * 	 Adom Kwabena
 *
 * @File Name
 *   LCD_driver.h
 *
 * @Summary
 *   This header file provides APIs for interfacing with the HD44780 LCD controller chip
 *
 * @Description
 *   This code supports 2x16 LCDs only and the interface used is the 4-bit interface
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

/**
 * Section: MOdule Definitions
 */

// Hardware Abstraction
#define LCD_RS          BIT2
#define LCD_EN          BIT4
#define LCD_D4          BIT3
#define LCD_D5          BIT1
#define LCD_D6          BIT2
#define LCD_D7          BIT7

// Some Handy LCD commands
#define DATA                0
#define COMMAND             1
#define _LCD_CLEAR          0x01
#define _LCD_CURSOR_OFF     0x0C
#define _LCD_CURSOR_ON      0x0D
#define _LCD_HOME           0x02
#define _LCD_HOME_2         0xA8
#define _LCD_SHIFT_LEFT     0x18
#define _LCD_SHIFT_RIGHT    0X1C

/**
 * Section: Module APIs
 */

/**
 * @Summary
 *   This function writes 4 bits of data to the LCD
 *
 * @Param
 *   nibble - data to be seent
 *
 * @Param
 *   register_select - selects register to which data is written
 *
 * @Returns
 *   None
 */
void LCD_Write(const char nibble, int reg_select);

/**
 * @Summary
 *   This function initializes the LCD
 *
 * @Param
 *   None
 *
 * @Returns
 *   None
 */
void LCD_Init(void);

/**
 * @Summary
 *   This function sends a single byte command to the LCD
 *
 * @Param
 *   c - command to be sent
 *
 * @Returns
 *   None
 */
void LCD_PutCmd(const char c);

/**
 * @Summary
 *   This function displays a character at the current cursor position
 *
 * @Param
 *   c - character to be displayed
 *
 * @Returns
 *   None
 */
void LCD_PutChar_Cp(const char c);

/**
 * @Summary
 *   This function displays a string on the LCD
 *   The string is displayed at the current cursor position
 *
 * @Param
 *   s - pointer to the string to be displayed
 *
 * @Returns
 *   None
 */
void LCD_PutString_Cp(const char *s);

/**
 * @Summary
 *   This function displays a character on the LCD
 *   The character is displayed at a user specified location
 *
 * @Param
 *   row - select row to display data
 *
 * @Param
 *   column - select column to display data
 *
 * @Param
 *   c - character to be displayed
 *
 * @Returns
 *   None
 */
void LCD_PutChar(int row, int column, const char c);

/**
 * @Summary
 *   This function displays a string of characters on the LCD
 *   The user specifies the location at which to begin displaying data
 *
 * @Param
 *   row - select row to begin displaying data
 *
 * @Param
 *   column - select column to begin displaying data
 *
 * @Param
 *   s - pointer to the string to be displayed
 *
 * @Returns
 *   None
 */
void LCD_PutString(int row, int column, const char *s);


#endif /* LCD_DRIVER_H_ */
