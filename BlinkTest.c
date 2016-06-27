/*
 * File:   BlinkTest.c
 * Author: Tom
 *
 * Created on June 17, 2016, 1:03 AM
 */


#define _XTAL_FREQ 4000000

#include <xc.h>

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
  TRISB0 = 0; //RB0 as Output PIN
  while(1)
  {
    RB0 = 1;  // LED ON
    __delay_ms(1000); // 1 Second Delay
    RB0 = 0;  // LED OFF
    __delay_ms(1000); // 1 Second Delay
  }
  return 0;
}