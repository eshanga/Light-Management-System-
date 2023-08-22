/*
 * test transmitter.c
 *
 * Created: 7/16/2023 12:46:14 PM
 * Author : KMN IT
 */ 


//define CPU clock speed if not defined
#ifndef F_CPU
//define CPU clock speed if not defined
#define F_CPU 16000000UL // AVR ATMega328P 16MHz
#endif


#include <avr/io.h> 
#include <util/delay.h>

//set desired baud rate
#define BAUDRATE 9600
//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)


#define SYNC 0xAA // synchronization signal
#define RADDR1 0x44 // receiver address1
#define RADDR2 0x55 // receiver address1
#define IR1_ADDRESS 0x33
#define IR2_ADDRESS 0x22

#define BUTTON1 0 // button switch connected to port C pin 0
#define BUTTON2 1 // button switch connected to port C pin 0




// Initializing UART
void USART_Init(void)
{
    // Setting the baud rate is done by writing to the UBRR0H and UBRR0L registers
    UBRR0H = (UBRRVAL >> 8);    //high byte
    UBRR0L = (uint8_t)UBRRVAL;  //low byte

    //Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
    UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) | (0 << UPM01) | (0 << UPM00) | (0 << USBS0) | (0 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00);
    //Enable Transmitter
    UCSR0B = (1 << TXEN0);
}

// Transmit data(byte) function
void USART_vSendByte(uint8_t u8Data)
{
    // Wait for transmit buffer to be empty
    while ((UCSR0A & (1 << UDRE0)) == 0);
    // Transmit data - load data into transmit register
    UDR0 = u8Data;
}

// Send packet of data
void Send_Packet(uint8_t addr, uint8_t cmd)
{
    USART_vSendByte(SYNC); // send synchronization byte
    USART_vSendByte(addr); // send receiver address
    USART_vSendByte(cmd);  // send command
    USART_vSendByte((addr + cmd)); // send checksum
}

unsigned char pir_state1()
{
    if (!(PINC & (1 << BUTTON1))) // the button is pressed when BUTTON bit is clear
    {
        if (!(PINC & (1 << BUTTON1))) return 1; // check the state of the button again
    }
    return 0;
}

unsigned char pir_state2()
{
	if (!(PINC & (1 << BUTTON2))) // the button is pressed when BUTTON bit is clear
	{
		if (!(PINC & (1 << BUTTON2))) return 1; // check the state of the button again
	}
	return 0;
}

unsigned char ir_state3()
{
	if (!(PINB & (1 << 1))) // the button is pressed when BUTTON bit is clear
	{
		if (!(PINB & (1 << 1))) return 1; // check the state of the button again
	}
	return 0;
}
unsigned char ir_state4()
{
	if (!(PINB & (1 << 2))) // the button is pressed when BUTTON bit is clear
	{
		if (!(PINB & (1 << 2))) return 1; // check the state of the button again
	}
	
	return 0;
}
// Main initialization
void Main_Init(void)
{
   DDRC = 0xFF; // Set all pins of PORTC as output.
	DDRB = 0xFF; // Set all pins of PORTB as output
    DDRC &= ~(1 << BUTTON1); // Make pin 0 of PORTC as Input
	DDRC &= ~(1 << BUTTON2); // Make pin 1 of PORTC as Input
	DDRB &= ~(1 << 1); // Make pin 1 of PORTB as Input
	DDRB &= ~(1 << 2); // Make pin 2 of PORTB as Input
	// DDRD |= (1 << PD1);
   // PORTC = 0xFF; // Set all pins of PORTC as HIGH. Internal Pull-Up resistor is enabled.
}

// main function - entry point of the program
int main(void)
{
    USART_Init();
    Main_Init();

    // main endless loop
    while (1)
    {
        if (pir_state1()) // If BUTTON1 is pressed
        {
            Send_Packet(RADDR1, 0x11); // Send command to turn on LED1
        }
        else
        {
            Send_Packet(RADDR1, 0x00); // Send command to turn off LED1
        }
		 if (pir_state2()) // If BUTTON1 is pressed
		 {
			 Send_Packet(RADDR2, 0x11); // Send command to turn on LED1
		 }
		else
		 {
			 Send_Packet(RADDR2, 0x00); // prSend command to turn off LED1
		 }
 		 if (ir_state3et(IR1_ADDRESS, 0x11); // Send command to turn on LED1
 		 }
		 else
	{()) // If IR connected to PB1 detects a signal
 		 {
 			 Send_Pack
	 Send_Packet(IR1_ADDRESS, 0x00); // Send command to turn off LED1
		 }
		 
		 if (ir_state4()) // If IR connected to PB2 detects a signal
 		 {
 			 Send_Packet(IR2_ADDRESS, 0x11); 
 		 }
		else
		 {
			 Send_Packet(IR2_ADDRESS, 0x00); 
		 }
    }

    return 0;
}
