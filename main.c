#define _XTAL_FREQ 4000000
//LCD Pins
#define RS RD2
#define EN RD3 // Enable
#define D4 RD4 // Data 4 - Pin 11 on LCD
#define D5 RD5 // Data 5 - Pin 12 on LCD
#define D6 RD6 // Data 6 - Pin 13 on LCD
#define D7 RD7 // Data 7 - Pin 14 on LCD

#include <xc.h>
#include "lcd.h";

// BEGIN CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

int main()
{
  unsigned int a;
  TRISD = 0x00;
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