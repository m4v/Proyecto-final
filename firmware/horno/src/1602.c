/*
===============================================================================
 Name        : LCD_16x2_PLL.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

/* Mod by gastonriera
 Connections from LPC1769 to LCD Module:
 P2.0 to P2.7 used as Data bits.
 P0.4 connected to pin4 i.e. RS	- Command / Data
 P0.5 connected to pin6 i.e. E - Enable
 Pin5 of LCD Module i.e. 'R/W' connected to ground
*/


#define PLOCK 0x00000400

void initLCD(void);
void enable(void);
void LCD_WriteChar(char c);
void LCD_WriteString(char * string);
void LCD_Cmd(unsigned int cmd);
void delayMS(unsigned int milliseconds);

void setupPLL0(void);
void feedSeq(void);
void connectPLL0(void);


int main(void)
{
    setupPLL0();
    feedSeq(); //sequence for locking PLL to desired freq.
    connectPLL0();
    feedSeq(); //sequence for connecting the PLL as system clock

    //SysClock is now ticking @ 60Mhz!

	initLCD(); //LCD Now intialized and ready to Print!
	LCD_WriteString(" Estamos andando");
	LCD_Cmd(0x80 + 0x40); //Come to 2nd Row
	LCD_WriteString("  con clock PLL");
	while(1); // Loop forever
	return 0; //This won't execute :P
}

void initLCD(void)
{
	LPC_GPIO2->FIODIR = 0xFF; //P2.0 to P2.7 configured as Output - Using 8 Bit mode
	LPC_GPIO0->FIODIR |= (1<<4) | (1<<5); //P0.4 and P0.5 configured as Output - Control Pins
	LPC_GPIO2->FIOPIN  = 0x0; //- No sé porqué lo hace. Reset Port2 to 0.
	LPC_GPIO0->FIOPIN  = 0x0; //- No sé porqué lo hace. Reset Port0 to 0 - Which also makes RS and Enable LOW.

	//LCD Initialization Sequence Now starts
	delayMS(20); //Initial Delay
	LCD_Cmd(0x3C); //Function Set Command : 8 Bit Mode , 2 Rows , 5x10 Font Style
	LCD_Cmd(0x0F); //Display Switch Command : Display on , Cursor on , Blink on
	LCD_Cmd(0x06); //Input Set : Increment Mode
	LCD_Cmd(0x01); //Screen Clear Command , Cursor at Home
	LCD_Cmd(0x80); //Not required the 1st time but needed to reposition the cursor at home after Clearing Screen
	//Done!
}

void enable(void)
{
    //Using common delay of 2ms
	delayMS(2);
	LPC_GPIO0->FIOPIN |=  (1<<5);//Enable=High
    delayMS(2);
    LPC_GPIO0->FIOPIN &= ~(1<<5);//Enable=Low
    delayMS(2);
}

void LCD_WriteChar(char c)
{
	LPC_GPIO0->FIOPIN |= (1<<4); //Switch to Data Mode
	LPC_GPIO2->FIOPIN = (int) c; //Supply Character Code
    enable(); //Pulse Enable to process it
}

void LCD_WriteString(char * string)
{
    int c=0;
    while (string[c]!='\0')
    {
        LCD_WriteChar(string[c]);
        c++;
    }
}

void LCD_Cmd(unsigned int cmd)
{
	LPC_GPIO0->FIOPIN = 0x0; //Enter Instruction Mode
	LPC_GPIO2->FIOPIN = cmd; //Supply Instruction/Command Code
    enable(); //Pulse Enable to process it
}

void delayMS(unsigned int milliseconds)
{
//Timers will be explained in detail in the very next tutorial @ www.ocfreaks.com/cat/embedded/

	int i=0;
	int t_f;
	int clock = 60000; // 60k ciclos es 1 ms
	t_f=clock*milliseconds;
	while(i<t_f){i++;}
}

//---------PLL Related Functions :---------------

void setupPLL0(void)
{
	LPC_SC->PLL0CON |=  (1<<0); // PPLE=1 & PPLC=0 so it will be enabled
                    // but not connected after FEED sequence
	LPC_SC->PLL0CFG |= 0x04; // set the multipler to 5 (i.e actually 4)
                    // i.e 12x5 = 60 Mhz (M - 1 = 4)!!!
                    // Set P=2 since we want FCCO in range!!!
                    // So , Assign PSEL =01 in PLL0CFG as per the table.
}

void feedSeq(void)
{
	LPC_SC->PLL0FEED = 0xAA;
	LPC_SC->PLL0FEED = 0x55;
}

void connectPLL0(void)
{
    // check whether PLL has locked on to the  desired freq by reading the lock bit
    // in the PPL0STAT register

	if ((LPC_SC->PLL0STAT,25)){
		LPC_SC->PLL0CON |= (1<<1);
	}
	else
		connectPLL0();
}
