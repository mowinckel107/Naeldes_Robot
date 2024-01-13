/************************************************
* "uart_int.c":                                 *
* Implementation file for Mega2560 UART driver. *
* Using UART 0.                                 *
* If parameter Rx_Int <> 0 :                    *
* Receiver interrupt will be enabled.           *
*                                               *
* Henning Hargaard, 3/10 2018                   *
*************************************************/
#include <avr/io.h>
#include <stdlib.h>

#include "uart_int.h"
// Constants
#define XTAL 16000000

/*************************************************************************
USART initialization.
    Asynchronous mode.
	RX and TX enabled.
	Number of Stop Bits = 1.
	Baud rate = Parameter.
	Data bits = Parameter.
Parameters:
	BaudRate: Wanted Baud Rate (110-115200).
	Databits: Wanted number of Data Bits (5-8).
	Parity: 'E' (Even parity), 'O' (Odd parity), otherwise No Parity.
	Rx_Int: If non-zero, receiver interrupt will be enabled.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, char Parity, unsigned char RX_Int)
{
  if ((BaudRate >= 110) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
  {
    // "Normal" clock, no multiprocessor mode (= default)
    UCSR0A = 0b00100000;
    // No interrupts enabled
    // Receiver enabled
    // Transmitter enabled
    // No 9 bit operation
    UCSR0B = 0b00011000;
    // Enable RX interrupt (if wanted by parameter)
    if (RX_Int)
      UCSR0B |= (1<<7);
    // Asynchronous operation, 1 stop bit
    // Bit 2 and bit 1 controls the number of data bits
    UCSR0C = (DataBit-5)<<1;
	// Set parity bits (if parity used)
    if (Parity == 'E')
      UCSR0C |= 0b00100000;
    else if (Parity == 'O')
      UCSR0C |= 0b00110000;
    // Set Baud Rate according to the parameter BaudRate:
    // Adding (8*Baudrate) ensures correct rounding (up/down)
    UBRR0 = (XTAL+(8*BaudRate))/(16*BaudRate) - 1;
  }
}

/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   return UCSR0A & (1<<7);
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
  // Wait for new character received
  while ( (UCSR0A & (1<<7)) == 0 )
  {}
  // Then return it
  return UDR0;
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter :
	Tegn : Character for sending.
*************************************************************************/
void SendChar(char Tegn)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSR0A & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR0 = Tegn;
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
   Streng: Pointer to the string.
*************************************************************************/
void SendString(char* Streng)
{
  // Repeat until zero-termination
  while (*Streng != 0)
  {
    // Send the character pointed to by "Streng"
    SendChar(*Streng);
    // Advance the pointer one step
    Streng++;
  }
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
    Tal: The integer to be converted and sent.
*************************************************************************/
void SendSignedInteger(signed int Tal)
{
char array[7];
  // Convert the integer to an ASCII string (array), radix = 10
  itoa(Tal, array, 10);
  // - then send the string
  SendString(array);
}

void SendUnsignedInteger(unsigned int Tal)
{
	char array[7];
	// Convert the integer to an ASCII string (array), radix = 10
	utoa(Tal, array, 10);
	// - then send the string
	SendString(array);
}

void SendDouble(double Tal)
{
/*
char* dtostrf	(
double 	__val, // The value we want to convert
signed char 	__width, // The total amount of digits, which includes "," and potential "-" of our number
unsigned char 	__prec, // The amount of digits AFTER the comma
char * 	__s	// The string to save it in
)
*/

	char array[50];
	dtostrf(Tal, 20 , 10, array);
	// - then send the string
	SendString(array);
}


void SendCharAsBinary(char Number)
{
	unsigned char counter = 0;
	for (unsigned char i = 8; i > 0; i--) // Run thought each bit of a char, printing 1 or 0 as we go
	{
	    if((counter%4 == 0) & (counter != 0)) // place a space after every 4 bits for ease of reading
	    {
		    SendString(" ");
	    }

		if (Number & (0b00000001<<(i-1)))
		{
			SendString("1");
		}
		else
		{
			SendString("0");
		}
		counter++;
	}
}

void SendIntAsBinary(int Number)
{
	unsigned char counter = 0;
	for (unsigned char i = 16; i > 0; i--) // Run thought each bit of a char, printing 1 or 0 as we go
	{
	    if((counter%4 == 0) & (counter != 0)) // place a space after every 4 bits for ease of reading
	    {
		    SendString(" ");
	    }

		if (Number & (0b0000000000000001<<(i-1)))
		{
			SendString("1");
		}
		else
		{
			SendString("0");
		}
		counter++;
	}
}


/************************************************************************/