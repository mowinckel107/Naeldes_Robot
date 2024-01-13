/****************************************
* "uart_int.h":                         *
* Header file for Mega2560 UART driver. *
* Using UART 0.                         *
* If parameter Rx_Int <> 0 :            *
* Receiver interrupt will be enabled    *
*                                       *
* Henning Hargaard, 11/11 2015          *
*****************************************/

#pragma once

void InitUART(unsigned long BaudRate, unsigned char DataBit, char Parity, unsigned char Rx_Int);
unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendSignedInteger(signed int Tal);
void SendUnsignedInteger(unsigned int Tal);
void SendDouble(double Tal);
void SendCharAsBinary(char Number);
void SendIntAsBinary(int Number);
/****************************************/