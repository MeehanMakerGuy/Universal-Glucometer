/******************************************************************************
 *
 * FileName:            NokiaTest
 * Dependencies:        see INCLUDES section 
 * Processor:           PIC16F1786
 * Compiler:            XC8
 * 
 ****************************************************************************** 
/* 
 * File Description:    main.c
 * Change History:
 * Author           Date        Version
 * Tom Meehan       7/24/16     V1.1
 * Adapted from: 
 * http://aranna.altervista.org/dragonsnest/microcontroller-projects/nokia-5110
 * -example-c-source-pic16f/?doing_wp_cron=1469323499.5610311031341552734375
 * 
 * ****************************************************************************
 * 
 * Include and Header files   
 *                                                         */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

#define _INTOSC 800000 //Internal Oscillator set to 8MHz
//Even though using Internal Oscillator had to set XTAL Frequency
#define _XTAL_FREQ 800000 // to enable __delay_ms() to work

unsigned char led_bit,spk_bit,spk_enable,spk_enable2;
unsigned int led_counter;

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Initialize I/O and Peripherals for application */
    InitApp(); //at end of user.c

    led_counter=0;
    spk_bit=0;  //what are the spk_bits ???
    led_bit=0;

    LCDInit();
    LCDClear();
    gotoXY(1,11);   //(1,11) is about halfway down
    LCDString("PIC 16LF1786");
    
    while(1)
    {
        /* TODO <INSERT USER APPLICATION CODE HERE> */
	if(spk_bit==1)
	{
	    if((spk_enable==1)&&(spk_enable2==1))
	    LATBbits.LATB6=1;  //B6 is the clk in for uploading program to PIC
	}else LATBbits.LATB6=0; 
    }

}

