/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Project: 		Post 8 MCP23017 I2C Expander
 * Hardware:		Arduino UNO
 * Micro:			ATMEGA328P
 * IDE:			Atmel Studio 6.2
 *
 * Name:    		main.c
 * Purpose: 		Experimenting with the MCP23017 I2C Expander
 * Date:			28-10-2015
 * Author:		Marcel van der Ven
 *
 * Hardware setup:		
 * Note(s):
 *--------------------------------------------------------------------------------------------------------------------------------------------------------*/

/************************************************************************/
/* Defines				                                                */
/************************************************************************/
#define F_CPU							16000000UL
#define IO_EXPANDER_ADDRESS_7BIT		0x20		/* 7-bit address */

/************************************************************************/
/* Includes				                                                */
/************************************************************************/
#include <avr/io.h>
#include "util/delay.h"
#include "common.h"
#include "mcp23017.h"

/***************************************************************************
*  Function:		Setup()
*  Description:		Setup the TWI of the ATMEGA328P.
*  Receives:		Nothing
*  Returns:			Nothing
***************************************************************************/
void Setup()
{
	 /* Setup TWI (I2C) */
	 
	 
	 
	 /* Setup the two interrupt lines coming from the IO Expander */
	 /* These are connected to PORTB0 (for interrupt on PORTA) and PORTB1 (for an interrupt on PORTB) */
	 /* We set all pins of DDRB as input. */
	 DDRB = 0x00;
}

/***************************************************************************
*  Function:		SetupIoExpander()
*  Description:		Setup the IO Expander, we don't care about the previous values of the
*					register, this function should therefore only called to setup the chip.
*  Receives:		Nothing
*  Returns:			Nothing
***************************************************************************/
void SetupIoExpander()
{
	/* Initialize the IO Expander */
	InitializeIoExpander(IO_EXPANDER_ADDRESS_7BIT, BANK0);
	
	/* Set pin 1 of PORTA and PORTB of the IO Expander as output (output = 0) */
	/* And the rest of the pins as input */
	SetPortDirectionReg(MCP23017_PORTA, 0xFE);
	SetPortDirectionReg(MCP23017_PORTB, 0xFE);
	
	/* For the two pushbutton-inputs enable the interrupt on change feature */
	/* The two pushbuttons are connected to pin 1 of PORTA and PORTB */
	SetIntOnChangeReg(MCP23017_PORTA, 0x02);
	SetIntOnChangeReg(MCP23017_PORTB, 0x02);
	
	/* The pushbuttons will pull the line low when pressed, */
	/* so set the bit 1 in DEFVAL register for each port */
	/* The DEFVAL register contains the compare value of the pin, if the value of the pin is */
	/* different then in the DEFVAL register a interrupt is generated. */
	SetDefaultCompareReg(MCP23017_PORTA, 0x02);
	SetDefaultCompareReg(MCP23017_PORTB, 0x02);
	
	/* Configure when the interrupt is generated */
	/* We have set DefaultCompare register so we generate the interrupt when the pin' value is not */
	/* equal to the value in the Default Compare register */
	SetIntControlReg(MCP23017_PORTA, 0x02);
	SetIntControlReg(MCP23017_PORTB, 0x02);
	
	/* Set the configuration of the chip, we use the default bank and we set the INTPOL bit */
	/* So the interrupt for PORTA and PORTB is high-active */
	SetIoConfigReg(MCP23017_PORTA, 0x01);
	
	/* Set the pull-up resistors for the two pushbutton-inputs */
	SetPullupConfigReg(MCP23017_PORTA, 0x02);
	SetPullupConfigReg(MCP23017_PORTB, 0x02);
}

/***************************************************************************
*  Function:		Main(void)
*  Description:		Main function of the program.
*  Receives:		Nothing
*  Returns:		Optionally the exit code.
***************************************************************************/
int main(void)
{
	/* Setup and initialization */
	Setup();
	SetupIoExpander();

    while (1) 
    {
    }
}

