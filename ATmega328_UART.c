#include "ATmega328_UART.h"


void UART_Init(const UART_CharacterSize characterSize,
            const UART_Parity parity,
      const UART_StopBits stopBits) {
 // Configure baud rate
uint16_t speed = (F_CPU/16/19200-1);
	UBRR0H = (speed >> 8);
	UBRR0L = speed;

 #if USE_2X
 UCSR0A |= (1 << U2X0);
 #else
 UCSR0A &= ~(1 << U2X0);
 #endif

 UCSR0A &= ~(1 << FE0); // clear framing error

 // Enable RX, TX and partially configure character size
 UCSR0B = ((1 << RXEN0) | (1 << TXEN0) | (characterSize & 0x04));

 // Configure parity, stop bits and character size
 UCSR0C = (parity | stopBits | ((characterSize & 0x03) << UCSZ00));
}

void UART_EnableInterruptTxReady(void) {
 UCSR0B |= (1 << UDRIE0);
}

void UART_DisableInterruptTxReady(void) {
 UCSR0B &= ~(1 << UDRIE0);
}

void UART_EnableInterruptRxComplete(void) {
 UCSR0B |= (1 << RXCIE0);
}

void UART_DisableInterruptRxComplete(void) {
 UCSR0B &= ~(1 << RXCIE0);
}


UART_Status UART_WriteReady(void) {
 return ((UCSR0A & UDRE0) == UDRE0);
}

void UART_Putchar(const uint8_t data, FILE *stream) {
 // Append line feed to newline character
 if (data == '\n') {
  UART_Putchar('\r', 0);
 }
 // Wait until write buffer is empty
 while ((UCSR0A & (1 << UDRE0)) == 0) {}
 UDR0 = data;
}

UART_Status UART_ReadReady(void) {
 // Read ready status | errors status
 return ((UCSR0A >> RXC0) | (UCSR0A & 0x1C));
}

uint8_t UART_Getchar(FILE *stream) {
 // Wait until there is something in the read buffer
 while (!(UCSR0A & (1 << RXC0)));
 return UDR0;
}


void UART_Write(const uint8_t data) {
 UDR0 = data;

}

uint8_t UART_Read(void) {
 return UDR0;
}
