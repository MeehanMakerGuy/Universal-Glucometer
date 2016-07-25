/******************************************************************************
 *
 * FileName:            NokiaTest   interrupts.c
 * Dependencies:        see INCLUDES section 
 * Processor:           PIC16F1786
 * Compiler:            XC8
 * 
 ****************************************************************************** 
/* 
 * File Description:    interrupts.c
 * Change History:
 *      Author           Date        Version
 *      Tom Meehan       7/24/16     V1.1
 * Adapted from: 
 * http://aranna.altervista.org/dragonsnest/microcontroller-projects/nokia-5110
 * -example-c-source-pic16f/?doing_wp_cron=1469323499.5610311031341552734375
 * 
 * ****************************************************************************
 * 
 * Include and Header files   
 *                                                         
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "system.h"
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
//Fairly certain that I don't need this for now
/*#ifndef _PIC12

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

/*      if(INTCONbits.TMR0IF==1)
    {
	INTCONbits.TMR0IF=0;
	if(spk_bit==1)
	{
	    spk_bit=0;
	}else
	{
	    spk_bit=1;
	}

	    if(led_counter>0x115)spk_enable=1;else spk_enable=0;
	    if(led_counter>0x150)
	    {
		if(spk_enable2==1)
		{
		    spk_enable2=0;
		}else
		{
		    spk_enable2=1;
		}
		if(led_bit==1)
		{
		    led_bit=0;
		}else
		{
		    led_bit=1;
		}
		led_counter=0;
	    }

	led_counter++;
    }
}
#endif 
*/

