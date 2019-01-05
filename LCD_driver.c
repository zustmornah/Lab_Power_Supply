/**
 * @Author
 * 	 Adom Kwabena
 *
 * @File Name
 *   LCD_driver.c
 *
 * @Summary
 *   This source file provides APIs for interfacing with the HD44780 LCD controller chip
 *
 * @Description
 *   This code supports 2x16 LCD only and the interface used is the 4-bit interface
 */

/**
 * Section: Included Files
 */

#include <stdint.h>
#include <msp430.h>
#include "system.h"		// Contains delay macros
#include "LCD_driver.h"

/**
 * Section: Module APIs
 */

void LCD_Write(const char nibble, int reg_select)
{
    if ((nibble & 0x08) || (nibble & 0x80))
    {
        P3OUT |= LCD_D7;
    }
    else
    {
        P3OUT &= ~LCD_D7;
    }
    if ((nibble & 0x04) || (nibble & 0x40))
    {
        P8OUT |= LCD_D6;
    }
    else
    {
        P8OUT &= ~LCD_D6;
    }
    if ((nibble & 0x02) || (nibble & 0x20))
    {
        P8OUT |= LCD_D5;
    }
    else
    {
        P8OUT &= ~LCD_D5;
    }
    if ((nibble & 0x01) || (nibble & 0x10))
    {
        P2OUT |= LCD_D4;
    }
    else
    {
        P2OUT &= ~LCD_D4;
    }
    if (reg_select == COMMAND)
    {
        P2OUT &= ~LCD_RS;
    }
    else if (reg_select == DATA)
    {
        P2OUT |= LCD_RS;
    }
    delay_us(2);
    P7OUT |= LCD_EN;
    delay_us(2);
    P7OUT &= ~LCD_EN;
}

void LCD_Init(void)
{
    delay_ms(15);
    LCD_Write(0x03, COMMAND);
    delay_ms(5);
    LCD_Write(0x03, COMMAND);
    delay_ms(5);
    LCD_Write(0x03, COMMAND);
    delay_ms(5);

    LCD_Write(0x02, COMMAND);   // start operation in 4 bit mode
    delay_ms(1);
    LCD_Write(0x02, COMMAND);   // 0 0 1 DL
    LCD_Write(0x08, COMMAND);   // N F * *, number of lines and character font
    delay_ms(1);
    LCD_Write(0x00, COMMAND);
    LCD_Write(0x08, COMMAND);   // Turn display off
    delay_ms(1);
    LCD_Write(0x00, COMMAND);
    LCD_Write(0x01, COMMAND);   // Clear display
    delay_ms(2);
    LCD_Write(0x00, COMMAND);
    LCD_Write(0x06, COMMAND);   // Set entry mode
    delay_ms(2);

    // Turn on LCD display
    LCD_Write(0x00, COMMAND);
    LCD_Write(0x0C, COMMAND);
    delay_ms(1);

    // Return Cursor Home
    LCD_Write(0x00, COMMAND);
    LCD_Write(0x02, COMMAND);
    delay_ms(3);
}

void LCD_PutCmd(const char c)
{
    LCD_Write(c & 0xF0, COMMAND);
    LCD_Write(c & 0x0F, COMMAND);
    delay_ms(5);
}

void LCD_PutChar_Cp(const char c)
{
    LCD_Write(c & 0xF0, DATA);
    LCD_Write(c & 0x0F, DATA);
    delay_us(100);
}

void LCD_PutString_Cp(const char *s)
{
    while (*s)
    {
        LCD_PutChar_Cp(*s++);
    }
}

void LCD_PutChar(int row, int column, const char c)
{
    if (1 == row)
    {
        LCD_PutCmd((row + column - 2) | 0x80);
    }
    else if (2 == row)
    {
        if (column <= 10)
        {
            LCD_PutCmd((row + column + 37) | 0x80);
        }
        else
        {
            LCD_PutCmd((row + column + 61) | 0x80);
        }
    }
    LCD_PutChar_Cp(c);
}

void LCD_PutString(int row, int column, const char *s)
{
    if (1 == row)
    {
        LCD_PutCmd((row + column - 2) | 0x80);
    }
    else if (2 == row)
    {
        if (column <= 10)
        {
            LCD_PutCmd((row + column + 37) | 0x80);
        }
        else
        {
            LCD_PutCmd((row + column + 61) | 0x80);
        }
    }
    while (*s)
    {
        LCD_PutChar_Cp(*s++);
    }
}



