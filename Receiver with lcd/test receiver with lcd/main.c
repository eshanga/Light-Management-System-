/*
 * test receiver with lcd.c
 *
 * Created: 7/16/2023 10:05:18 PM
 * Author : KMN IT
 */ 
#ifndef F_CPU
//define CPU clock speed if not defined
#define F_CPU 16000000UL // AVR ATMega328P 16MHz
#endif

#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <util/delay.h> 

#include "lcd.h"
#include "utilityDisplay.h"

#define BAUDRATE 9600

#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)


#define SYNC 0xAA // synchronization signal
#define RADDR1 0x44 // receiver address1
#define RADDR2 0x55 // receiver address1
#define IR1_ADDRESS 0x33
#define IR2_ADDRESS 0x22
#define LED1 0 // LED1 connected to PORTC pin 0
#define LED2 1 // LED1 connected to PORTC pin 1

int count = 0;
 uint8_t data = 0x00;

// Initializing UART
void USART_Init(void)
{
    UBRR0H = (UBRRVAL >> 8);    //high byte
    UBRR0L = (uint8_t)UBRRVAL;  //low byte

    //Set data frame format: asynchronous mode, no parity, 1 stop bit, 8 bit size
    UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) | (0 << UPM01) | (0 << UPM00) | (0 << USBS0) | (0 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00);
    //Enable Receiver Interrupt on receive complete
    UCSR0B = (1 << RXEN0) | (1 << RXCIE0);
}

// Read the value out of the UART buffer
uint8_t USART_vReceiveByte(void)
{
    // Wait until a byte has been received
    while ((UCSR0A & (1 << RXC0)) == 0);
    // Return received data
    return UDR0;
}

// USART Receiver interrupt service routine
ISR(USART_RX_vect)
{
    // Define variables
    uint8_t raddress, data, chk;

    // Receive destination address
    raddress = USART_vReceiveByte();
    // Receive data
    data = USART_vReceiveByte();
    // Receive checksum
    chk = USART_vReceiveByte();
    
    if (chk == (raddress + data)) 
    {
        if (raddress == RADDR1)
        {
		    if (data == 0x11) 
            {
                PORTC |= (1 << LED1); 
                displayStart();
            }
        }
        
        if (raddress == RADDR2)
        {
		    if (data == 0x11) 
            {
                PORTC |= (1 << LED2); 
                displayEnd();
            }
        }
		
		if (raddress == IR1_ADDRESS) // If transmitter address matches RADDR2
		{
			if (data == 0x11) // If command data is 0x11 (turn on LED1)
			{
				 count=count+1;
				 _delay_ms(500);
				data1[0] =count%10;
				data1[1] =count/10;
				displayData();
					
			}
		}
		if (raddress == IR2_ADDRESS) // If transmitter address matches RADDR2
		{
			if (data == 0x11) // If command data is 0x11 (turn on LED1)
			{
				if(count>0)
				{
				count=count-1;;
				_delay_ms(500);
				data1[0] =count%10;
				data1[1] =count/10;	
				displayData();
				}
				
				
				else if(count <= 0)
				{
					displayZero();
				}
				else{
				
				}
			}
		}
    }
}

// Button debouncing variables and constants
#define DEBOUNCE_DELAY_MS 50 // Debounce delay time in milliseconds
volatile uint8_t button1State = 0;
volatile uint8_t button2State = 0;

// Function to debounce buttons
uint8_t debounceButton(volatile uint8_t *buttonState,volatile uint8_t pinMask)
{
    uint8_t currentState = PINB & pinMask;
    if (currentState != *buttonState)
    {
        _delay_ms(DEBOUNCE_DELAY_MS);
        currentState = PINB & pinMask;
        if (currentState != *buttonState)
        {
            *buttonState = currentState;
            return currentState;
        }
    }
    return 0;
}

// Function to initialize buttons
void Button_Init(void)
{
    // Set PB1 and PB2 as input pins
    DDRB &= ~(1 << PB1);
    DDRB &= ~(1 << PB2);

    // Enable internal pull-up resistors for PB1 and PB2
    PORTB |= (1 << PB1) | (1 << PB2);
	
	
}

// Function to check if button 1 is pressed
uint8_t IsButton1Pressed(void)
{
    return debounceButton(&button1State, (1 << PB1));
}

// Function to check if button 2 is pressed
uint8_t IsButton2Pressed(void)
{
    return debounceButton(&button2State, (1 << PB2));
}

// Main initialization
void Main_Init(void)
{
    Lcd_PortConfig();
    DDRC = 0xFF; // Set all pins of PORTC as output.
    PORTC = 0xFF;
    sei(); // Enable global interrupts
    Button_Init();
	 DDRD &= ~(1 << PD0);
}


int main(void)
{
    Main_Init();
    USART_Init();
    Lcd_init();
  displayStand(); //Display greeting at the LCD

    // main endless loop
    while (1)
    {
        if (IsButton1Pressed())
        {
            PORTC ^= (1 << LED1);
            if (PORTC & (1 << LED1))
            {
                displayStart();
            }
            else
            {
                displayStand();
            }
        }

        if (IsButton2Pressed())
        {
            
            PORTC ^= (1 << LED2); 
            if (PORTC & (1 << LED2))
            {
                displayEnd();
            }
            else
            {
                displayStand();
            }
        }
		
		if(count>0)
		{
			PORTC |= (1 << 2);
		}
		else
		{
			PORTC &= 0B11111011;
		}
    }
    return 0;
}
