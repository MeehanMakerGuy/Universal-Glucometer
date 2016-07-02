/*
 * File:   main_1.c
 * ProjectName:    PIC1786lcd    
 * Dependencies:    none
 * Processor:       PIC16LF1786
 * Compiler:        XC8
 * Author: Tom Meehan
 * Company: LearnByMaking.Blogspot.com
 * Created on July 1, 2016, 12:32 AM
 */

#define _INTOSC 800000 //Internal Oscillator set to 8MHz
//Even though using Internal Oscillator had to set XTAL Frequency
#define _XTAL_FREQ 800000 // to enable __delay_ms() to work 

//LCD Pin connections to micro-controller changed for the PIC16F1786
#define RS RC5
#define EN RC6 // Enable
#define D4 RC4 // Data 4 - Pin 11 on LCD
#define D5 RC3 // Data 5 - Pin 12 on LCD
#define D6 RC2 // Data 6 - Pin 13 on LCD
#define D7 RC7 // Data 7 - Pin 14 on LCD

#include <xc.h>
#include "lcd_1.h";

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (Low-voltage programming enabled)
//END CONFIG

int main()
{
  unsigned int a;
  TRISC = 0x00;
  Lcd_Init();
  while(1)
  {
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("LCD Library for");
    Lcd_Set_Cursor(2,4);
    Lcd_Write_String("MPLAB XC8");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("LearnByMaking");
    Lcd_Set_Cursor(2,5);
    Lcd_Write_String("a ....");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,3);
    Lcd_Write_String("Universal");
    Lcd_Set_Cursor(2,3);
    Lcd_Write_String("Glucometer");
    __delay_ms(2000);

    for(a=0;a<15;a++)
    {
        __delay_ms(300);
        Lcd_Shift_Left();
    }

    for(a=0;a<15;a++)
    {
        __delay_ms(300);
        Lcd_Shift_Right();
    }
__delay_ms(2000);
    Lcd_Clear();
  }
  return 0;
}