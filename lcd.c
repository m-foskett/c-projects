/******************************************************************************

   FILE 
      filename.c
      
   ENTRY (PUBLIC) ROUTINE - May be called from outside this module
      function            -  the C function may be called from the OS
      
   PRIVATE ROUTINE   - May *ONLY* be called from inside this module
      None
      
   INITIALISATION ROUTINES
      None
      
   DESCRIPTION 
        MTRX3700 Major Project


/******************************************************************************
                               I M P O R T S                                */

   
#include <stdio.h>      // standard C header file
#include <stdlib.h>
#include <p18f4520.h>    // Include microcontroller specific files
#include <string.h>
//#include <configReg.h>



/******************************************************************************
                         P R I V A T E    D A T A
          N A M E D    C O N S T A N T S    A N D    M A C R O S            */
#define DB4 PORTDbits.RD0
#define DB5 PORTDbits.RD1
#define DB6 PORTDbits.RD2
#define DB7 PORTDbits.RD3
#define RS   PORTDbits.RD4
#define RW PORTDbits.RD5
#define E  PORTDbits.RD6

/******************************************************************************
                    F O R W A R D    D E C L A R A T I O N S                */
void putsLCD(unsigned char *string[]);
void putcLCD(unsigned char character);
void clearLCD(void);
void initLCD(void);
void usDelay(int multiple);
void msDelay(int multiple);
void instructionWrite(unsigned char instruction);
void moveCursor(int pos, int line);
void enableSignal(void);
/******************************************************************************
            E N T R Y    R O U T I N E    D E F I N I T I O N               */
void main(void)
{
    TRISD = 0; // Set PORTD to outputs for databus and control bits
    PORTD = 0; // Initially clear all pins
    initLCD(); // Initiate the LCD with the new settings
    //usDelay(); // Let LCD finish internal operations after new settings
    putsLCD("Welcome to Joustice!");
    //msDelay(4000);  // Enough time to read it
    //clearLCD();
    // Next things to be done
}


/******************************************************************************
            P R I V A T E   R O U T I N E   D E F I N I T I O N              */
void instructionWrite(unsigned char instruction)
{
    RS = 0; // Instruction Register
    RW = 0; // Write Operation
    DB7 = instruction & 0x80;  // Extracting the Higher Order Nibble
    DB6 = instruction & 0x40;
    DB5 = instruction & 0x20;
    DB4 = instruction & 0x10;
    // enableSignal();
    DB7 = instruction & 0x08;  // Extracting the Lower Order Nibble
    DB6 = instruction & 0x04;
    DB5 = instruction & 0x02;
    DB4 = instruction & 0x01;
    // enableSignal();
}

void initLCD(void)
{
    // Default Startup Conditions: 
    //  - 8-bit data bus mode
    //  - 1 line display
    //  - Display/Cursor OFF
    
    msDelay(35);            // 30 ms delay after Vdd rises to 4.5V 
    instructionWrite(0x20); // Change to 4 - bit mode (lower nibble = dont care)
    instructionWrite(0x20); // Change to 4 - bit mode still
    instructionWrite(0x80); // 2-line mode, 5 x 8 Font type
    usDelay(50);            // delay > 39 micro
    instructionWrite(0x0F); // Display and Cursor ON, Cursor Blink ON
    usDelay(50);            // delay > 39 micro
    instructionWrite(0x01); // Send blanks to all DDRAM (Clear Display)
    msDelay(2);              // delay > 1.53 milli
    instructionWrite(0x06); // Increment DDRAM by 1 and cursor moves right
                            // Shift Display OFF (?)  
}

void clearLCD(void)
{
    RS = 0; // Instruction Register (IR)
    RW = 0; // Write Operation
    instructionWrite(0x01); // Clears the LCD
    msDelay(2); // delay > 1.53 milli
}

void putcLCD(unsigned char character)
{
    RS = 1; // Data Register (DR) Selected
    RW = 0; // Write Operation
    // Potentially need to subtract  48 from character (ASCII)
    DB7 = character & 0x80;  // Extracting the Higher Order Nibble
    DB6 = character & 0x40;
    DB5 = character & 0x20;
    DB4 = character & 0x10;
    // enableSignal();
    DB7 = character & 0x08;  // Extracting the Lower Order Nibble
    DB6 = character & 0x04;
    DB5 = character & 0x02;
    DB4 = character & 0x01;
    // enableSignal();
}

void putsLCD(char *string[])
{
    // Behaviour at end of 1st line of LCD unsure, may need to manually move 
    // cursor(address counter) to 2nd line of LCD
    int i, maxPos = 16;
    RS = 0;
    RW= 0;
    for(i=0;i<strlen(string);i++)
    {
        if(i = 16)
        {
           break;
        }
        putcLCD(string[i]);
    }
    instructionWrite(0xC0); // Moves the address counter to 2nd line 1st pos
                            // (DDRAM = 0x40)[1:upper 3 bits:lower 4 bits]
    for(;i<strlen(string);i++)
    {
        putcLCD(string[i]); // Assuming we don't exceed 32 characters (2 x 16)
    }
}

void moveCursor(int pos, int line)
{
    
}

void usDelay(int multiple)
{
    int i,j,microsecond;    //Need to set value which corresponds to 1us
    for(i=0;i<multiple;i++)
    {
        for(j=0;j<microsecond;j++);
    }
}

void msDelay(int multiple)
{
    usDelay(multiple*1000);
}

void enableSignal(void)
{
    E = 1; // Enable Signal 
    // some delay
    E = 0;
    // some delay for internal ops to finish
    // can check busy flag
    // delay based on after busy flag goes low  = 1/2Fosc
}