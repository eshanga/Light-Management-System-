/*
 * lcd.h
 *
 * Created: 7/16/2023 10:34:02 PM
 *  Author: KMN IT
 */ 


#ifndef LCD_H_
#define LCD_H_


#define LcdDataBus    PORTD
#define LcdControlBus PORTD

#define LcdDataBusDirnReg DDRD

#define LCD_RS 1
#define LCD_RW 2
#define LCD_EN 3

void Lcd_PortConfig(void)
{
	LcdDataBusDirnReg = 0xFE; //POrt as Output
	

}

void Lcd_CmdWrite(char cmd)
{
	LcdDataBus = (cmd & 0xF0);    //Set upper 4 bits of the cmd
	LcdControlBus &= ~(1<<LCD_RS);//Set RS pin to LOW
	LcdControlBus &= ~(1<<LCD_RW);//Set RW pin to LOW
	LcdControlBus |= (1<<LCD_EN); //Generate High-to-Low pulse
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	
	_delay_ms(10);
	
	LcdDataBus = ((cmd<<4) & 0xF0);    //Set lower 4 bits of the cmd
	LcdControlBus &= ~(1<<LCD_RS);//Set RS pin to LOW
	LcdControlBus &= ~(1<<LCD_RW);//Set RW pin to LOW
	LcdControlBus |= (1<<LCD_EN); //Generate High-to-Low pulse
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(10);
}

void Lcd_DataWrite(char dat)
{
	LcdDataBus = (dat & 0xF0);    //Set upper 4 bits of the data
	LcdControlBus |= (1<<LCD_RS);//Set RS pin to High
	LcdControlBus &= ~(1<<LCD_RW);//Set RW pin to LOW
	LcdControlBus |= (1<<LCD_EN); //Generate High-to-Low pulse
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	
	_delay_ms(10);
	
	LcdDataBus = ((dat<<4) & 0xF0);    //Set lower 4 bits of the data
	LcdControlBus |= (1<<LCD_RS);//Set RS pin to HIGH
	LcdControlBus &= ~(1<<LCD_RW);//Set RW pin to LOW
	LcdControlBus |= (1<<LCD_EN); //Generate High-to-Low pulse
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(10);
}

void Lcd_init(void)
{
	Lcd_CmdWrite(0x02); //Initialize Lcd in 4-bit mode
	Lcd_CmdWrite(0x28); //enable 5x7 mode for chars
	Lcd_CmdWrite(0x0E); //Display OFF, Cursor ON
	Lcd_CmdWrite(0x01); //Clear Display
}




#endif /* LCD_H_ */