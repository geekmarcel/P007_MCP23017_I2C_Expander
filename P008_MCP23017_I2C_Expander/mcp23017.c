/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Project:			MCP23017 TWI Library	
 * Hardware:		Arduino UNO
 * Micro:			ATMEGA328P
 * IDE:				Atmel Studio 6.2
 *
 * Name:    		mcp23017.c
 * Purpose: 		MCP23017 TWI Library
 * Date:			28-10-2015
 * Version:			1.0	
 * Author:			Marcel van der Ven
 *
 *
 * Note(s):
 *--------------------------------------------------------------------------------------------------------------------------------------------------------*/

/************************************************************************/
/* Defines
/************************************************************************/
#define F_CPU			16000000UL


/************************************************************************/
/* Includes
/************************************************************************/
#include <avr/io.h>
#include "util/delay.h"
#include "mcp23017.h"
#include "string.h"


/************************************************************************/
/* Structures
/************************************************************************/
struct MCP23017
{
	BYTE address;
	BankInUse bank;
	
	/* Specifies if the IO Expander is initialized */
	BOOL isInitialized;
	
}mcp23017;


/************************************************************************/
/* Functions
/************************************************************************/	

/***************************************************************************
*  Function:		SetPortDirection(MCP23017_Port port, BYTE value)
*  Description:		Sets the direction port register. When a bit is set the corresponding
*				pin becomes an input and when its cleared the pin becomes an output.
*  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
*				BYTE value			:	The value to set.
*  Returns:		Nothing
***************************************************************************/
void InitializeIoExpander(BYTE address, BankInUse bank)
{
	mcp23017.address = address;
	mcp23017.bank = bank;
	
	/* Initialization finished, set flag */
	mcp23017.isInitialized = TRUE:
}

/***************************************************************************
  Function:		SetPortDirection(MCP23017_Port port, BYTE value)
  Description:	Sets the direction port register. When a bit is set the corresponding
				pin becomes an input and when its cleared the pin becomes an output.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
				BYTE value				:	The value to set.
  Returns:		Nothing
***************************************************************************/
void SetPortDirectionReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_IODIRA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_IODIRB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_IODIRA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_IODIRB_BANK1, value);
		}
	}
}

/***************************************************************************
  Function:		BYTE ReadPortDirection(MCP23017_Port port)
				Bits which are set are inputs, and bit that are cleared are outputs.
  Description:	Reads the direction port register.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
  Returns:		Byte that was read.
***************************************************************************/
BYTE ReadPortDirectionReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_IODIRA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_IODIRB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_IODIRA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_IODIRB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
  Function:		SetPortPolarity(MCP23017_Port port, BYTE value)
  Description:	Sets the port polarity register, when the corresponding bit is set
				the GPIO register bit will reflect the inverted value of the pin.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
				BYTE value				:	The value to set.
  Returns:		Nothing
***************************************************************************/
void SetPortPolarityReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_IPOLA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_IPOLB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_IPOLA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_IPOLB_BANK1, value);
		}
	}
}

/***************************************************************************
  Function:		BYTE ReadPortDirection(MCP23017_Port port)
  Description:	Reads the input polarity register.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
  Returns:		Byte that was read.
***************************************************************************/
BYTE ReadPortPolarityReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_IPOLA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_IPOLB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_IPOLA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_IPOLB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
  Function:		SetIntOnChange(MCP23017_Port port, BYTE value)
  Description:	Sets the interrupt-on-change register, if a bit is set the
				corresponding pin is enabled for interrupt-on-change.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
				BYTE value				:	The value to set.
  Returns:		Nothing
***************************************************************************/
void SetIntOnChangeReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_GPINTENA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_GPINTENB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_GPINTENA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_GPINTENB_BANK1, value);
		}
	}
}

/***************************************************************************
  Function:		BYTE ReadIntOnChange(MCP23017_Port port)
  Description:	Reads the interrupt-on-change register.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
  Returns:		Byte that was read.
***************************************************************************/
BYTE ReadIntOnChangeReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_GPINTENA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_GPINTENB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_GPINTENA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_GPINTENB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
  Function:		SetDefaultCompareReg(MCP23017_Port port, BYTE value)
  Description:	Sets the default compare register, these bits set the compare value
				for pins configured for interrupt-on-change, if the associated pin
				level is the opposite from the register bit, an interrupt occurs.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
				BYTE value				:	The value to set.
  Returns:		Nothing
***************************************************************************/
void SetDefaultCompareReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_DEFVALA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_DEFVALB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_DEFVALA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_DEFVALB_BANK1, value);
		}
	}
}

/***************************************************************************
  Function:		BYTE ReadDefaultCompareReg(MCP23017_Port port)
  Description:	Reads the default compare register for interrupt-on-change.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
  Returns:		Byte that was read.
***************************************************************************/
BYTE ReadDefaultCompareReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_DEFVALA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_DEFVALB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_DEFVALA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_DEFVALB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
  Function:		SetIntControlReg(MCP23017_Port port, BYTE value)
  Description:	Sets the interrupt control register, this register controls how the associated
				pin value is compared for the interrupt-on-change.
				If a bit is set, the corresponding IO pin is compared against the
				associated bit in the DEFVAL register.
				If a bit value is clear, the corresponding IO pin is compared against the previous value.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
				BYTE value				:	The value to set.
  Returns:		Nothing
***************************************************************************/
void SetIntControlReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_INTCONA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_INTCONB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_INTCONA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_INTCONB_BANK1, value);
		}
	}
}

/***************************************************************************
  Function:		BYTE ReadIntControlReg(MCP23017_Port port)
  Description:	Reads the interrupt control register.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
  Returns:		Byte that was read.
***************************************************************************/
BYTE ReadIntControlReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_INTCONA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_INTCONB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_INTCONA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_INTCONB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
  Function:		SetIoConfigReg(MCP23017_Port port, BYTE value)
  Description:	Sets the IO Expander Configuration register, this register contains settings
				that determine how the IO Expander behaves.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
				BYTE value				:	The value to set.
  Returns:		Nothing
***************************************************************************/
void SetIoConfigReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_IOCONA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_IOCONB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_IOCONA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_IOCONB_BANK1, value);
		}
	}
}

/***************************************************************************
  Function:		BYTE ReadIntControlReg(MCP23017_Port port)
  Description:	Reads the IO Expander Configuration register.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
  Returns:		Byte that was read.
***************************************************************************/
BYTE ReadIoConfigReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_IOCONA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_IOCONB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_IOCONA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_IOCONB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
  Function:		SetPullupConfigReg(MCP23017_Port port, BYTE value)
  Description:	Sets the pull-up resistor configuration register, if a bit is set
				and the corresponding pin is configured as an input the corresponding
				port pin is internally pulled up with a 100 kOhm resistor.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
				BYTE value				:	The value to set.
  Returns:		Nothing
***************************************************************************/
void SetPullupConfigReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_GPPUA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_GPPUB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			TwiSend(address, MCP23017_GPPUA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			TwiSend(address, MCP23017_GPPUB_BANK1, value);
		}
	}
}

/***************************************************************************
  Function:		BYTE ReadPullupConfigReg(MCP23017_Port port)
  Description:	Reads pull-up configuration register.
  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
  Returns:		Byte that was read.
***************************************************************************/
BYTE ReadPullupConfigReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_GPPUA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_GPPUB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = twi_read1byte(address, MCP23017_GPPUA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = twi_read1byte(address, MCP23017_GPPUB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
*  Function:		BYTE ReadInterruptFlagReg(MCP23017_Port port)
*  Description:		The INTF register reflects the interrupt condition on the
*					port pins of any pin that is enabled for interrupts via the
*					GPINTEN register. A set bit indicates that the
*					associated pin caused the interrupt.
*					This is a read-only register.
*  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
*  Returns:			Byte that was read.
***************************************************************************/
BYTE ReadInterruptFlagReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = i2c_read1byte(address, MCP23017_INTFA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = i2c_read1byte(address, MCP23017_INTFB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = i2c_read1byte(address, MCP23017_INTFA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = i2c_read1byte(address, MCP23017_INTFB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
*  Function:		BYTE ReadInterruptCaptureReg(MCP23017_Port port)
*  Description:		The INTCAP register captures the GPIO port value at
*					the time the interrupt occurred. The register is read
*					only and is updated only when an interrupt occurs. The
*					register will remain unchanged until the interrupt is
*					cleared via a read of INTCAP or GPIO.
*  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
*  Returns:			Byte that was read.
***************************************************************************/
BYTE ReadInterruptCaptureReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = i2c_read1byte(address, MCP23017_INTCAPA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = i2c_read1byte(address, MCP23017_INTCAPB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = i2c_read1byte(address, MCP23017_INTCAPA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = i2c_read1byte(address, MCP23017_INTCAPB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
*  Function:		SetPortReg(MCP23017_Port port, BYTE value)
*  Description:		The GPIO register reflects the value on the port.
*					Reading from this register reads the port. Writing to this
*					register modifies the Output Latch (OLAT) register.
*  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
*					BYTE value				:	The value to set.
*  Returns:			Nothing
***************************************************************************/
void SetPortReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			i2c_send(address, MCP23017_GPIOA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			i2c_send(address, MCP23017_GPIOB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			i2c_send(address, MCP23017_GPIOA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			i2c_send(address, MCP23017_GPIOB_BANK1, value);
		}
	}
}
/***************************************************************************
*  Function:		BYTE ReadPortReg(MCP23017_Port port)
*  Description:		The GPIO register reflects the value on the port.
*					Reading from this register reads the port. Writing to this
*					register modifies the Output Latch (OLAT) register.
*  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
*  Returns:			Byte that was read.
***************************************************************************/
BYTE ReadPortReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = i2c_read1byte(address, MCP23017_GPIOA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = i2c_read1byte(address, MCP23017_GPIOB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = i2c_read1byte(address, MCP23017_GPIOA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = i2c_read1byte(address, MCP23017_GPIOB_BANK1);
		}
	}
	
	return byteRead;
}

/***************************************************************************
*  Function:		SetOutputLatchReg(MCP23017_Port port, BYTE value)
*  Description:		The OLAT register provides access to the output
*					latches. A read from this register results in a read of the
*					OLAT and not the port itself. A write to this register
*					modifies the output latches that modifies the pins
*					configured as outputs.
*  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
*					BYTE value				:	The value to set.
*  Returns:			Nothing
***************************************************************************/
void SetOutputLatchReg(MCP23017_Port port, BYTE value)
{
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			i2c_send(address, MCP23017_OLATA, value);
		}
		else if(port == MCP23017_PORTB)
		{
			i2c_send(address, MCP23017_OLATB, value);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			i2c_send(address, MCP23017_OLATA_BANK1, value);
		}
		else if(port == MCP23017_PORTB)
		{
			i2c_send(address, MCP23017_OLATB_BANK1, value);
		}
	}
}
/***************************************************************************
*  Function:		BYTE ReadOutputLatchReg(MCP23017_Port port)
*  Description:		The OLAT register provides access to the output
*					latches. A read from this register results in a read of the
*					OLAT and not the port itself. A write to this register
*					modifies the output latches that modifies the pins
*					configured as outputs.
*  Receives:		MCP23017_Port port		:	The port on the MCP23017 (MCP23017_PORTA or MCP23017_PORTB).
*  Returns:			Byte that was read.
***************************************************************************/
BYTE ReadOutputLatchReg(MCP23017_Port port)
{
	BYTE byteRead = 0;
	
	if(BankInUse == BANK0)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = i2c_read1byte(address, MCP23017_OLATA);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = i2c_read1byte(address, MCP23017_OLATB);
		}
	}
	else if(BankInUse == BANK1)
	{
		if(port == MCP23017_PORTA)
		{
			byteRead = i2c_read1byte(address, MCP23017_OLATA_BANK1);
		}
		else if(port == MCP23017_PORTB)
		{
			byteRead = i2c_read1byte(address, MCP23017_OLATB_BANK1);
		}
	}
	
	return byteRead;
}