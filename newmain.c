/*
 * File:   newmain.c
 * ProjectName:    PIC1786Blink    
 * Dependencies:    none
 * Processor:       PIC16LF1786
 * Compiler:        XC8
 * Author: Tom Meehan
 * Company: LearnByMaking.Blogspot.com
 * Created on June 24, 2016, 10:13 PM
 */

#define _INTOSC 800000 //Internal Oscillator set to 8MHz
//Even though using Internal Oscillator had to set XTAL Frequency
#define _XTAL_FREQ 800000 // to enable __delay_ms() to work


#include <xc.h>

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
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = OFF       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming disenabled)

void main(void) {

  TRISB0 = 0; //RB0 as Output PIN
  while(1)  {
      RB0 = 1;
      __delay_ms(1000);
      RB0 = 0;
      __delay_ms(1000);
  }
  return ;
}
