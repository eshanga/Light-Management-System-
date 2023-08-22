/*
 * utilityDisplay.h
 *
 * Created: 7/16/2023 10:35:01 PM
 *  Author: KMN IT
 */ 


#ifndef UTILITYDISPLAY_H_
#define UTILITYDISPLAY_H_


#define MAX_LENGTH 10
int data1[MAX_LENGTH];


void displayHello(void)
{
	Lcd_CmdWrite(0x01);
	Lcd_CmdWrite(0x80);
	Lcd_DataWrite('H');
	Lcd_DataWrite('E');
	Lcd_DataWrite('L');
	Lcd_DataWrite('L');
	Lcd_DataWrite('O');
	Lcd_DataWrite(':');
}

void displayStart(void)
{
	Lcd_CmdWrite(0x80);
	for (uint8_t i = 0; i < 16; i++) {
		Lcd_DataWrite(' '); // Write empty space to clear the character
	}
	Lcd_CmdWrite(0x80);
	Lcd_DataWrite('A');
	Lcd_DataWrite('R');
	Lcd_DataWrite('E');
	Lcd_DataWrite('A');
	Lcd_DataWrite(' ');
	Lcd_DataWrite('1');
	//Lcd_CmdWrite(0x01);
}

void displayEnd(void)
{
	Lcd_CmdWrite(0x80);
	for (uint8_t i = 0; i < 16; i++) {
		Lcd_DataWrite(' '); // Write empty space to clear the character
	}
	Lcd_CmdWrite(0x80);
	Lcd_DataWrite('A');
	Lcd_DataWrite('R');
	Lcd_DataWrite('E');
	Lcd_DataWrite('A');
	Lcd_DataWrite(' ');
	Lcd_DataWrite('2');
	//Lcd_CmdWrite(0x01);
}

void displayEnd1(void)
{
	Lcd_CmdWrite(0x80);
	for (uint8_t i = 0; i < 16; i++) {
		Lcd_DataWrite(' '); // Write empty space to clear the character
	}
	Lcd_CmdWrite(0x80);
	Lcd_DataWrite('A');
	Lcd_DataWrite('R');
	Lcd_DataWrite('E');
	Lcd_DataWrite('A');
	Lcd_DataWrite(' ');
	Lcd_DataWrite('1');
	Lcd_DataWrite('2');
	//Lcd_CmdWrite(0x01);
}

void displayStand(void)
{
	//Lcd_CmdWrite(0x01);
	Lcd_CmdWrite(0x80);
	Lcd_DataWrite('S');
	Lcd_DataWrite('T');
	Lcd_DataWrite('A');
	Lcd_DataWrite('N');
	Lcd_DataWrite('D');
	Lcd_DataWrite(' ');
	Lcd_DataWrite('B');
	Lcd_DataWrite('Y');
	Lcd_DataWrite(':');
	
}
void displayZero(void)
{
	Lcd_CmdWrite(0xC0);
	for (uint8_t i = 0; i < 16; i++) {
		Lcd_DataWrite(' '); // Write empty space to clear the character
	}
	Lcd_CmdWrite(0xC0);
	Lcd_DataWrite('N');
	Lcd_DataWrite('O');
	Lcd_DataWrite(' ');
	Lcd_DataWrite('V');
	Lcd_DataWrite('I');
	Lcd_DataWrite('S');
	Lcd_DataWrite('I');
	Lcd_DataWrite('T');
	Lcd_DataWrite('O');
	Lcd_DataWrite('R');
	Lcd_DataWrite('S');
	
}

void displayCount(void)
{
	Lcd_DataWrite('C');
	Lcd_DataWrite('O');
	Lcd_DataWrite('U');
	Lcd_DataWrite('N');
	Lcd_DataWrite('T');
	Lcd_DataWrite(':');
}


void displayData(void)
{
	Lcd_CmdWrite(0xC0);
	for (uint8_t i = 0; i < 16; i++) {
		Lcd_DataWrite(' '); // Write empty space to clear the character
	}
	Lcd_CmdWrite(0xC0);
	displayCount();
    Lcd_DataWrite(data1[1]+0x30);
    Lcd_DataWrite(data1[0]+0x30);
}




#endif /* UTILITYDISPLAY_H_ */